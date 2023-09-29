'''
This service delivers and process images from camera to QML GUI

'''
from ids_peak_ipl.ids_peak_ipl import PixelFormatName_BGR8, ConversionMode_Fast, ConversionMode_HighQuality
from PySide6.QtCore import QThread, Signal, Slot, QObject
from ids_peak import ids_peak, ids_peak_ipl_extension
import numpy as np
import src.constants.Constants as const
import cv2


class ImageProvider(QThread):

    def __init__(self):
        super().__init__()
        self.image = None
        self.device_manager = None
        self.device = None
        self.nodemap_remote_device = None
        self.nodemap_datastream = None

    def _get_image(self, cam : int):
        """
        Private Method. uses IDS peak API to obtain image from chosen camera
        image is copied to image property.

        :param cam: Set to 0  to obtain image from GiGE camera. 1 to get image from gripper cam.
        :type cam: int

        """
        # initialize IDS API library
        ids_peak.Library.Initialize()
        self.device_manager = ids_peak.DeviceManager.Instance()
        print(f"CameraService.ImageProvider._get_image(), devicemanager at {str(self.device_manager)}")

        try:
            # try to update device manager
            self.device_manager.Update()
            if self.device_manager.Devices().empty():
                print("CameraService.ImageProvider.Setup: No device found. Exiting Camera Setup.")
                return
            else:
                # print all availlable devices in cli
                for i, device in enumerate(self.device_manager.Devices()):
                    print(str(i) + ": " + device.ModelName() + " ("
                          + device.ParentInterface().DisplayName() + "; "
                          + device.ParentInterface().ParentSystem().DisplayName() + "v."
                          + device.ParentInterface().ParentSystem().Version() + ")")

                # open device
                self.device = self.device_manager.Devices()[cam].OpenDevice(ids_peak.DeviceAccessType_Control)

                # get remote device node map
                self.nodemap_remote_device = self.device.RemoteDevice().NodeMaps()[0]

                # print model name and user id
                print("CameraService.ImageProvider.Setup:\nModel Name: " + self.nodemap_remote_device.FindNode("DeviceModelName").Value())
                try:
                    print("User ID: " + self.nodemap_remote_device.FindNode("DeviceUserID").Value())
                except ids_peak.Exception:
                    print("User ID: (unknown)")

                # print sensor information
                try:
                    print("Sensor Name: " + self.nodemap_remote_device.FindNode("SensorName").Value())
                except ids_peak.Exception:
                    print("Sensor Name: " + "(unknown)")
                # print resolution information
                try:
                    print("Max. resolution (w x h): "
                          + str(self.nodemap_remote_device.FindNode("WidthMax").Value()) + " x "
                          + str(self.nodemap_remote_device.FindNode("HeightMax").Value()))
                except ids_peak.Exception:
                    print("Max. resolution (w x h): (unknown)")
                # set up datastream and open datastream
                self.data_streams = self.device.DataStreams()
                if self.data_streams.empty():
                    print("CameraService.ImageProvider.extractImage: No data stream found")
                    return
                self.data_stream = self.device.DataStreams()[0].OpenDataStream()
                self.nodemap_datastream = self.data_stream.NodeMaps()[0]

                try:
                    if self.data_stream:
                        # Flush buffer queue and prepare buffers to be revoked
                        self.data_stream.Flush(ids_peak.DataStreamFlushMode_DiscardAll)

                        # Clear all buffers
                        try:
                            for buffer in self.data_stream.AnnouncedBuffers():
                                self.data_stream.RevokeBuffer(buffer)
                        except Exception as e:
                            print(f"CameraService.ImageProvider.extractImage: Error while revoking buffers: {str(e)}")
                        payload_size = self.nodemap_remote_device.FindNode("PayloadSize").Value()
                        print(f"CaneraService.ImageProvider.extractImage: {payload_size}")
                        num_buffers_min_required = self.data_stream.NumBuffersAnnouncedMinRequired()
                        print(f"number of minimum buffers required: {num_buffers_min_required}")
                        # Allocate and announce buffers
                        try:
                            for count in range(num_buffers_min_required):
                                buffer = self.data_stream.AllocAndAnnounceBuffer(payload_size)
                                self.data_stream.QueueBuffer(buffer)
                        except Exception as e:
                            print(f"CameraService.ImageProvider.extractImage: Error while allocating buffer: {str(e)}")
                except Exception as e:
                    print(f"CameraService.ImageProvider.extractImage: Error while announcing buffers: {str(e)}")

                # Start acquisition
                try:
                    self.data_stream.StartAcquisition(ids_peak.AcquisitionStartMode_Default, ids_peak.DataStream.INFINITE_NUMBER)
                    self.nodemap_remote_device.FindNode("TLParamsLocked").SetValue(1)
                    self.nodemap_remote_device.FindNode("AcquisitionStart").Execute()
                except Exception as e:
                    print(f"CameraServicee.ImageProvider.extractImage: Error while starting acquisition: {str(e)}")

                # receive image
                try:
                    buffer = self.data_stream.WaitForFinishedBuffer(5000)
                    image = ids_peak_ipl_extension.BufferToImage(buffer)
                    image = image.ConvertTo(PixelFormatName_BGR8, ConversionMode_HighQuality)
                    self.data_stream.QueueBuffer(buffer)
                    # convert image to numpy array and decouple it from data stream
                    self.image = np.copy(image.get_numpy_3D())
                    self.image = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
                except Exception as e:
                    print(str(e))
        except:
            print("CameraService.ImageProvide.Setup: Error while updating device manager")
        finally:
            ids_peak.Library.Close()


    def get_image(self, cam):
        """
        Public wrapper to call _get_image method.
        returns the obtained image
        """
        if cam == 0:
            self._get_image(0)
        elif cam == 1:
            self._get_image(1)
        else:
            raise ValueError("CameraService.ImageProvider.getImage: Invalid camera number")
        return self.image


    '''
    def get_image(self, cam):
        if cam == 0:
            return cv2.imread("../../Jupyter/ChessBoardImages/rawShot24Mp.png")
        elif cam == 1:
            return cv2.imread("../../Jupyter/ChessBoardImages/rawShot5Mp.png")
    '''

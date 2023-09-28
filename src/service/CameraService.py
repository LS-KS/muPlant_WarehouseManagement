'''
This service delivers and process images from camera to QML GUI

'''
import ids_peak_ipl.ids_peak_ipl
from PySide6.QtCore import QThread, Signal, Slot, QObject
from ids_peak import ids_peak_ipl_extension
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
        ids_peak.Library.Initialize()
        self.device_manager = ids_peak.DeviceManager.Instance()
        print(f"CameraService.ImageProvider._get_image(), devicemanager at {str(self.device_manager)}")
        try:
            self.device_manager.Update()
            if self.device_manager.Devices().empty():
                print("CameraService.ImageProvider.Setup: No device found. Exiting Camera Setup.")
                return
            else:
                for i, device in enumerate(self.device_manager.Devices()):
                    print(str(i) + ": " + device.ModelName() + " ("
                          + device.ParentInterface().DisplayName() + "; "
                          + device.ParentInterface().ParentSystem().DisplayName() + "v."
                          + device.ParentInterface().ParentSystem().Version() + ")")
                self.device = self.device_manager.Devices()[cam].OpenDevice(ids_peak.DeviceAccessType_Control)
                self.nodemap_remote_device = self.device.RemoteDevice().NodeMaps()[0]
                print("CameraService.ImageProvider.Setup:\nModel Name: " + self.nodemap_remote_device.FindNode("DeviceModelName").Value())
                try:
                    print("User ID: " + self.nodemap_remote_device.FindNode("DeviceUserID").Value())
                except ids_peak.Exception:
                    print("User ID: (unknown)")
                try:
                    print("Sensor Name: " + self.nodemap_remote_device.FindNode("SensorName").Value())
                except ids_peak.Exception:
                    print("Sensor Name: " + "(unknown)")
                    try:
                        print("Max. resolution (w x h): "
                              + str(self.nodemap_remote_device.FindNode("WidthMax").Value()) + " x "
                              + str(self.nodemap_remote_device.FindNode("HeightMax").Value()))
                    except ids_peak.Exception:
                        print("Max. resolution (w x h): (unknown)")
                self.data_streams = self.device.DataStreams()
                self.data_stream = self.device.DataStreams()[0].OpenDataStream()
                self.nodemap_datastream = self.data_stream.NodeMaps[0]
                if self.data_stream.empty():
                    print("CameraService.ImageProvider.extractImage: No data stream found")
                    return
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
                        num_buffers_min_required = self.data_stream.NumBuffersAnnouncedMinRequired()

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
                    image = image.ConvertTo(ids_peak_ipl.PixelFormatName_BGR8, ids_peak_ipl.ConversionMode_HIGHQUALITY)
                    self.data_stream.QueueBuffer(buffer)
                    # convert image to numpy array and decouple it from data stream
                    self.image = np.copy(image.get_numpy_3D())
                    self.image = cv2.cvtColor(self.image, cv2.COLOR_BGR2RGB)
                except Exception as e:
                    print(str(e))
        except:
            print("CameraService.ImageProvide.Setup: Error while updating device manager")
        finally:
            ids_peak.Library.Close()


    def get_image(self, cam):
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

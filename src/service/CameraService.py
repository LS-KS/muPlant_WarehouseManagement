'''
This service delivers and process images from camera to QML GUI

'''
import ids_peak.ids_peak
import ids_peak_ipl.ids_peak_ipl
from PySide6.QtCore import QThread, Signal, Slot, QObject
from ids_peak import ids_peak_ipl_extension
import numpy as np
import src.constants.Constants as const

class _ImageProvider(QThread):

    def __init__(self):
        super().__init__()
        self.image = None
        ids_peak.Library.Initialize()
        self.device_manager = ids_peak.DeviceManager.Instance()
        print(f"CameraService.ImageProvider: Device Manager initialized{str(self.device_manager)}")
        self.device = None
        self.nodemap_remote_device = None

    def _setup(self, cam : int):
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
        except:
            print("CameraService.ImageProvide.Setup: Error while updating device manager")

    def _extractImage(self):
        self.data_stream = self.device.DataStreams()
        if self.data_stream.empty():
            print("CameraService.ImageProvider.extractImage: No data stream found")
            return
        try:
            if self.data_stream:
                # Flush buffer queue and prepare buffers to be revoked
                for buffer in self.data_stream.AnnouncedBuffers():
                    self.data_stream.RevokeBuffer(buffer)
                payload_size = self.nodemap_remote_device.FindNode("PayloadSize").Value()
                num_buffers_min_required = self.data_stream.NumBuffersAnnouncedMinRequired()

                # Allocate and announce buffers
                for count in range(num_buffers_min_required):
                    buffer = self.data_stream.AllocAndAnnounceBuffer(payload_size)
                    self.data_stream.QueueBuffer(buffer)
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
        except Exception as e:
            print(str(e))

class RobotImageProvider:


    def __init__(self):
        self.camera = 1
        self.deviceName = "UI158xSE-C"

    def get_image(self):
        pass

    def get_aruco_data(self):
        pass



class StoragecellImageProvider:


    def __init__(self):
        self.camera = 0
        self.deviceName = "GV-580xSE-C"


    def get_image(self):
        pass

    def get_aruco_data(self):
        pass
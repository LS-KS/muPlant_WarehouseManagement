'''
This Python File implements the logic to recognize arUco markers.
class VideoThread inherits from QThread class. So image capture and image processing code is in seperated thread.
Processed images are provided to qml by using class videoPlayer which inherits from QQuickImageProvider.
'''

import cv2
from PySide6.QtGui import QImage
from PySide6.QtCore import Signal, Slot, Qt, QThread
from PySide6.QtQuick import QQuickImageProvider
from PySide6.QtQml import QQmlImageProviderBase


class VideoThread(QThread):
    #: Signal which is emitted when a new image is ready for QQuickImageProvider
    frameChanged = Signal(QImage)

    def __init__(self, cam:int ,parent=None):
        QThread.__init__(self, parent)
        self.capture = cv2.VideoCapture(cam)  #: initializes the camera device.
        self.capture.set(cv2.CAP_PROP_FPS, 30)  #: limit FPS cap to 30 fps. This is set to slow the thread down.
        self.running = True  #: run variable for while loop in run() function
        self.detecting = False  #: enables/disables feature detection

        #: initialize haar cascade face detection.. just that there is some image processing
        self.faceCascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
        print("VideoThread initialization finished")

    def run(self):
        """
        This Method reads the camera sensor and performs necessary image processing.
        Converts processed image to Qt's QImage class and emits Signal with QImage
        """
        while self.running:
            ret, frame = self.capture.read()        #: reads the camera sensor
            if ret:     #: If frame is returned successfully ret will be True else False.
                if self.detecting:      #: ImageProcessing can be dis/enabled via GUI
                    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)      #: Convert the frame to grayscale
                    faces = self.faceCascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)        #: Detect faces in the frame
                    #: Draw rectangles around the faces
                    for (x, y, w, h) in faces:
                        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
                #: Converts frame to rgb image and create QImage object
                rgbImage = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                h, w, _ = rgbImage.shape
                qImage = QImage(rgbImage.data, w, h, QImage.Format_RGB888)
                #: emit qImage for GUI as new image
                self.frameChanged.emit(qImage)
        self.capture.release()      #: If while loop is stopped, release camera sensor

    def quit(self):
        '''
        Necessary Implementation of inherited class to quit existing thread.
        '''
        self.running = False #: stops the while loop in run-method
        super().quit() #: calls quit-method from inherited class
        super().wait() #: wait until thread is quitted
        self.deleteLater() #: deletes thread object
        print("Camera thread closed")

    def start(self):
        '''
        Necessary Implementation of inherited class to quit existing thread.
        '''
        print("Starting camera thread...")
        self.running = True
        super().start()
        print("... done")

    def detect(self):
        '''
        enables/disables detection in run-method
        '''
        self.detecting = not self.detecting


class VideoPlayer(QQuickImageProvider):
    '''
    This class implements QQuickImageProvider class from PySide6 framework. It is necessary to pass captured
    and processed images to QML GUI.
    The signal imageChanged passes the QImage object to QQmlEngine to show it in GUI
    '''

    imageChanged = Signal(QImage)
    def __init__(self):
        '''
        calls the init-function from inherited class then creates objects from VideoThread class and an image field
        VideoThread and image are initialized with None
        '''
        super().__init__(QQmlImageProviderBase.Image, QQmlImageProviderBase.ForceAsynchronousImageLoading)
        self.videoThread = None
        self.VideoThread2 = None
        self.image = None
        self.image2 = None

    def requestImage(self, id, size, requestedSize):
        '''
        This function overrides requestImage from inherited class.
        :param id: necessary identifier to switch between images. Can be any value. Implemented as boolean value which is toggled
        everytime when imageChanged is emitted form a JavaScript - function in CameraApplicationMain.qml
        :param size:
        :param requestedSize:
        :return: returns QImage object in RGBA color format
        '''
        if self.image:
            img = self.image
        else:
            img = QImage(1280, 720, QImage.Format_RGBA8888)
            img.fill(Qt.black)
        return img

    @Slot(QImage)
    def updateImage(self, frame):
        '''
        Implements connection between VideoThread and VideoPlayer. If VideoThread emits a new image this Slot is called.
        stores emitted image in self.image and emits image to QQmlEngine
        :param frame: QImage which is emitted from run-method in VideoThread object.
        :return: this method returns nothing but emits signal to QQmlEngine
        '''
        print("new image in updateImage")
        self.image = frame
        self.imageChanged.emit(frame)

    @Slot()
    def start(self):
        '''
        Overrides start method of inherited class QQuickImageProvider. It is a Slot and called from QML Button of CameraAppMain.qml
        :return: this method returns nothing.
        '''
        print("Starting Video feed...")
        if not self.videoThread:
            self.videoThread = VideoThread(0)
            self.videoThread.frameChanged.connect(self.updateImage)
        self.videoThread.running = True
        self.videoThread.start()

    @Slot()
    def stop(self):
        '''
        Overrides stop method of inherited class QQuickImageProvider. It is a Slot and called from QML Button of CameraAppMain.qml
        :return: this method returns nothing
        '''
        print("Finishing Video feed.")
        if self.videoThread:
            self.videoThread.quit()
            self.videoThread = None
            print("Finished Video feed.")

    @Slot()
    def toggleDetection(self):
        '''
        Toggles detection field of VideoThread object. Enables / disables feature detection in VideoThread's run method.
        It is a Slot and called from QML Button of CameraAppMain.qml
        :return: This method returns nothing
        '''
        self.videoThread.detect()

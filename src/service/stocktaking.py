'''
This Python File implements the logic to recognize arUco markers.
class VideoThread inherits from QThread class. So image capture and image processing code is in seperated thread.
Processed images are provided to qml by using class videoPlayer which inherits from QQuickImageProvider.
'''

#import sys, os
#sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))

import cv2
import skimage.util
from PySide6.QtGui import QImage, QPixmap
from PySide6.QtCore import Signal, Slot, Qt, QThread, QObject
from PySide6.QtQuick import QQuickImageProvider
from PySide6.QtQml import QQmlImageProviderBase
from src.service.CameraService import ImageProvider
from src.service.CameraService import ImageProvider
from src.constants.Constants import Constants
from src.service.EventlogService import EventlogService
from skimage import transform
import numpy as np
import math
import matplotlib.pyplot as plt
from yaml import  load, Loader
import time
import asyncio
import re
class Stocktaker(QQuickImageProvider):
    allow_accept_stock = Signal(bool) # send with True to enable Accent button in stocktaking
    call_overview = Signal()
    transmit_data_to_plugin = Signal(int, int, bool, int, int) # row, col, pallet, cupa id, cupb id

    def __init__(self, eventLogService: None | EventlogService):
        super().__init__(QQmlImageProviderBase.Image, QQmlImageProviderBase.ForceAsynchronousImageLoading)
        self.cameraService = ImageProvider()
        self.cameraService.imageSignal.connect(self.handle_image_signal)
        self.constants = Constants()
        self.eventlogService = eventLogService
        self.raw_image = []
        self.image = []
        self.sections = []
        self.cupsA = []
        self.pallets = []
        self.gripper_id = 0
        self.detected_cups = []
        self.stockmodel = None
        self.submitPalletImage = Signal(QImage)
        self.submitCupImage = Signal(QImage)
        self.submitResultMatrix = Signal(list)
        self.call_overview.connect(self.handle_overview_call)
    
    def handle_overview_call(self):
        self.evaluate_storagecell_cam()

    def handle_image_signal(self, image: np.ndarray):
        print(f"Image received {image}")
        self.image = image.copy()

    def __del__(self):
        print("Stocktaker: Destructor called")
    
    def set_stockmodel(self, stockmodel):
        self.stockmodel = stockmodel

    @Slot(int, int, result=QImage)
    def getSlotA(self, row: int, col: int) -> QImage:
        print("called slotA")
        idx = 6*col + row
        print(f"idx: {idx}")
        if idx == -7:
            return QImage()
        elif idx >= len(self.cupsA):
            return QImage()
        elif self.cupsA[idx] is not None:
            print(f"image: {image}")
            image = QImage(self.cupsA[idx])
            return image
        else:
            return QImage()

    def requestImage(self, id:str, size, requestedSize)->QImage:
        print(f"called an Image {id}, {size}, {requestedSize}")
        strings = id.split('_')
        row, col, slot = int(strings[0]), int(strings[1]), strings[2][0]
        idx = 6*row + col
        print(f"idx: {idx}")
        if(slot =="Pallet"):
            print(f"imagedata: {self.pallets[idx]}")
            image = QImage(self.pallets[idx])
            print(f"pallet image: {image}")
            return image
        elif slot == 'A' and idx < len(self.cupsA) :
            print(f"imagedata: {self.cupsA[idx]}")
            image = QImage(self.cupsA[idx]) if self.cupsA[idx] is not None else QImage()
            print(f"image: {image}")
            return image
        else:
            return QImage()

    def requestPixmap(self, id, size, requestedSize)->QPixmap:
        pass
        
    @Slot(int, int)
    def getSlotB(self, row:int, col: int) ->QImage:
        print("called slotB")
        idx = 6*col + row
        if self.cupsA[idx] is not None:
            image = QImage(self.cupsA[idx])
            return image
        else:
            return QImage()

    @Slot(int, int)
    def getPallet(self, row: int, col: int)->QImage:
        print("called getPallet")
        idx = 6*col + row
        if self.pallets[idx] is not None:
            image = QImage(self.pallets[idx])
            return image
        else:
            return QImage()
    
    @Slot()
    def callOverviewCam(self):
        self.call_overview.emit()
        
    @Slot()
    def evaluate_storagecell_cam(self):
        """
        Public Method. Obtains image from camera via CameraServic.Imageprovider, performs arUco detection.
        Slices the image into sub images related to Storage location.
        Afterwards signals with processed image is emitted to QML Engine.
        Before every step a message is emitted to EventlogService in main screen
        """

        self.detected_cups = []
        self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Start obtaining image from camera...")
        self.cameraService.get_image(0)
        self.raw_image = np.copy(self.image)
        #plt.imshow(self.image, cmap= 'gray')
        #plt.show()
        waiting = 0
        while waiting < 1000:
            if self.image is None:
                time.sleep(0.01)
                waiting +=1
            else: break

        if self.image is None:
            self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "No image obtained from camera! Stocktaking aborted.")
            return
        else:
            self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Image obtained. Start arUco recognition...")
        self.image = self._automatic_brightness_and_contrast(
            clip_hist_percent = 1,
            image=self.image)
        parameters = self._loadDetectorConf(
            imgtype='binary',
            area=0,
            type= 'cell')
        markers, self.image = self._detect_markers(parameters= parameters)
        self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "arUco recognition finished. Start image transformation...")
        shelf_corners, shelf_ids = self._get_shelf_markers(markers)
        x_corners, y_corners, y_min, y_max, ret = self._get_transformation_corners(shelf_corners)
        if ret:
            image, tform3 = self._transform_image( self.image, x_corners, y_corners, y_min, y_max)
            self.image = image
            image, tform3 = self._transform_image(self.raw_image, x_corners, y_corners, y_min, y_max)
            self.raw_image = image
            self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Image transformation finished. Start detecting slicing...")
        else:
            self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Not enough shelf markers found!\n"
                                                                                   f"x_corners: {x_corners}\n"
                                                                                   f"y_corners: {y_corners}\n"
                                                                                   "Possible Reason: Markers are not visible die to camera position/angle change.\n"
                                                                                   "Possiblee Solution: Adjust image slice boundaries in '_get_transformation_corners' method.")
            return
        self._slice_storage(self.raw_image)
        self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Slicing finished. Start marker detection in sections...")
        print("Detection in pallets:")
        for i, pallet in enumerate(self.pallets):
            parameters = self.select_marker_parameters(
                i= i,
                imtype= 'gray',
                target= 'pallet')
            self.pallets[i] = self._automatic_brightness_and_contrast(
                image= pallet,
                clip_hist_percent=0.5)
            markers, self.pallets[i] = self._detect_markers(
                section=pallet,
                section_id=i,
                parameters= parameters)
            pallets, ids = self._get_pallet_markers(markers)
            self.pallets[i] = self._draw_markers(pallets, ids, (255,0,0), pallet, i)
            cv2.imwrite(f"temp/pallet_{i + 1}.png", pallet)
        self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Pallets finished. Start marker detection in cups...")
        print("Detection in cups:")
        for i, cup in enumerate(self.cupsA):
            parameters= self.select_marker_parameters(
                i= i,
                imtype= 'gray',
                target= 'cup')
            self.cupsA[i] = self._automatic_brightness_and_contrast(
                image= cup,
                clip_hist_percent=1)
            markers, self.cupsA[i] = self._detect_markers(
                section=cup,
                section_id=i,
                cups=True,
                parameters=parameters)
            cups, ids = self._get_cup_markers(markers)
            self.cupsA[i] = self._draw_markers(cups, ids, (255,255,255), cup, i)
            cv2.imwrite(f"temp/cup{i + 1}.png", cup)
        print(f"cups: {self.detected_cups}")
        print(f"pallets: {self.pallets}")
        self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Cups finished. Start calculating result matrix...")
        self.calculate_result_matrix()
        self.eventlogService.write_event("Stocktaker.evaluate_storagecell_cam", "Result matrix calculated. Process finished.")

    @Slot()
    def evaluate_gripper(self):
        """
        Public Method. Obtains image from CameraService.Imageprovider.
        Since marker should take a significant area of the image, no rectification is performed.
        Performs arUco detection after brightness and color adjustment.
        processed image is kept in gripper_image property.
        """
        self.detected_cups = []
        self.eventlogService.write_event("Stocktaker.evaluate_gripper", "Start obtaining image from camera...")
        try:
            self.cameraService.get_image(2)
        except Exception as e:
            self.eventlogService.write_event("Stocktaker.evaluate_gripper", f"Error while obtaining image from camera: {str(e)}")
            return
        if self.image is None:
            self.eventlogService.write_event("Stocktaker.evaluate_gripper", "No image obtained from camera! Stocktaking aborted.")
            return
        else:
            self.eventlogService.write_event("Stocktaker.evaluate_gripper", "Image obtained. Start arUco recognition...")
            markers, image = self._detect_markers(section=self.image, cups=True)
            if markers[0][0] is not None:
                print("marker detcted")
                for i, marker in enumerate(markers[0]):
                    self._draw_markers(markers[1][i], markers[0][i], color= (0,255,0))
        cv2.imwrite("espImage.png", self.image)

    def select_marker_parameters(self, i:int, imtype: str, target:str):
        """
        Selects detector settings, from locating integer and string
        """
        if i in (0, 1, 2, 6, 7, 8):
            parameters = self._loadDetectorConf(imgtype=imtype, area=1, type=target)
        elif i in (3, 4, 5, 9, 10, 11):
            parameters = self._loadDetectorConf(imgtype=imtype, area=2, type=target)
        elif i in (12, 13, 14):
            parameters = self._loadDetectorConf(imgtype=imtype, area=3, type=target)
        elif i in (15, 16, 17):
            parameters = self._loadDetectorConf(imgtype=imtype, area=4, type=target)
        else:
            parameters = cv2.aruco.DetectorParameters()
        return parameters
    
    def calculate_result_matrix(self):
        """
        Public Method. Calculates the result matrix based on detected markers.
        Emits self.submitResultMatrix signal with result matrix.
        """
        # TODO: Get pallet data

        # TODO: Get cup data
        # TODO: Calclulate 6x6x2 result matrix
        # TODO: reformat result matrix to make it qml accessible
        # TODO: emit signal
    
    @Slot(int)
    def emit_pallet_cup_images(self, storage_cell):
        pass
        # TODO get images from storage_cell number
        # TODO emit images
    
    @Slot()
    def emit_cell_image(self):
        pass
        # TODO get image from cell
        # TODO emit image
    
    @Slot()
    def _refactor_corners(self, corners, ids):
        """
        Private method to refactor aruco marker corners.
        creates a list with id and 4 corners of the markers.

        :param corners: result of cv2.aruco.detectMarker's cornerlist
        :type corners: list
        :param ids: result of cv2.aruco.detectMarker's id list
        :return: formatted, combined list of marker ids and corners.
        :rtype: list of dictionaries
        """
        markers = [[],[]]
        if corners is not None:
            markers[0].append(ids)
        if ids is not None:
            markers[1].append(corners)
        return markers
    
    def _get_shelf_markers(self, markers):
        """
        Private method to extract shelf-markers from marker list
        :param markers: formatted, combined list of markers with id
        :type markers: list
        :return: formatted, combined list of shelfcorner markers.
        :rtype: list
        """
        assert markers is not None
        shelf_corners = []
        shelf_ids = []
        ids = markers[0]
        ids = ids[0]
        corners = markers[1]
        corners = corners[0]
        for i, id in enumerate(ids):
            if ids[i] == self.constants.SHELF_ARUCO:
                shelf_corners.append(corners[i])
                shelf_ids.append(id)
        return shelf_corners, shelf_ids
    
    def _get_pallet_markers(self, markers):
        """
        Private method to extract all pallet markers from marker list.
        :param markers: formatted and combined list of marker corners and ids
        :type markers: list
        :return: formatted, combined list of pallet markers
        :rtype: list
        """
        assert markers is not None
        pallet_markers = []
        pallet_ids = []
        ids = markers[0]
        corners = markers[1]
        if (len(corners)>0) and (len(ids)>0):
            corners = corners[0]
            ids = ids[0]
            for i, id in enumerate(ids):
                if ids[i] == self.constants.PALLET_ARUCO:
                    pallet_markers.append(corners[i])
                    pallet_ids.append(id)
        return pallet_markers, pallet_ids
    
    def _get_cup_markers(self, markers):
        """
        Private method to extract all cup markers from marker list.
        :param markers: formatted and combined list of marker corners and ids
        :type markers: list
        :return: formatted, combined list of cup markers
        :rtype: list
        """
        assert markers is not None
        cup_markers = []
        cup_ids = []
        ids = markers[0]
        corners = markers[1]
        if (len(corners)>0) and (len(ids)>0):
            corners = corners[0]
            ids = ids[0]
            corners = corners[0]
            for i, id in enumerate(ids):
                if ids[i] == self.constants.CUP_ARUCO.any():
                    cup_markers.append(corners[i])
                    cup_ids.append(id)
        return cup_markers, cup_ids
    
    def _get_storage_element_markers(self, markers):
        """
        Private method to extract all markers related to a storage from marker list.
        :param markers: formatted and combined list of marker corners and ids
        :type markers: list
        :return: formatted, combined list of storage markers
        :rtype: list
        """
        assert markers is not None
        storageelement_markers = []
        storageelement_ids = []
        ids = markers[0]
        ids = ids[0]
        corners = markers[1]
        corners = corners[0]

        for i, id in enumerate(ids):
            if ids[i] == self.constants.STORAGE_ELEMENT_ARUCO.any():
                storageelement_markers.append(corners[i])
                storageelement_ids.append(id)
        return storageelement_markers, storageelement_ids
    
    def _get_transformation_corners(self, shelf_markers):
        """
        Private method, calculates the inner shelf markers and a resulting rectangle corners.
        :param shelf_markers: formatted, combined list of shelf markers and ids
        :type shelf_markers: list
        :return: two lists with x and y pixel coordinates of resulting rectangle.
        :rtype: list
        """
        assert shelf_markers is not None
        x_corners = [0, 0, 0, 0]
        y_corners = [0, 0, 0, 0]
        y_min = self.image.shape[0]
        y_max = 0
        shelf_markers = np.asarray(shelf_markers)
        for i in range(4):
            for shelfcorner in shelf_markers:
                shelfcorner = np.asarray(shelfcorner)
                shelfcorner = shelfcorner[0]
                x_vals = [x[0] for x in shelfcorner]
                y_vals = [y[1] for y in shelfcorner]
                x = min(x_vals) if i in (0, 3) else max(x_vals)
                y = min(y_vals) if i in (0, 1) else max(y_vals)
                if i == 0 and x < 1600:
                    if y < 1000:
                        x_corners[i] = x
                        y_corners[i] = y
                elif i == 1 and x > 3000:
                    if 900 < y < 1500:
                        x_corners[i] = x
                        y_corners[i] = y
                elif i == 2 and x > 3000:
                    if 1500 < y < 2000:
                        x_corners[i] = x
                        y_corners[i] = y
                elif i == 3 and x < 1500:
                    if y > 800:
                        x_corners[i] = x
                        y_corners[i] = y
                if y < y_min:
                    y_min = y
                if y > y_max:
                    y_max = y
        print("x_corners: ",x_corners)
        print("y_corners: ", y_corners)
        if min(x_corners) >0 and min(y_corners) > 0:
            return x_corners, y_corners, y_min, y_max, True
        else:
            return x_corners, y_corners, y_min, y_max, False
    
    def _transform_image(self,im_source, x_corners, y_corners, y_glob_min, y_glob_max):
        """
        Private method. uses skimage lib to rectify image using submitted corners.
        :param x_corners: list of x- coordinates of rectangle
        :type x_corners: list
        :param y_corners: list of y- coordinates of rectangle
        :type y_corners:list
        :return: warped image and transformationmatrix.
        :rtype: array
        """
        y_glob_min = int(y_glob_min)
        y_glob_max = int(y_glob_max)
        dx = max(x_corners) - min(x_corners)
        dy = max(y_corners) - min(y_corners)
        hx = math.sqrt(dx ** 2 + dy ** 2)
        dh = hx/105
        hy = dh*31
        x_min = 0.5*dx
        x_max = x_min + hx
        y_min = 1.2*dy
        y_max = y_min + hy
        src = np.array([[x_min, y_min], [x_max, y_min], [x_max, y_max], [x_min, y_max]])
        dst = np.column_stack((x_corners, y_corners))
        tform3 = transform.ProjectiveTransform()
        tform3.estimate(dst= dst, src= src)
        image = transform.warp(im_source, tform3, output_shape=(im_source.shape[0], im_source.shape[1]))
        image =  skimage.util.img_as_ubyte(image)
        # image = image[950: 3000, 1200:3150]
        # print(f"calculated global boundaries: y: {y_glob_min, y_glob_max}, x: {x_min, x_max}")
        x_min = int(x_min)
        x_max = int(x_max)
        image = image[y_glob_min + 550: y_glob_max + 520, x_min + 300 : x_max - 180]
        cv2.imwrite("temp/transformed.png", image)
        #plt.imshow(image, cmap= 'gray')
        #plt.title("transformed image")
        #plt.show(cmap= 'gray')
        return image, tform3
    
    def _detect_markers(self, parameters: None | cv2.aruco.DetectorParameters = None, section = None, section_id= 0, cups = False):
        """
        uses cv2's detectMarkers()  to recognize arUco marker.
        :return: list of markers
        :rtype: list
        """
        parameters : cv2.aruco.DetectorParameters = cv2.aruco.DetectorParameters() if parameters is None else parameters

        assert self.image is not None
        if type(section) is type(None):
            self.image = cv2.cvtColor(self.image, cv2.COLOR_RGB2GRAY) if self.image.ndim == 3 else self.image
            (corners, ids, rejected) = cv2.aruco.detectMarkers(self.image, self.constants.ARUCODICT, parameters= parameters )
            markers = self._refactor_corners(corners, ids)
            # print(f"detection: {markers[0]}, {len(markers[1])}")
            return markers, self.image
        else:
            section = cv2.cvtColor(section, cv2.COLOR_RGB2GRAY) if section.ndim == 3 else section
            (corners, ids, rejected) = cv2.aruco.detectMarkers(section, self.constants.ARUCODICT, parameters= parameters )
            markers = self._refactor_corners(corners, ids)
            marker_content = markers[0][0]
            if marker_content is not None:
                marker_content = marker_content[0][0]
            if cups:
                self.detected_cups.append(marker_content)
            print(f"detection id {section_id+1}: {marker_content}, {len(markers[1])}")
            return markers, section
    
    def _draw_markers(self, corners, ids, color, section = None, section_id=0):
        """
        draw given markers in given color.
        There is no python documentation for corner structure. From C++ Documentation: For N corners must be std::vector<std::vector<cv::Point2f>> which results in
        Nx4 dims. The order of marker corners must be clockwise.
        :param markers: list of marker corners that shall be drawn
        :param ids: list of marker ids that shall be drawn
        :type markers: list
        :type ids: list
        :param color: tuple of RGB color
        :type color: tuple (r,g,b) of 0..255
        """
        if len(corners) > 0:
            corners = [x[0] for x in corners]
            for i, marker in enumerate(corners):
                if type(section) == type(None):
                    self.image = cv2.rectangle(img= self.image, pt1= (int(marker[0][0]), int(marker[0][1])), pt2= (int(marker[2][0]), int(marker[2][1])), color= color, thickness= 30)
                    return self.image
                else:
                    section = cv2.rectangle(img= section, pt1= (int(marker[0][0]), int(marker[0][1])), pt2= (int(marker[2][0]), int(marker[2][1])), color= color, thickness= 30)
                    return section
    
    def _slice_storage(self, image):
        """
        Private Method. Slices the image in storage elements.
        divides self.image into 18 sections (three in y-direction, 6 in x-direction)
        :return: List of image slices
        :rtype: list
        """
        sections = []
        cups = []
        pallets = []
        x_dim = image.shape[1]
        y_dim = image.shape[0]
        # print(f"x: {x_dim}, y: {y_dim}")
        for y in range(3):
            for x in range(6):
                y_min = int(y*y_dim/3)
                y_max = int((y+1)*y_dim/3) if (y+1)*y_dim/3 <= y_dim else int(y_dim)
                x_min = int(x*x_dim/6)
                x_max = int((x+1)*x_dim/6) if ((x+1)*x_dim/6) <= x_dim else int(x_dim)
                section = image[y_min: y_max, x_min : x_max]
                # threshold = 190
                # section = cv2.threshold(section, threshold, 255, cv2.THRESH_BINARY)[1]
                cup_area = section [int(section.shape[0]*0.2) : int(section.shape[0]*0.5), 0:int(section.shape[1])]
                pallet_area =section [int(section.shape[0]*0.6) : int(section.shape[0]*0.9), 0:int(section.shape[1])]
                sections.append(section)
                cups.append(cup_area)
                pallets.append(pallet_area)

        self.sections = sections
        self.cupsA = cups
        self.pallets = pallets
    
    def _automatic_brightness_and_contrast(self,image,  clip_hist_percent):
        """
        Autoadjusting color and brightness for better marker detection.
        Source: Stackoverflow
        https://stackoverflow.com/questions/56905592/automatic-contrast-and-brightness-adjustment-of-a-color-photo-of-a-sheet-of-pape
        """

        gray = image

        # Calculate grayscale histogram
        hist = cv2.calcHist(gray, [0], None, [256], [0,256])
        hist_size = len(hist)

        # Calculate cumulativ distribution from the histogram
        accumulator = []
        accumulator.append(float(hist[0]))
        for index in range(1, hist_size):
            accumulator.append(accumulator[index-1]+float(hist[index]))

        # Locate points to clip
        maximum = accumulator[-1]
        clip_hist_percent *= (maximum/100)
        clip_hist_percent /=2

        # Locate left cut
        minimum_gray = 0

        while accumulator[minimum_gray] < clip_hist_percent:
            minimum_gray +=1

        # Locate right cut
        maximum_gray = hist_size-1
        while accumulator[maximum_gray] >= (maximum - clip_hist_percent):
            maximum_gray -= 1

        # Calculate alpha and beta values
        if maximum_gray -minimum_gray !=0:
            alpha = 255/(maximum_gray - minimum_gray)
            beta = -minimum_gray * alpha

            # Calculate new histogram with desired range and show histogram
            # new_hist = cv2.calcHist([gray], [0], None, [256], [minimum_gray, maximum_gray])
            # plt.plot(hist)
            # plt.plot(new_hist)
            # plt.xlim([0, 256])
            # plt.show()

            # print(alpha, beta)
            img = cv2.convertScaleAbs(gray, alpha= alpha, beta=beta)
            cv2.imwrite("temp/processed_before_detection.png", img)
            #plt.imshow(img, cmap= 'gray')
            #plt.show()
            return img
        else:
            return gray
    
    def _loadDetectorConf(self, imgtype: str, area: int, type: str) -> cv2.aruco.DetectorParameters:
        """
        Loads the parameter configuration for marker detection from a yaml file which might has been fitted by genetic algorithm.
        Returns standard parameters in case yaml file could not be found.
        :param imgtype: 'gray' for gray-image-configuration, 'binary' for binary-image-configuration
        :type imgtype: str
        :param area: 0= global, 1= upper left, 2= upper right, 3 = lower right, 4 = lower left
        :type area: int
        :param type: 'cup' for cup detection parameters, 'pallet' for pallet detection
        :type type: str
        :returns parameters: instance of cv2.aruco.DetectorParameters
        """
        parameters = cv2.aruco.DetectorParameters()
        # calculate field from arguments
        fieldname = "ARUCO_DETECTOR_"
        fieldname += "GRAY_" if imgtype == 'gray' else "BINARY_"
        fieldname += "PALLETS_" if type == 'pallet' else 'CUPS_'
        fieldname += str(area)
        filename = getattr(self.constants, fieldname)
        try:
            with open(filename, "r") as file:
                read = load(file, Loader=Loader)
                for key in read.keys():
                    value = read[key]
                    try:
                        setattr(parameters, key, value)
                    except Exception as ex:
                        self.eventlogService.write_event("Stocktaker._loadDetectorConf", f"Could not set detector attribute {key}, Exceptio: {ex}")
        except FileNotFoundError as e:
            self.eventlogService.write_event("Stocktaker._loadDetectorConf", f"Exception while opening configuration file: {e}")
        return parameters

if __name__ == '__main__':
    stocktaker = Stocktaker()
    cups = []
    for i in range(5):
        stocktaker.evaluate_storagecell_cam()
        if i == 0:
            cups = stocktaker.detected_cups
        else:
            if len(stocktaker.detected_cups) >=1:
                cups = [stocktaker.detected_cups[j] if stocktaker.detected_cups[j] is not None else cups[j] for j in
                        range(len(cups))]
            else:
                i-=1
    cupnames = ["L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9", "L10", "L11", "L12", "L13", "L14", "L15", "L16",
            "L17", "L18"]

    # Define the number of rows and columns
    num_rows = 3
    num_columns = 6

    # Initialize a variable to store the formatted string
    formatted_matrix = ""

    # Loop through rows and columns to build the matrix
    for i in range(num_rows):
        row_elements = []
        for j in range(num_columns):
            index = i * num_columns + j
            if index < len(cupnames):
                row_elements.append(f"L{index + 1} = {cups[index]}")
        formatted_row = " | ".join(row_elements)  # Join row elements with " | " separator
        formatted_matrix += f"|{formatted_row}|\n"

    # Print the formatted matrix
    print(formatted_matrix)

'''
This Python File implements the logic to recognize arUco markers.
class VideoThread inherits from QThread class. So image capture and image processing code is in seperated thread.
Processed images are provided to qml by using class videoPlayer which inherits from QQuickImageProvider.
'''

#import sys, os
#sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))

import cv2
import skimage.util
from PySide6.QtGui import QImage
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





class Stocktaker(QQuickImageProvider):

    def __init__(self):
        super().__init__(QQmlImageProviderBase.Image, QQmlImageProviderBase.ForceAsynchronousImageLoading)
        self.cameraService = ImageProvider()
        self.constants = Constants()
        self.eventlogService = EventlogService()
        self.image = None
        self.sections = None

    def __del__(self):
        print("Stocktaker: Destructor called")

    def evaluate_storagecell_cam(self):
        """
        Public Method. Obtains image from CameraServic.Imageprovider, performs 4-point rectification and arUco detection.
        Slices the image into subimages related to Storage location.
        Afterwards signals with processed image is emitted to QML Engine.
        Before every step a message is emitted to EventlogService in main screen
        """
        self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "Start obtaining image from camera...")
        self.image = self.cameraService.get_image(0)
        plt.imshow(self.image, cmap= 'gray')
        plt.show()
        if self.image is None:
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "No image obtained from camera! Stocktaking aborted.")
            return
        else:
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "Image obtained. Start arUco recognition...")
        self.image = self._automatic_brightness_and_contrast(clip_hist_percent = 1, image=self.image)
        markers = self._detect_markers()
        # markers: [ [[[0],[0]][[([[[3175]
        self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "arUco recognition finished. Start image transformation...")
        shelf_corners, shelf_ids = self._get_shelf_markers(markers)
        x_corners, y_corners, ret = self._get_transformation_corners(shelf_corners)
        if ret:
            image, tform3 = self._transform_image( x_corners, y_corners)
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam",
                                            "Image transformation finished. Start detecting arUco markers...")
            self.image = image
        else:
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "Not enough shelf markers found!\n"
                                                                                   f"x_corners: {x_corners}\n"
                                                                                   f"y_corners: {y_corners}\n"
                                                                                   "Possible Reason: Markers are not visible die to camera position/angle change.\n"
                                                                                   "Possiblee Solution: Adjust image slice boundaries in '_get_transformation_corners' method.")
            return
        markers = self._detect_markers()
        shelf, shelf_ids = self._get_shelf_markers(markers)
        pallets, pallet_ids = self._get_pallet_markers(markers)
        cups, cup_ids = self._get_cup_markers(markers)
        storage, storage_ids = self._get_storage_element_markers(markers)
        self._draw_markers(shelf, shelf_ids, color = (255, 0, 0))
        self._draw_markers(pallets, pallet_ids, color= (255, 0, 0))
        self._draw_markers(cups, shelf_ids,color= (255, 0, 0))
        self._draw_markers(storage, storage_ids, color=(255, 0, 0))
        plt.imshow(self.image)
        cv2.imwrite("withdetected_markers.png", self.image)
        plt.show()
        self._slice_storage()
        for i, section in enumerate(self.sections):
            self.sections[i] = self._automatic_brightness_and_contrast(image=section, clip_hist_percent=1)
            markers = self._detect_markers(section, i)
            print(markers)
            pallets, pallet_ids = self._get_pallet_markers(markers)
            self._draw_markers(pallets, pallet_ids, (255, 0, 0), section, i)
            plt.imshow(section, cmap= 'gray')
            plt.show()
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
        ids = ids[0]
        corners = markers[1]
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
        shelf_markers = np.asarray(shelf_markers)
        # shelf_markers = shelf_markers[0]
        # print(shelf_markers)
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
        print("x_corners: ",x_corners)
        print("y_corners: ", y_corners)
        if min(x_corners) >0 and min(y_corners) > 0:
            # self.image = cv2.rectangle(self.image, (int(min(x_corners)), int(min(y_corners))),
            #               (int(max(x_corners)), int(max(y_corners))), (255, 0, 0), thickness=15)
            # plt.imshow(self.image, cmap= 'gray')
            # plt.show()
            return x_corners, y_corners, True
        else:
            return x_corners, y_corners, False

    def _transform_image(self, x_corners, y_corners):
        """
        Private method. uses sci-image lib to rectify image using submitted corners.
        :param x_corners: list of x- coordinates of rectangle
        :type x_corners: list
        :param y_corners: list of y- coordinates of rectangle
        :type y_corners:list
        :return: warped image and transformationmatrix.
        :rtype: array
        """
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
        image = transform.warp(self.image, tform3, output_shape=(self.image.shape[0], self.image.shape[1]))
        image =  skimage.util.img_as_ubyte(image)
        print(image.shape)
        image = image[950: 3000, 1200:3150]
        cv2.imwrite("transformed.png", image)
        plt.imshow(image, cmap= 'gray')
        plt.title("transformed image")
        plt.show(cmap= 'gray')
        return image, tform3

    def _detect_markers(self, section = None, section_id= 0):
        """
        uses cv2's detectMarkers()  to recognize arUco marker.
        :return: list of markers
        :rtype: list
        """
        assert self.image is not None
        if type(section) is type(None):
            self.image = cv2.cvtColor(self.image, cv2.COLOR_RGB2GRAY) if self.image.ndim == 3 else self.image
            (corners, ids, rejected) = cv2.aruco.detectMarkers(self.image, self.constants.ARUCODICT, )
            markers = self._refactor_corners(corners, ids)
            return markers
        else:
            self.sections[section_id] = cv2.cvtColor(self.sections[section_id], cv2.COLOR_RGB2GRAY) if self.sections[section_id].ndim == 3 else self.sections[section_id]
            (corners, ids, rejected) = cv2.aruco.detectMarkers(self.sections[section_id], self.constants.ARUCODICT, )
            markers = self._refactor_corners(corners, ids)
            return markers

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
                else:
                    self.sections[section_id] = cv2.rectangle(img= section, pt1= (int(marker[0][0]), int(marker[0][1])), pt2= (int(marker[2][0]), int(marker[2][1])), color= color, thickness= 30)

    def _slice_storage(self):
        """
        Private Method. Slices the image in storage elements.
        divides self.image into 18 sections (three in y-direction, 6 in x-direction)
        :return: List of image slices
        :rtype: list
        """
        image = self.image
        sections = []
        x_dim = image.shape[1]
        y_dim = image.shape[0]
        print(f"x: {x_dim}, y: {y_dim}")
        for y in range(3):
            for x in range(6):
                y_min = int(y*y_dim/3)
                y_max = int((y+1)*y_dim/3) if (y+1)*y_dim/3 <= y_dim else int(y_dim)
                x_min = int(x*x_dim/6)
                x_max = int((x+1)*x_dim/6) if ((x+1)*x_dim/6) <= x_dim else int(x_dim)
                sections.append(image[y_min: y_max, x_min : x_max])

        self.sections = sections
        print(len(self.sections))




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
        alpha = 255/(maximum_gray - minimum_gray)
        beta = -minimum_gray * alpha

        # Calculate new histogram with desired range and show histogram
        # new_hist = cv2.calcHist([gray], [0], None, [256], [minimum_gray, maximum_gray])
        # plt.plot(hist)
        # plt.plot(new_hist)
        # plt.xlim([0, 256])
        # plt.show()

        print(alpha, beta)
        img = cv2.convertScaleAbs(gray, alpha= alpha, beta=beta)
        cv2.imwrite("processed_before_detection.png", img)
        #plt.imshow(img, cmap= 'gray')
        #plt.show()
        return img



if __name__ == '__main__':
    stocktaker = Stocktaker()
    stocktaker.evaluate_storagecell_cam()
    plt.imshow(stocktaker.image, cmap= 'gray')
    plt.show()
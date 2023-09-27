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
from src.service.CameraService import CameraService
from src.constants.Constants import Constants
from src.service.EventlogService import EventlogService
from skimage import transform
import math

class Stocktaker(QObject):

    def __init__(self):
        self.cameraService = CameraService()
        self.constants = Constants()
        self.eventlogService = EventlogService()

    def __del__(self):
        print("Stocktaker: Destructor called")

    def evaluate_storagecell_cam(self):
        self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "Start obtaining image from camera...")
        image = self.cameraService.getImage(0)
        if image is None:
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "No image obtained from camera! Stocktaking aborted.")
            return
        else:
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "Image obtained. Start arUco recognition...")
        (corners, ids, rejected) = cv2.aruco.detectMarkers(image, self.constants.ARUCODICT, )
        self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "arUco recognition finished. Start image transformation...")
        markers = self._refactor_corners(corners, ids)
        shelf_markers = self._get_shelf_markers(markers)
        x_corners, y_corners, ret = self._get_transformation_corners(shelf_markers)
        if ret:
            image, tform3 = self._transform_image(image, x_corners, y_corners)
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam",
                                            "Image transformation finished. Start storage slicing...")
        else:
            self.eventlogService.writeEvent("Stocktaker.evaluate_storagecell_cam", "Not enough shelf markers found!\n"
                                            "Possible Reason: Markers are not visible die to camera position/angle change.\n"
                                            "Possiblee Solution: Adjust image slice boundaries in '_get_transformation_corners' method.")
            return



    def _refactor_corners(self, corners, ids,):
        assert corners is not None
        assert ids is not None
        markers = []
        for i, id in enumerate(ids):
            marker = {}
            marker["id"] = id
            for j in range(4):
                marker["x" + str(j)] = corners[i][0][j][0]
                marker["y" + str(j)] = corners[i][0][j][1]
            markers.append(marker)
        return markers

    def _get_shelf_markers(self, markers):
        assert markers is not None
        shelf_markers = []
        for marker in markers:
            if marker["id"] == 0:
                shelf_markers.append(marker)
        return shelf_markers

    def _get_transformation_corners(self, shelf_markers):
        assert shelf_markers is not None
        x_corners = [0, 0, 0, 0]
        y_corners = [0, 0, 0, 0]
        for shelfcorner in shelf_corners:
            for i in range(4):
                x = min(shelfcorner[1][0][0][0], shelfcorner[1][0][1][0]) if i in (0, 3) else max(
                    shelfcorner[1][0][0][0], shelfcorner[1][0][1][0])
                y = min(shelfcorner[1][0][0][1], shelfcorner[1][0][1][1]) if i in (0, 1) else max(
                    shelfcorner[1][0][0][1], shelfcorner[1][0][1][1])
                if i == 0 and x < 1400:
                    if y < 800:
                        x_corners[i] = x
                        y_corners[i] = y
                elif i == 1 and x > 3000:
                    if 500 < y > 1200:
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
        if min(x_corners) >0 and min(y_corners) > 0:
            return x_corners, y_corners, True
        else:
            return x_corners, y_corners, False

    def _transform_image(self, image, x_corners, y_corners):
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
        tform3.estimate(src, dst)
        image = transform.warp(image, tform3, output_shape=(image.shape[0], image.shape[1]))
        return image, tform3

    def _transform_markercoords(self, marker, tform3):
        assert marker is not None
        assert tform3 is not None
        marker_list = [[marker["x0"], marker["y0"]], [marker["x1"], marker["y1"]], [marker["x2"], marker["y2"]], [marker["x3"], marker["y3"]]]
        marker_corrected = transform.matrix_transform(marker_list, tform3.params)
        
        return marker

    def _slice_storage(self, image):
        pass
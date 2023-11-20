"""
This file provides all constant URL data.
"""
from pathlib import Path
import cv2
import numpy as np
class Constants:
    def __init__(self):
        # self.PRODUCTLIST = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "Produkte.db"
        self.PRODUCTLIST = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "Products.yaml"
        self.STORAGEDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "StorageData.yaml"
        self.STORAGEDATAWRITE = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "StorageData.yaml"
        self.COMMISSDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "Commissdata.db"
        self.CAMAPP_QML = "../cameraApplication/qml/CameraAppMain.qml"
        #self.COMMISSIONDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "CommissionData.db"
        self.COMMISSIONDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "CommissionData.yaml"
        self.PRODUCTLISTAPP_QML = "../src/view/ProductList.qml"
        self.PREFERENCES = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "Preferences.yaml"
        #self.PREFERENCES = "src/data/Preferences.yaml"
        self.RFID_DATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "RfidData.yaml"
        self.ARUCODICT = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)
        self.SHELF_ARUCO = 0
        self.PALLET_ARUCO = 1
        self.CUP_ARUCO = np.arange(5, 45, 1)
        self.STORAGE_ELEMENT_ARUCO = np.arange(45, 65, 1)
        #self.ARUCO_DETECTOR_GRAY_CELL = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayCell.yaml"
        self.ARUCO_DETECTOR_GRAY_CELL = Path(__file__).resolve().parent.parent / "data" / "Cell.yaml"
        self.ARUCO_DETECTOR_BINARY_CELL = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryCell.yaml"
        self.ARUCO_DETECTOR_BINARY_CUPS_0 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryCups0.yaml"
        self.ARUCO_DETECTOR_BINARY_CUPS_1 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryCups1.yaml"
        self.ARUCO_DETECTOR_BINARY_CUPS_2 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryCups2.yaml"
        self.ARUCO_DETECTOR_BINARY_CUPS_3 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryCups3.yaml"
        self.ARUCO_DETECTOR_BINARY_CUPS_4 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryCups4.yaml"
        self.ARUCO_DETECTOR_BINARY_CUPS_5 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryCups5.yaml"
        self.ARUCO_DETECTOR_BINARY_PALLETS_0 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryPallets0.yaml"
        self.ARUCO_DETECTOR_BINARY_PALLETS_1 = Path(__file__).resolve().parent.parent/ "data" / "ConfDetectionBinaryPallets1.yaml"
        self.ARUCO_DETECTOR_BINARY_PALLETS_2 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryPallets2.yaml"
        self.ARUCO_DETECTOR_BINARY_PALLETS_3 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryPallets3.yaml"
        self.ARUCO_DETECTOR_BINARY_PALLETS_4 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryPallets4.yaml"
        self.ARUCO_DETECTOR_BINARY_PALLETS_5 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionBinaryPallets5.yaml"
        self.ARUCO_DETECTOR_GRAY_CUPS_0 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayCups0.yaml"
        self.ARUCO_DETECTOR_GRAY_CUPS_1 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayCups1.yaml"
        self.ARUCO_DETECTOR_GRAY_CUPS_2 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayCups2.yaml"
        self.ARUCO_DETECTOR_GRAY_CUPS_3 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayCups3.yaml"
        self.ARUCO_DETECTOR_GRAY_CUPS_4 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayCups4.yaml"
        self.ARUCO_DETECTOR_GRAY_CUPS_5 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayCups5.yaml"
        self.ARUCO_DETECTOR_GRAY_PALLETS_0 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayPallets0.yaml"
        self.ARUCO_DETECTOR_GRAY_PALLETS_1 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayPallets1.yaml"
        self.ARUCO_DETECTOR_GRAY_PALLETS_2 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayPallets2.yaml"
        self.ARUCO_DETECTOR_GRAY_PALLETS_3 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayPallets3.yaml"
        self.ARUCO_DETECTOR_GRAY_PALLETS_4 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayPallets4.yaml"
        self.ARUCO_DETECTOR_GRAY_PALLETS_5 = Path(__file__).resolve().parent.parent / "data" / "ConfDetectionGrayPallets5.yaml"
        self.ESP32_IMAGE_URL = "http://141.51.45.177:8140/capture"








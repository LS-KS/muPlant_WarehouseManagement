"""
This file provides all constant URL data.
"""
from pathlib import Path
import cv2
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






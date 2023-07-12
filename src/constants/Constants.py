"""
This file provides all constant URL data.
"""
from pathlib import Path

class Constants:
    def __init__(self):
        self.PRODUCTLIST = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "Produkte.db"
        self.STORAGEDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "StorageData.db"
        self.STORAGEDATAWRITE = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "StorageDataWrite.db"
        self.COMMISSDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "Commissdata.db"
        self.CAMAPP_QML = "../cameraApplication/qml/CameraAppMain.qml"
        #self.COMMISSIONDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "CommissionData.db"
        self.COMMISSIONDATA = Path(__file__).resolve().parent.parent.parent / "src" / "data" / "CommissionData.yaml"
        self.PRODUCTLISTAPP_QML = "../src/view/ProductList.qml"
        self.PREFERENCES = "src/data/Preferences.yaml"






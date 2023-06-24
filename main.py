
'''
µPlant WareHouse Management Software.
Bachelor Thesis 2023
Author: L.Schink
Date Project Start: 20.06.2023
Language : Python 3.11

This Software implements warehouse logic from heterogene modular autonomic production site.
The warehouse works autonomous while receiving orders from modbus TCP/IP.
also OPC UA is implemented.

Uses  PySide6 with PyQt6.5.1 for GUI implementation
'''
import sys
from pathlib import Path
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine
from src.controller.invController import invController
from src.service.EventlogService import EventlogService

if __name__ == '__main__':
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()

    # create inventoryController with included Data Model and sets itself and viewModels  as rootContext
    inventoryController = invController()
    engine.rootContext().setContextProperty("inventoryController", inventoryController)
    engine.rootContext().setContextProperty("storageModel", inventoryController.storageViewModel)
    engine.rootContext().setContextProperty("productlistModel", inventoryController.productlistViewModel)
    engine.rootContext().setContextProperty("productSummaryModel", inventoryController.productSummaryViewModel)

    # creates EventlogService object and sets itself as rootContext
    eventlogService = EventlogService()
    inventoryController.eventlogService = eventlogService

    # define load main.qml file to start application
    qml_file = Path(__file__).resolve().parent / "src" / "view" / "main.qml"
    engine.load(qml_file)

    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec())





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
from PySide6.QtQml import QQmlApplicationEngine, qmlRegisterType
from PySide6.QtCore import Qt
from src.controller.invController import invController
from src.controller.CommissionController import CommissionController
from src.controller.PreferenceController import PreferenceController
from src.controller.RfidController import RfidController
from src.service.EventlogService import EventlogService
from src.service.OpcuaService import OpcuaService
from src.constants.Constants import Constants
from src.service.AgentService import AgentService


if __name__ == '__main__':
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()
    constants = Constants()
    # create inventoryController with included Data Model and sets itself and viewModels  as rootContext
    inventoryController = invController()

    engine.rootContext().setContextProperty("inventoryController", inventoryController)
    engine.rootContext().setContextProperty('storageModel', inventoryController.storageViewModel)
    engine.rootContext().setContextProperty('productListModel', inventoryController.productlistViewModel)
    engine.rootContext().setContextProperty('productSummaryModel', inventoryController.productSummaryViewModel)

    # creates EventlogService object and sets itself as rootContext
    eventlogService = EventlogService()
    inventoryController.eventlogService = eventlogService
    engine.rootContext().setContextProperty("eventLogController", eventlogService)

    # creates CommissionController object and sets itself as rootContext
    commissionController =  CommissionController()
    commissionController.commissionFilterProxyModel.autoAcceptChildRows()
    engine.rootContext().setContextProperty("commissionController", commissionController)
    engine.rootContext().setContextProperty('commissionModel', commissionController.commissionFilterProxyModel)
    #engine.rootContext().setContextProperty('commissionModel', commissionController.commissionViewModel)

    # creates preferenceController object and sets itself as rootContext
    preferenceController = PreferenceController(eventlogService)
    engine.rootContext().setContextProperty("preferenceController", preferenceController)

    # creates AgentService object and sets itself as rootContext
    agentservice = AgentService(eventlogService, preferenceController)
    engine.rootContext().setContextProperty("agentService", agentservice)

    # creates Controller and models for RFID Server Plugin
    rfidController = RfidController()
    engine.rootContext().setContextProperty("rfidController", rfidController)
    engine.rootContext().setContextProperty("rfidModel", rfidController.rfidViewModel)
    #engine.rootContext().setContextProperty("rfidModel", rfidController.rfidProxyViewModel)

    # creates opcua service
    opcuaService = OpcuaService(eventlogService, preferenceController)
    engine.rootContext().setContextProperty("opcuaService", opcuaService)

    # define load main.qml file to start application
    qml_file =  str(Path(__file__).resolve().parent / "src" / "view" / "main.qml")
    engine.load(qml_file)

    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec())




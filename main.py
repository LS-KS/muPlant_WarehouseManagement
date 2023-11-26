'''
µPlant WareHouse Management Software.
Bachelor Thesis 2023
Author: L.Schink
Date Project Start: 20.06.2023
Language: Python 3.11

This Software implements warehouse logic from heterogene modular autonomic production site.
The warehouse works autonomous while receiving orders from modbus TCP/IP.
also OPC UA is implemented.

Uses PySide6 with PyQt6.5.1 for GUI implementation
'''
import sys
from pathlib import Path
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine
from src.controller.invController import invController
from src.controller.CommissionController import CommissionController
from src.controller.PreferenceController import PreferenceController
from src.controller.RfidController import RfidController
from src.service.EventlogService import EventlogService
from src.service.OpcuaService import OpcuaService
from src.constants.Constants import Constants
from src.service.AgentService import AgentService
from src.service.rfidservice import RfidService
from src.service.stocktaking import Stocktaker
from src.service.comissionservice import CommissionService
from src.controller.ABBController import ABBController
from src.viewmodel.stockmodel import stockmodel, tablemodel
from src.viewmodel.EventViewModel import EventSortModel

#TODO: check and correct function of START / STOP Buttons in main.qml - this should quit and reset all services.
#TODO: CommissionController must take transportable data objects from future not from actual storage. 

#TODO: CommissionContoller must change actual inventory data when commission is done.
#TODO: When Commission is pending, set transportable object into gripper.
#TODO: Implement listeners to opcuas agent variables
#TODO: Connect opcua agent listeners to commissioncontroller

#TODO: Commission handling: Implement functions to edit or delete commissions.

#TODO: Fix crash of MCC Plugin when Plugin is started first time. (second time works always fine)

#TODO: Adjust tests to dynamic data files, so that they will never fail because data files changed. Alternatevly: create test data files from actual data.
if __name__ == '__main__':
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()
    constants = Constants()
    # create inventoryController with included Data Model and sets itself and viewModels  as rootContext
    inventoryController = invController()

    engine.rootContext().setContextProperty("inventoryController", inventoryController)
    engine.rootContext().setContextProperty('storageModel', inventoryController.storageViewModel)
    engine.rootContext().setContextProperty('productListModel', inventoryController.productListViewModel)
    engine.rootContext().setContextProperty('productSummaryModel', inventoryController.productSummaryViewModel)

    # creates EventlogService object and sets itself as rootContext
    eventlogService = EventlogService()
    #engine.rootContext().setContextProperty("eventModel", eventlogService.eventSortModel)
    engine.rootContext().setContextProperty("eventModel", eventlogService.eventViewModel)
    inventoryController.eventlogService = eventlogService
    engine.rootContext().setContextProperty("eventLogController", eventlogService)
    
    # creates preferenceController object and sets itself as rootContext
    preferenceController = PreferenceController(eventlogService)
    engine.rootContext().setContextProperty("preferenceController", preferenceController)

    # Create ABB Controller for IRB 140
    abbController = ABBController(preferenceController, eventlogService)
    engine.rootContext().setContextProperty("abbController", abbController)

    # creates CommissionController object and sets itself as rootContext
    commissionController =  CommissionController(inventoryController, eventlogService)
    commissionController.commissionFilterProxyModel.autoAcceptChildRows()
    engine.rootContext().setContextProperty("commissionController", commissionController)
    # engine.rootContext().setContextProperty('commissionModel', commissionController.commissionFilterProxyModel)
    engine.rootContext().setContextProperty('commissionModel', commissionController.commissionViewModel)

    #creates commission service to handle commissions with opcua and abb controller
    commission_service = CommissionService(commission_controller = commissionController, abb_controller = abbController, )
    engine.rootContext().setContextProperty("commission_service", commission_service)
    commissionController.new_commission.connect(commission_service.handle_new_commission)

    # creates AgentService object and sets itself as rootContext
    agentservice = AgentService(eventlogService, preferenceController)
    engine.rootContext().setContextProperty("agentService", agentservice)

    # creates Controller and models for RFID Server Plugin
    rfidController = RfidController()
    engine.rootContext().setContextProperty("rfidController", rfidController)
    engine.rootContext().setContextProperty("rfidModel", rfidController.rfid_viewmodel)
    #engine.rootContext().setContextProperty("rfidModel", rfidController.rfidProxyViewModel)

    # creates rfid_service object and sets itself as rootContext
    rfid_service = RfidService(eventlogService, rfidController)
    rfidController.rfid_service = rfid_service
    engine.rootContext().setContextProperty("rfid_service", rfid_service)
    rfid_service.data.connect(rfidController.update_model)

    # creates opcua service
    opcuaService = OpcuaService(
        preferenceController= preferenceController,
        inventory_controller= inventoryController,
        commission_controller= commissionController,
        rfidcontroller= rfidController,
        agentservice= agentservice)
    engine.rootContext().setContextProperty("opcuaService", opcuaService)
    opcuaService.online.connect(rfidController.notify_opcua)
    opcuaService.event.connect(eventlogService.write_event)
    rfidController.data_to_opcua.connect(opcuaService.handle_rfid_update)

    # creates Stocktaker object used in stocktaking plugin
    stocktaker = Stocktaker(eventlogService)
    engine.rootContext().setContextProperty("stocktaker", stocktaker)
    engine.addImageProvider("stocktaker", stocktaker)

    #create stockmodel
    stock_model = stockmodel(inv_controller=inventoryController)
    table_model = tablemodel(inv_controller=inventoryController)
    engine.rootContext().setContextProperty("storagemodel", stock_model)
    engine.rootContext().setContextProperty("tablemodel", table_model)

    # define load main.qml file to start application
    qml_file =  str(Path(__file__).resolve().parent / "src" / "view" / "main.qml")
    engine.load(qml_file)

    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec())




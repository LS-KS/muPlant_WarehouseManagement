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
from src.service.abbservice import abbservice
from src.viewmodel.stockmodel import stockmodel, tablemodel
from src.viewmodel.EventViewModel import EventSortModel


################################################# COMMISSION MODEL ########################################################################
#TODO: new variable to determine wether the Robot shall be drove fast or slow depending on water inside the cup or not. 
#TODO: Communication with IRC5 wether the robot will wait at certain destinations to take a picture from gripper cam. 

############################################### COMMISSION CONTROLLER #####################################################################
#TODO: in CommissionController: if a commission is prepared and gets executed: a method to backtrace the prepared commission is needed. Only affects commissions to/from robot

##################################################### ABB SERVICE #########################################################################
#TODO: fix commission handling with abbservice
#TODO: GUI freezes when commission is performed.
#TODO: refactor run method to use recvfrom(). This way the byteobject comes together with ip adress to determine the sender. Link: https://docs.python.org/3/library/socket.html#socket-objects

#################################################### OPC UA SERVICE #######################################################################
#TODO: Connect opcua agent listeners to commissioncontroller when commission is called as execute

########################################################## IRC5 ###########################################################################
#TODO: Find out how to select IRC5 via MAC address using socket package
#TODO: Zustand variable must be set in robot as well as Näherungsschalter.
#TODO: DI5: light barrier
#TODO: DI3, DI4: proximity switches
#TODO: Signal from Robot before waiting at camera position

####################################################### STOCKTAKING #######################################################################
#TODO: Test overview cam together with GUI
#TODO: Test gripper cam together with GUI
#TODO: Implement image handling so that the user can confirm/change inventory changes. 
#TODO: Implement 'Details' Button logic as a Dialog. 
#TODO: Buttons are not visible beause window's height is too large. 

###################################################### Nice to have #######################################################################
#TODO: CommissionController must take transportable data objects from future not from actual storage. 
#TODO: if commission is tested that transport a cup from workbench to mobile Robot, False is returned.
#TODO: Robot-> Workbench: in commissioncheck_perform: sE_cup is always None. Check why commission check temperory deactivated
#TODO: Adjust tests to dynamic data files, so that they will never fail because data files changed. Alternatevly: create test data files from actual data.
#TODO: Rewrite inventoryController tests.

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
    abb_service = abbservice(ip= preferenceController.get_abb_ip(), port= preferenceController.get_abb_port())
    engine.rootContext().setContextProperty("abb_service", abb_service)

    # creates CommissionController object and sets itself as rootContext
    commissionController =  CommissionController(inventoryController, eventlogService)
    commissionController.commissionFilterProxyModel.autoAcceptChildRows()
    engine.rootContext().setContextProperty("commissionController", commissionController)
    engine.rootContext().setContextProperty('commissionModel', commissionController.commissionViewModel)


    # creates AgentService object and sets itself as rootContext
    agentservice = AgentService(eventlogService, preferenceController)
    engine.rootContext().setContextProperty("agentService", agentservice)

    # creates Controller and models for RFID Server Plugin
    rfidController = RfidController()
    engine.rootContext().setContextProperty("rfidController", rfidController)
    engine.rootContext().setContextProperty("rfidModel", rfidController.rfid_viewmodel)

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




from PySide6.QtCore import Signal, Slot, QObject
from src.service.EventlogService import EventlogService
from yaml import load, dump, Loader, Dumper
from src.model.Preferences import Preferences
from src.constants.Constants import Constants
from pathlib import Path


class PreferenceController(QObject):
    """
    Controller class for Preferences
    """
    modbusIPError = Signal(bool)
    modbusPortError = Signal(bool)
    modbusReconnectError = Signal(bool)
    abbIPError = Signal(bool)
    abbPortError = Signal(bool)
    sendPreferences = Signal(str, int, int, str, int, bool, bool, str, str, str, str)

    def __init__(self, eventlogService: EventlogService):
        super().__init__()
        self.preferences = Preferences()
        self.eventLogService = eventlogService
        self.constants = Constants()
        self._loadPreferencesYAML()

    
    def  get_abb_ip(self):
        return self.preferences.abb.ip
    
    def get_abb_port(self):
        return self.preferences.abb.port

    @Slot(str, int, int)
    def setModBusPreferences(self, ip, port, reconnects):
        """
        Sets the preferences for the ModBus connection
        """
        ipRes = self.preferences.modBus.setIP(ip)
        portRes = self.preferences.modBus.setPort(port)
        reconnectRes = self.preferences.modBus.setMaxReconnects(reconnects)

        if not ipRes:
            self.eventLogService.write_event("Preferences", f"{ip} is an invalid IP address!")
            self.modbusIPError.emit(True)
        else:
            self.modbusIPError.emit(False)
        if not portRes:
            self.eventLogService.write_event("Preferences", f"Error in port: {port} is an invalid port!")
            self.modbusPortError.emit(True)
        else:
            self.modbusPortError.emit(False)
        if not reconnectRes:
            self.eventLogService.write_event("Preferences", f"Error in max reconnects: {reconnects} is not a number")
            self.modbusReconnectError.emit(True)
        else:
            self.modbusReconnectError.emit(False)
        if ipRes and portRes and reconnectRes:
            self._dumpPreferencesYAML()

    @Slot(str, str)
    def setOPCPreferences(self, enpoint, namespace, cUrl, cNamespace):
        """
        Sets the preferences for the OPC UA connection
        """
        self.preferences.opcua.endpoint = enpoint
        self.preferences.opcua.namespace = namespace
        self.preferences.opcua.clientUrl = cUrl
        self.preferences.opcua.clientNamespace = cNamespace
        self._dumpPreferencesYAML()

    @Slot(str, int)
    def setAbbPreferences(self, ip, port):
        """
        Sets the preferences for the ABB controller connection

        :param ip:
        :param port:
        :return:
        """
        ipRes = self.preferences.abb.setIP(ip)
        portRes = self.preferences.abb.setPort(port)
        if not ipRes:
            self.eventLogService.write_event("Preferences", f"{ip} is an invalid IP address!")
            self.abbIPError.emit(True)
        else:
            self.abbIPError.emit(False)
        if not portRes:
            self.eventLogService.write_event("Preferences", f"{port} is an invalid port!")
            self.abbPortError.emit(True)
        else:
            self.abbPortError.emit(False)
        if ipRes and portRes:
            self._dumpPreferencesYAML()

    @Slot(bool, bool)
    def setPlugInPreferences(self, rfid, mcc):
        """
        Sets the preferences if plugins are automatically enabled or not

        :param rfid: if True, the RFID Server plugin will start automatically if the Start button is pressed
        :param mcc: if True, the ManualCommissionControl  plugin will start automatically if the Start button is pressed
        :return:
        """
        self.preferences.plugins.autostartRfidServer = rfid
        self.preferences.plugins.autostartMcc = mcc
        self._dumpPreferencesYAML()


    @Slot()
    def loadPreferences(self):
        """
        Emits getPreferences signal.
        """
        self._loadPreferencesYAML()
        self.sendPreferences.emit(self.preferences.modBus.ip,
                                  self.preferences.modBus.port,
                                  self.preferences.modBus.maxReconnects,
                                  self.preferences.abb.ip,
                                  self.preferences.abb.port,
                                  self.preferences.plugins.autostartRfidServer,
                                  self.preferences.plugins.autostartMccPlugin,
                                  self.preferences.opcua.endpoint,
                                  self.preferences.opcua.namespace,
                                  self.preferences.opcua.clientUrl,
                                  self.preferences.opcua.clientNamespace,)

    def _dumpPreferencesYAML(self):
        """
        Dumps the preferences to a yaml file
        """
        with open(self.constants.PREFERENCES, "w") as file:
            dump({'modbusip': self.preferences.modBus.ip,
                  'modbusport': self.preferences.modBus.port,
                  'modbusreconnects': self.preferences.modBus.maxReconnects,
                  'abbip': self.preferences.abb.ip,
                  'abbport': self.preferences.abb.port,
                  'autostartRfidServer': self.preferences.plugins.autostartRfidServer,
                  'autostartMcc': self.preferences.plugins.autostartMccPlugin,
                  'opcuaEndpoint': self.preferences.opcua.endpoint,
                  'opcuaNamespace': self.preferences.opcua.namespace,
                  'clientUrl': self.preferences.opcua.clientUrl,
                  'clientNamespace': self.preferences.opcua.clientNamespace},
                 file)

    def _loadPreferencesYAML(self):
        """
        Loads the preferences from a yaml file
        """
        try:
            with open(self.constants.PREFERENCES, "r") as file:
                read = load(file, Loader=Loader)
                self.preferences.modBus.setIP(read['modbusip'])
                self.preferences.modBus.setPort(read['modbusport'])
                self.preferences.modBus.setMaxReconnects(read['modbusreconnects'])
                self.preferences.abb.setIP(read['abbip'])
                self.preferences.abb.setPort(read['abbport'])
                self.preferences.plugins.autostartRfidServer = read['autostartRfidServer']
                self.preferences.plugins.autostartMccPlugin = read['autostartMcc']
                self.preferences.opcua.endpoint = read['opcuaEndpoint']
                self.preferences.opcua.namespace = read['opcuaNamespace']
                self.preferences.opcua.clientUrl = read['clientUrl']
                self.preferences.opcua.clientNamespace = read['clientNamespace']
        except FileNotFoundError as e:
            self.eventLogService.write_event("Preferences", "Preferences file not found No preferences can be loaded.")
            print("Preferences file not found No preferences can be loaded." + str(e))

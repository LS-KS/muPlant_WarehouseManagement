from PySide6.QtCore import Signal, Slot, QObject
from src.service.EventlogService import EventlogService
from yaml import load, dump, Loader, Dumper
from src.model.Preferences import Preferences
from src.constants.Constants import Constants


class PreferenceController(QObject):
    """
    Controller class for Preferences
    """
    modbusIPError = Signal(bool)
    modbusPortError = Signal(bool)
    modbusReconnectError = Signal(bool)
    abbIPError = Signal(bool)
    abbPortError = Signal(bool)
    sendPreferences = Signal(str, int, int, str, int)

    def __init__(self, eventlogService: EventlogService):
        super().__init__()
        self.preferences = Preferences()
        self.eventLogService = eventlogService
        self.constants = Constants()
        self._loadPreferencesYAML()

    @Slot(str, int, int)
    def setModBusPreferences(self, ip, port, reconnects):
        """
        Sets the preferences for the ModBus connection
        """
        ipRes = self.preferences.modBus.setIP(ip)
        portRes = self.preferences.modBus.setPort(port)
        reconnectRes = self.preferences.modBus.setMaxReconnects(reconnects)

        if not ipRes:
            self.eventLogService.writeEvent("Preferences", f"{ip} is an invalid IP address!")
            self.modbusIPError.emit(True)
        else:
            self.modbusIPError.emit(False)
        if not portRes:
            self.eventLogService.writeEvent("Preferences", f"Error in port: {port} is an invalid port!")
            self.modbusPortError.emit(True)
        else:
            self.modbusPortError.emit(False)
        if not reconnectRes:
            self.eventLogService.writeEvent("Preferences", f"Error in max reconnects{reconnects} is not a number")
            self.modbusReconnectError.emit(True)
        else:
            self.modbusReconnectError.emit(False)
        if ipRes and portRes and reconnectRes:
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
            self.eventLogService.writeEvent("Preferences", f"{ip} is an invalid IP address!")
            self.abbIPError.emit(True)
        else:
            self.abbIPError.emit(False)
        if not portRes:
            self.eventLogService.writeEvent("Preferences", f"{port} is an invalid port!")
            self.abbPortError.emit(True)
        else:
            self.abbPortError.emit(False)
        if ipRes and portRes:
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
                                  self.preferences.abb.port)

    def _dumpPreferencesYAML(self):
        """
        Dumps the preferences to a yaml file
        """
        with open(self.constants.PREFERENCES, "w") as file:
            dump({'modbusip': self.preferences.modBus.ip,
                  'modbusport': self.preferences.modBus.port,
                  'modbusreconnects': self.preferences.modBus.maxReconnects,
                  'abbip': self.preferences.abb.ip,
                  'abbport': self.preferences.abb.port},
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
        except FileNotFoundError:
            pass

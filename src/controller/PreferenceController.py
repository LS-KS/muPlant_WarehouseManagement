from PySide6.QtCore import Signal, Slot, QObject

from src.model.Preferences import Preferences
from src.service.EventlogService import EventlogService

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

    def __init__(self, eventlogService : EventlogService):
        super().__init__()
        self.preferences = Preferences()
        self.eventLogService = eventlogService

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
        if not portRes:
            self.eventLogService.writeEvent("Preferences", f"{port} is an invalid port!")
            self.modbusPortError.emit(True)
        if not reconnectRes:
            self.eventLogService.writeEvent("Preferences", f"{reconnects} is not a number")
            self.modBusReconnectError.emit(True)

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
        if not portRes:
            self.eventLogService.writeEvent("Preferences", f"{port} is an invalid port!")
            self.abbPortError.emit(True)

    @Slot()
    def loadPreferences(self):
        """
        Emits getPreferences signal.
        """

        self.sendPreferences.emit(self.preferences.modBus.ip,
                                 self.preferences.modBus.port,
                                 self.preferences.modBus.maxReconnects,
                                 self.preferences.abb.ip,
                                 self.preferences.abb.port)

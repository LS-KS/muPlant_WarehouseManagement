#import obidrfid
from PySide6.QtCore import QObject, Signal, Slot
from src.controller.RfidController import RfidController
from src.service.EventlogService import EventlogService
from src.model.RfidModel import RfidModel

class rfid_service(QObject):

    def __init__(self, eventlogservice: EventlogService, rfidcontroller: RfidController, parent=None):
        super().__init__(parent)
        self.eventlogservice = eventlogservice
        self.rfidcontroller = rfidcontroller

    def start_node(self, node):
        """
        Starts given RFID Node which is a slice of rfidcontrollers rfidviewmodel.
        :param node: RFID Node to start
        :type node: RfidModel
        """
        ip = node.ipAddr
        port = node.ipPort

    def _validate_ip_port(self, ip: str, port: str | int) -> bool:
        """
        Validates given ip and port.
        :param ip: ip to validate
        :type ip: str
        :param port: port to validate
        :type port: str |int
        :return: True if ip and port are valid, False otherwise
        :rtype: bool
        """
        exps = ip.split(".")
        if len(exps) != 4:
            return False
        for exp in exps:
            if not exp.isnumeric():
                return False
            elif int(exp) > 255:
                return False
        if not port.isnumeric():
            return False
        elif int(port) > 65535:
            return False
        return True







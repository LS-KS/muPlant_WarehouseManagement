import obidrfid
from PySide6.QtCore import QObject, Signal, Slot, QThread
from src.controller.RfidController import RfidController
from src.service.EventlogService import EventlogService
from src.model.RfidModel import RfidModel

class rfid_readertask(QThread):

    def __init__(self, node, service, parent = None ):
        super().__init__(parent)
        self.node: RfidModel = node
        self.service: rfid_service = service

    def start(self):
        super().start()
        if self.node.reader is not None:
            try:
                self.node.data = obidrfid.rfid_read(self.node.reader)
                'TODO: callback if tagdata is read'
                'TODO: create and emit signal if tagdata is read'
            except Exception as e:
                self.service.eventlogservice.writeEvent("RFIDReaderTask", f"RFID-Node {self.node.name} mit IP {self.node.ipAddr} und Port {self.node.ipPort} konnte nicht gelesen werden. {e}")
            finally:
                self.stop()
        return self

    def stop(self):
        super().quit()
        super().wait()
        super().deleteLater()
class rfid_service(QObject):

    def __init__(self, eventlogservice: EventlogService, rfidcontroller: RfidController, parent=None):
        super().__init__(parent)
        self.eventlogservice = eventlogservice
        self.rfidcontroller = rfidcontroller
        self.nodes = []

    def start_node(self, node) -> None:
        """
        Starts given RFID Node which is a slice of rfidcontrollers rfidviewmodel.
        :param node: RFID Node to start
        :type node: RfidModel
        """
        if not self._validate_ip_port(node.ipAddr, node.ipPort):
            self.eventlogservice.writeEvent("RFIDService.start_node", f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} konnte nicht gestartet werden. IP oder Port ungültig")
            return
        node.reader = obidrfid.rfid_connect(node.ipAddr, node.ipPort)
        task = rfid_readertask(node).start()
        self.nodes.append([node, task])
        self.eventlogservice.writeEvent("RFIDService.start_node", f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} gestartet.")

    def stop_node(self, node) -> bool:
        """
        Stops given RFID Node which is a slice of rfidcontrollers rfidviewmodel and kills its existing QThread
        :param node: RFID Node to stop
        :type node: RfidModel
        """
        if node in self.nodes:
            idx = self.nodes.index(node)
            self.nodes[idx][1].stop()
            self.nodes[idx][0].reader = None
            self.nodes.remove(node)
            self.eventlogservice.writeEvent("RFIDService.stop_node", f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} gestoppt.")
            return True
        else:
            self.eventlogservice.writeEvent("RFIDService.stop_node", f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} konnte nicht gestoppt werden. Node nicht gefunden.")
        return False

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







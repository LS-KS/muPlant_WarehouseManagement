from typing import Optional
from OBID_RFID import obidrfid
from PySide6.QtCore import QObject, Signal, Slot, QThread
from src.controller.RfidController import RfidController
from src.service.EventlogService import EventlogService
from src.model.RfidModel import RfidModel
import datetime

class rfid_readerworker(QObject):
    data = Signal(str, str, str, str) # transponder type, iid, dfsid, timestamp
    
    def __init__(self, node, service, parent = None) -> None:
        super().__init__(parent)
        self.node = node
        self.service = service
        self.running = False
    
    def run(self):
        print("run-method started")
        if self.node.reader is None:
            try:
                print("read ip address")
                ip = self.node.ipAddr
                print("check ip validity")
                if ip is None or not obidrfid.validate_ip(ip):
                    raise ValueError(f"{ip} ist eine ungültige IP-Adresse. Die folgende RFID-Node konnte nicht gestartet werden: {self.node.name}")
                print(f"connect to rfid node with {ip}")
                self.node.reader = obidrfid.rfid_connect(str(ip))
                self.service.eventlogservice.writeEvent("RFIDReaderTask", f"RFID-Node {self.node.name} mit IP {self.node.ipAddr} und Port {self.node.ipPort} connected {obidrfid.rfid_reader_info(self.node.reader)}")
                print("start reader loop")
                self.running = True
                while(self.running):
                    data = obidrfid.rfid_read(self.node.reader)
                    if(len(data)):
                        self.node.transponder_type = data[0].get('tr_type')
                        self.node.iid = data[0].get('iid')
                        self.node.dsfid = data[0].get('dsfid')
                        self.node.timestamp = datetime.datetime.now().timestamp()
                        self.node.last_valid_transponder_type = self.node.transponder_type
                        self.node.last_valid_iid = self.node.iid
                        self.node.last_valid_dsfid = self.node.dsfid
                        self.node.last_valid_timestamp = datetime.datetime.now().timestamp()
                        self.service.eventlogservice.writeEvent("RFIDReaderTask", f"RFID-Node {self.node.name} mit IP {self.node.ipAddr} und Port {self.node.ipPort}: Daten gelesen: iid: {self.node.iid}, dsfid: {self.node.dsfid}, transpondertype: { self.node.transponder_type}")
                    else:
                        self.node.transponder_type = "No Transponder"
                        self.node.iid = "0"
                        self.node.dsfid = "0"
                        self.node.timestamp = datetime.datetime.now().timestamp()
                        self.service.eventlogservice.writeEvent("RFIDReaderTask", f"RFID-Node {self.node.name} mit IP {self.node.ipAddr} und Port {self.node.ipPort}: No Transponder")
            except Exception as e:
                self.service.eventlogservice.writeEvent("RFIDReaderTask", f"RFID-Node {self.node.name} mit IP {self.node.ipAddr} und Port {self.node.ipPort} konnte nicht gelesen werden. {e}")
            finally:
                self.stop()
        else:
            print("reader is not None")
    def stop(self):
        self.running = False

class rfid_readertask(QThread):

    def __init__(self, node:RfidModel, service, parent = None ):
        super().__init__(parent)
        self.worker = rfid_readerworker(node, service)
        self.worker.data.connect(self.handle_data_read)

    def start(self):
        super().start()
        
    def run(self):
        self.worker.run()

    def stop(self):
        self.worker.running = False
        self.worker.quit()
        self.worker.wait()
        self.worker.deleteLater()
    
    def handle_data_read():
        pass

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
        task = rfid_readertask(node, self)
        self.nodes.append([node, task])
        task.start()
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







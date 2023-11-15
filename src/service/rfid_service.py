from typing import Optional
from OBID_RFID import obidrfid
from PySide6.QtCore import QObject, Signal, Slot, QThread, QMutex, QModelIndex, QByteArray
from src.controller.RfidController import RfidController
from src.service.EventlogService import EventlogService
from src.model.RfidModel import RfidModel
import datetime

class rfid_readerworker(QObject):
    data = Signal(str, str, str, str) # transponder type, iid, dfsid, timestamp
    
    def __init__(self, ip:str, name:str, service:EventlogService, parent = None) -> None:
        super().__init__(parent)
        self.ip = ip
        self.name = name
        self.service = service
        self.running = False
        self.reader = None
        self.lock = QMutex() # Thread lock
    
    def run(self):
        """
        Ths function uses the obidrfid library to connect to a RFID Node and read its data.
        It also uses PySides QMutex class to lock the thread while the while loop is running.
        Data is emitted via the data signal.

        Thread safety needs to be tested, bt change from 14.11.2023 should improve this further. When crashes occur,
        check if rfid_readertask needs also be muted. There is no good documentation about threadsafety in Qt.

        One thing to be sure: don't use the threading module from python, use Qt-native threading classes instead!


        This method first uses obidrfid's validation method to check if the submitted ip is valid. This uses ping command.

        If ping is successful, the method tries to connect to the RFID Node with the given ip and calls the rfid_read
        function. obidrfid is a fork of the original obidrfid library, which is mainly adapted to use .dll file
        instead of .so file of the FEIG .NET SDK.

        Any exception is caught and logged to the eventlogservice. Note that only the pointer to the eventlogservice
        instance is submitted and writeEvent is a Slot. So theoretically, this should be thread safe.

        :raises ValueError: if ip is invalid
        :raises ConnectionError: if connection to RFID Node failed
        """
        print("run-method started")
        self.lock.lock()
        try:
            # print("read ip address")
            # print("check ip validity")
            if self.ip is None or not obidrfid.validate_ip(self.ip):
                raise ValueError(f"{self.ip} ist eine ungültige IP-Adresse. Die folgende RFID-Node konnte nicht gestartet werden: {self.name}")
            #print(f"connect to rfid node with {self.ip}")
            self.reader = obidrfid.rfid_connect(str(self.ip))
            if self.reader is None:
                raise ConnectionError(f"Verbindung zu RFID-Node {self.name} mit IP {self.ip} konnte nicht hergestellt werden.")
            self.service.writeEvent("RFIDReaderTask", f"RFID-Node {self.name} mit IP {self.ip} connected {obidrfid.rfid_reader_info(self.reader)}")
            #print("start reader loop")
            self.running = True
            while(self.running):
                data = obidrfid.rfid_read(self.reader)
                if(len(data)):
                    transponder_type = data[0].get('tr_type')
                    iid = data[0].get('iid')
                    dsfid = data[0].get('dsfid')
                    timestamp = datetime.datetime.now().timestamp()
                    self.service.writeEvent("RFIDReaderTask", f"RFID-Node {self.name} mit IP {self.ip}: Daten gelesen: iid: {iid}, dsfid: {dsfid}, transpondertype: {transponder_type}")
                    self.data.emit(str(transponder_type), str(iid), str(dsfid), str(timestamp))
                else:
                    transponder_type = "No Transponder"
                    iid = "0"
                    dsfid = "0"
                    timestamp = datetime.datetime.now().timestamp()
                    self.service.writeEvent("RFIDReaderTask", f"RFID-Node {self.name} mit IP {self.ip}: No Transponder")
                    self.data.emit(str(transponder_type), str(iid), str(dsfid), str(timestamp))
        except Exception as e:
            self.data.emit("None","Error", "Error", str(datetime.datetime.now()) )
            self.service.writeEvent("RFIDReaderTask", f"RFID-Node {self.name} mit IP {self.ip} konnte nicht gelesen werden. {e}")
        finally:
            self.lock.unlock()

    def stop(self):
        """
        Stops the while loop in the run method.
        """
        self.lock.lock()
        try:
            self.running = False
        finally:
            self.lock.unlock()

class rfid_readertask(QThread):
    data = Signal(str, str, str, str, str) # ip, transponder type, iid, dfsid, timestamp
    def __init__(self, ip:str, name:str, service:EventlogService, parent = None ):
        super().__init__(parent)
        self.worker = rfid_readerworker(ip, name, service)
        self.worker.data.connect(self.handle_data_read)
        self.worker.moveToThread(self)
        self.ip: str = ip

    def start(self):
        super().start()
        
    def run(self):
        self.worker.run()

    def stop(self):
        self.worker.running = False
        self.worker.quit()
        self.worker.wait()
        self.worker.deleteLater()
    
    def handle_data_read(self, transponder_type:str, iid:str, dsfid:str, timestamp:str):
        #print(f"worker got Signal transponder type: {transponder_type}, iid: {iid}, dsfid:{dsfid}, timestamp: {timestamp}")
        self.data.emit(self.ip, transponder_type, iid, dsfid, timestamp)

class rfid_service(QObject):

    def __init__(self, eventlogservice: EventlogService, rfidcontroller: RfidController, parent=None):
        super().__init__(parent)
        self.eventlogservice = eventlogservice
        self.rfidcontroller = rfidcontroller
        self.rolenames = None
        self.nodes = []

    def start_node(self, node, index: QModelIndex, rolenames: dict) -> None:
        """
        Starts given RFID Node, which is a slice of rfidcontrollers rfidviewmodel.
        Connects rfid_readertask.data to own handle_data_read method which sets submitted data to given node.
        Not that these methods and classes used need to be thread safe!

        :param node: RFID Node to start
        :type node: RfidModel
        """
        self.rolenames: dict = rolenames
        if not self._validate_ip_port(node.ipAddr, node.ipPort):
            self.eventlogservice.writeEvent("RFIDService.start_node", f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} konnte nicht gestartet werden. IP oder Port ungültig")
            return
        task = rfid_readertask(node.ipAddr, node.name, self.eventlogservice, self)
        self.nodes.append([node, index, task])
        task.data.connect(self.handle_data_read)
        task.start()
        self.eventlogservice.writeEvent("RFIDService.start_node", f"starte RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort}...")

    def handle_data_read(self, ip:str, transponder_type:str, iid:str, dsfid:str, timestamp:str):
        """
        Sets submitted data to given node.
        Parameters

        :param ip: ip address of RFID Node
        :type ip: str
        :param transponder_type: transponder type of RFID Node
        :type transponder_type: str
        :param iid: iid of RFID Node
        :type iid: str
        :param dsfid: dsfid of RFID Node
        :type dsfid: str
        :param timestamp: timestamp data is read
        :type timestamp: str
        """
        print(f"service got Signal transponder ip: {ip} type: {transponder_type}, iid: {iid}, dsfid:{dsfid}, timestamp: {timestamp}")

        for node, index, task in self.nodes:
            if node.ipAddr == ip:
                #print("found the right one")
                roles = list(self.rolenames.keys())
                rolenames = list(self.rolenames.values())
                
                self.rfidcontroller.rfidViewModel.setData(index, transponder_type, roles[rolenames.index(b'transponder_type')])
                self.rfidcontroller.rfidViewModel.setData(index, iid, roles[rolenames.index(b'iid')])
                self.rfidcontroller.rfidViewModel.setData(index, dsfid, roles[rolenames.index(b'dsfid')])
                self.rfidcontroller.rfidViewModel.setData(index, timestamp, roles[rolenames.index(b'timestamp')])
                if iid != "Error":
                    self.rfidcontroller.rfidViewModel.setData(index, transponder_type, roles[rolenames.index(b'last_valid_transponder_type')])
                    self.rfidcontroller.rfidViewModel.setData(index, iid, roles[rolenames.index(b'last_valid_iid')])
                    self.rfidcontroller.rfidViewModel.setData(index, dsfid, roles[rolenames.index(b'last_valid_dsfid')])
                    self.rfidcontroller.rfidViewModel.setData(index, timestamp, roles[rolenames.index(b'last_valid_timestamp')])
                break
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







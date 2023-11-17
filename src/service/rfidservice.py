from OBID_RFID import obidrfid
from PySide6.QtCore import QObject, Signal, Slot, QThread, QMutex, QModelIndex, QByteArray, QTimer
from src.controller.RfidController import RfidController
from src.service.EventlogService import EventlogService
from src.model.RfidModel import RfidModel
import datetime


class RfidReaderWorker(QObject):
    data = Signal(str, str, str, str)  # transponder type, iid, dfsid, timestamp

    def __init__(self, ip: str, name: str, parent=None) -> None:
        super().__init__(parent)
        self.ip = ip
        self.name = name
        self.running = False
        self.reader = None
        self.lock = QMutex()

    def run(self):
        """
        Ths function uses the obidrfid library to connect to a RFID Node and read its data.
        It also uses PySides QMutex class to lock the thread while the while loop is running.
        Data is emitted via the data signal.

        Ip must be valid!
        thread is locked while connecting to the node.
        Tries to connect to the RFID Node with the given ip and calls the rfid_read
        function for a max amount of five times.
        obidrfid is a fork of the original obidrfid library, which is mainly adapted to use .dll file
        instead of .so file of the FEIG .NET SDK.

        Any exception is caught. Note that no eventlog_service is submitted to this clas because of thread-safety.
        errored readings must be identified by strings

        :raises ConnectionError: if connection to RFID Node failed for 5 times, catches this and emits a erroneous data signal
        """
        self.lock.lock()
        try:
            tries: int = 0
            while tries < 5:
                self.reader = obidrfid.rfid_connect(str(self.ip))
                if self.reader is None:
                    tries += 1
                    if tries > 5:
                        raise ConnectionError(
                            f"Verbindung zu RFID-Node {self.name} mit IP {self.ip} konnte nicht hergestellt werden.")
                else:
                    break
            data = obidrfid.rfid_read(self.reader)
            if (len(data)):
                transponder_type = data[0].get('tr_type')
                iid = data[0].get('iid')
                dsfid = data[0].get('dsfid')
                timestamp = datetime.datetime.now().timestamp()
                self.data.emit(str(transponder_type), str(iid), str(dsfid), str(timestamp))
            else:
                transponder_type = "No Transponder"
                iid = "0"
                dsfid = "0"
                timestamp = datetime.datetime.now().timestamp()
                self.data.emit(str(transponder_type), str(iid), str(dsfid), str(timestamp))
        except Exception as e:
            self.data.emit("None", "Error", "Error", str(datetime.datetime.now()))
        finally:
            self.lock.unlock()


class RfidReadertask(QThread):
    data = Signal(str, str, str, str, str)  # ip, transponder type, iid, dfsid, timestamp
    worker: RfidReaderWorker

    def __init__(self, ip: str, name: str, parent=None):
        super().__init__(parent)
        self.running = True
        self.ip: str = ip
        self.name: str = name

    def start(self):
        """
        Starts the QThread.
        Creates RfidReaderWorker instance.
        Links RfidReaderWorker's data signal to handle_data_read - method.
        Moves RfidReaderWorker to this QThread instance.e
        """
        super().start()
        self.worker = RfidReaderWorker(self.ip, self.name)
        self.worker.data.connect(self.handle_data_read)
        self.worker.moveToThread(self)

    def run(self):
        """
        Main-loop of the RfidReaderTask instance.
        calls RfidReaderWorker's run method, which connects to the node and emits data read as signal.
        """
        while self.running:
            self.worker.run()
            self.sleep(1)

    def stop(self):
        """
        Stops the main loop and stops the QThread instance.
        """
        self.running = False
        self.worker.deleteLater()

    def handle_data_read(self, transponder_type: str, iid: str, dsfid: str, timestamp: str):
        """
        This method is connected to RfidReaderWorker's instance data signal.
        emits RfidReaderTasks's data signal.
        """
        self.data.emit(self.ip, transponder_type, iid, dsfid, timestamp)


class RfidService(QObject):
    data = Signal(bool, QModelIndex, int, str, int, str, int, str, int, str)

    def __init__(self, eventlog_service: EventlogService, rfid_controller: RfidController, parent=None):
        super().__init__(parent)
        self.role_names = None
        self.eventlog_service = eventlog_service
        self.rfid_controller = rfid_controller
        self.nodes = []

    def start_node(self, node, index: QModelIndex, role_names: dict) -> None:
        """
        Starts given RFID Node, which is a slice of rfidcontrollers rfidviewmodel.
        Connects rfid_readertask.data to own handle_data_read method which sets submitted data to given node.
        Not that these methods and classes used need to be thread safe!

        :param node: RFID Node to start
        :type node: RfidModel
        :param index: Index of RfidController's viewmodel
        :type index: QModelIndex
        :param role_names: submitted dict to be able to emit the right role for viewmodel's setData slot
        """
        self.role_names = role_names
        if not self._validate_ip_port(node.ipAddr, node.ipPort):
            self.eventlog_service.writeEvent("RFIDService.start_node",
                                             f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} konnte nicht gestartet werden. IP oder Port ungültig")
            return
        task = RfidReadertask(node.ipAddr, node.name)
        self.nodes.append([node, index, task])
        task.data.connect(self.handle_data_read)
        task.start()
        self.eventlog_service.writeEvent("RFIDService.start_node",
                                         f"starte RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort}...")

    def handle_data_read(self, ip: str, transponder_type: str, iid: str, dsfid: str, timestamp: str):
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

        for node, index, task in self.nodes:
            if node.ipAddr == ip:
                # print("found the right one")
                roles = list(self.role_names.keys())
                names = list(self.role_names.values())
                self.data.emit(
                    iid != "Error",
                    index,
                    roles[names.index(b'transponder_type')],
                    transponder_type,
                    roles[names.index(b'iid')],
                    iid,
                    roles[names.index(b'dsfid')],
                    dsfid,
                    roles[names.index(b'timestamp')],
                    timestamp
                )
                break

    def stop_node(self, node, index) -> bool:
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
            self.eventlog_service.writeEvent("RFIDService.stop_node",
                                             f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} gestoppt.")
            return True
        else:
            self.eventlog_service.writeEvent("RFIDService.stop_node",
                                             f"RFID-Node {node.name} mit IP {node.ipAddr} und Port {node.ipPort} konnte nicht gestoppt werden. Node nicht gefunden.")
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

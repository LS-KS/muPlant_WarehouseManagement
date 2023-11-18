from src.model.RfidModel import RfidModel
from src.viewmodel.RfidViewModel import RfidViewModel, RfidProxyViewModel
from src.constants.Constants import Constants
from PySide6.QtCore import QObject, Signal, Slot, Qt, QModelIndex
from yaml import safe_load, safe_dump


class RfidController(QObject):
    data_to_opcua = Signal(str, str, str, str, str, str, str)
    # Data to send: ip, timestamp, iid, dsfid, last_valid_timestamp, last_valid_iid, last_valid_dsfid
    create_opcua_node = Signal(str, str)

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.rfid_service = None
        self.constants = Constants()
        self.rfidViewModel = RfidViewModel()
        self._load_rfid_nodes()
        self.rfidProxyViewModel = RfidProxyViewModel()
        self.rfidProxyViewModel.setSourceModel(self.rfidViewModel)
        self.rfidViewModel.controller = self

    @Slot()
    def send_data_to_opcua(self):
        """
        Emits data_to_opcua signal to post new rfid data to opcua server
        """
        for idx, node in enumerate(self.rfidViewModel.rfidData):
            self.data_to_opcua.emit(node.ipAddr, node.timestamp, node.iid, node.dsfid, node.last_valid_timestamp,
                                    node.last_valid_iid, node.last_valid_dsfid)

    @Slot()
    def select_all(self):
        """
        Marks all RFID-Nodes as selected.
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for node in nodes:
            self.select_node(node, True)

    @Slot()
    def select_none(self):
        """
        Marks all RFID-Nodes as selected.
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for node in nodes:
            self.select_node(node, False)

    @Slot(int, bool)
    def select_node(self, id: int, selected: bool):
        """
        marks RFID-Node with id as selected.
        """
        rows = self.rfidViewModel.rowCount()
        for i in range(rows):
            print("i: " + str(i))
            node = self.rfidViewModel.rfidData[i]
            if node.idVal == id:
                oldVal = node.selected
                index = self.rfidViewModel.index(i, 0)
                self.rfidViewModel.setData(index, selected, 13)
                newVal = node.selected
                print(f"Data changed from {oldVal} to {newVal} in index {index.row()}")
                self.rfidViewModel.dataChanged.emit(index, index, [Qt.DisplayRole + 13])

    @Slot(int, str, str, str, str)
    def save_node_changes(self, id_val, name, reader_ip, reader_port, ):
        """
        saves changes made to RFID-Nodes.
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for i, node in enumerate(self.rfidViewModel.rfidData):
            if node.idVal == id_val:
                index = self.rfidViewModel.index(i, 0)
                self.rfidViewModel.setData(index, name, 0)
                self.rfidViewModel.setData(index, reader_ip, 3)
                self.rfidViewModel.setData(index, reader_port, 4)
                self._dump_rfid_nodes()
                return

    @Slot()
    def start_selected(self):
        """
        starts all RFID-Nodes.
        :returns: None
        
        """
        for row, node in enumerate(self.rfidViewModel.rfidData):
            if node.selected == True:
                index = self.rfidViewModel.createIndex(row, 0)
                self.rfid_service.start_node(node, index, self.rfidViewModel.roleNames())

    @Slot()
    def stop_selected(self):
        """
        stops all RFID-Nodes.
        :returns: None
        
        """
        for row, node in enumerate(self.rfidViewModel.rfidData):
            if node.selected == True:
                index = self.rfidViewModel.createIndex(row, 0)
                self.rfid_service.stop_node(node, index)

    @Slot()
    def remove_selected(self):
        """
        removes all selected RFID-Nodes.
        :returns: None
        
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for i, node in enumerate(self.rfidViewModel.rfidData):
            if node.selected == True:
                index = self.rfidViewModel.index(i, 0)
                self.rfidViewModel.removeRow(index.row(), QModelIndex())

    def _load_rfid_nodes(self):
        """
        Loads all RFID-Nodes from file RfidData.yaml and overwrites data in rfidViewModel.
        List comprehension syntax is used in heavily shortened syntax to parse data into RfidModel.
        This is possible through the dataclass decorator and YAML's safe_load function.
        :returns: None
        """
        with open(self.constants.RFID_DATA, 'r') as file:
            records = safe_load(file)
            if records is None:
                print("No RFID-Data found")
                return
            rfidData = [RfidModel(**record) for record in records]
            self.rfidViewModel.rfidData = rfidData

    @Slot(bool)
    def notify_opcua(self, online):
        """
        This method is connected to rfid_service's online signal in main.py.
        This makes it be called right after the opcua_service is initialized so that the
        opcua server gets at least last_valid - data after startup.
        :param online: True if server is started (should not be anything else)
        :type online: bool
        """
        if not online:
            return
        for node in self.rfidViewModel.rfidData:
            self.create_opcua_node.emit(str(node.ipAddr), str(node.name))

    @Slot(bool, QModelIndex, int, str, int, str, int, str, int, str)
    def update_model(self, error: bool, model_index: QModelIndex, transponder_role: int, transponder_type: str,
                     iid_role: int, iid: str, dsfid_role: int, dsfid: str, timestamp_role: int, timestamp: str):
        """
        Method, connected to RfidService's data signal, is used to update RfidViewModel instance of
        RfidController.
        If the first argument is True, a tag was read. In that case the submitted values are set as last_valid_ vals.
        :param error: True if iid >0 and not "Error"
        :type error: bool
        :param model_index: Index to directly index into viewmodel
        :type model_index: QModelIndex
        :param transponder_role: role to index into viewmodel role
        :type transponder_role: int
        :param transponder_type: value of transponder type
        :type transponder_type: str
        :param iid_role: role to index into viewmodel's iid role
        :type iid_role: int
        :param iid: value of IID
        :type iid: str
        :param dsfid_role: role to index into viewmodel's dsfid role
        :type dsfid_role: int
        :param dsfid: value of DSFID
        :type dsfid: str
        :param timestamp_role: role to index into viewmodel's timestamp role
        :type timestamp_role: int
        :param timestamp: value of timestamp
        :type timestamp: str
        """
        self.rfidViewModel.setData(model_index, transponder_type, transponder_role)
        self.rfidViewModel.setData(model_index, iid, iid_role)
        self.rfidViewModel.setData(model_index, dsfid, dsfid_role)
        self.rfidViewModel.setData(model_index, timestamp, timestamp_role)
        if error:
            roles = list(self.rfidViewModel.roleNames().keys())
            names = list(self.rfidViewModel.roleNames().values())
            self.rfidViewModel.setData(model_index, transponder_type,
                                       roles[names.index(b'last_valid_transponder_type')])
            self.rfidViewModel.setData(model_index, iid, roles[names.index(b'last_valid_iid')])
            self.rfidViewModel.setData(model_index, dsfid, roles[names.index(b'last_valid_dsfid')])
            self.rfidViewModel.setData(model_index, timestamp, roles[names.index(b'last_valid_timestamp')])

    def _dump_rfid_nodes(self):
        """
        Saves all RFID-Nodes from rfidViewModel to file RfidData.yaml.
        :returns: None
        """
        with open(self.constants.RFID_DATA, 'w') as file:
            model_dict = [record.__dict__ for record in self.rfidViewModel.rfidData]
            safe_dump(model_dict, file)

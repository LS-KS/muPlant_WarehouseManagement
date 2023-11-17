from typing import Optional
from src.model.RfidModel import RfidModel
from src.viewmodel.RfidViewModel import RfidViewModel, RfidProxyViewModel
from src.constants.Constants import Constants
from PySide6.QtCore import QObject, Signal, Slot, Qt, QModelIndex
from yaml import safe_load, safe_dump
from dataclasses import fields

class RfidController(QObject):

    data_to_opcua = Signal(str, str, str, str, str, str, str) # Data to send: ip, timestamp, iid, dsfid, last_valid_timestamp, last_valid_iid, last_valid_dsfid
    create_opcua_node = Signal(str, str)

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.constants = Constants()
        self.rfidViewModel = RfidViewModel()
        self._loadRfidNodes()
        self.rfidProxyViewModel = RfidProxyViewModel()
        self.rfidProxyViewModel.setSourceModel(self.rfidViewModel)
        self.rfidViewModel.controller = self

    @Slot()
    def send_data_to_opcua(self):
        for idx, node in enumerate(self.rfidViewModel.rfidData):
            self.data_to_opcua.emit(node.ipAddr, node.timestamp, node.iid, node.dsfid, node.last_valid_timestamp, node.last_valid_iid, node.last_valid_dsfid)

    @Slot()
    def selectAll(self):
        """
        Marks all RFID-Nodes as selected.
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for node in nodes:
            self.selectNode(node, True)


    @Slot()
    def selectNone(self):
        """
        Marks all RFID-Nodes as selected.
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for node in nodes:
            self.selectNode(node, False)

    @Slot(int, bool)
    def selectNode(self, id: int, selected: bool):
        """
        marks RFID-Node with id as selected.
        :returns: None
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
                
            
    @Slot(int,str, str, str, str,)        
    def saveNodeChanges(self, idVal, name, readerIp, readerPort,):
        """
        saves changes made to RFID-Nodes.
        :returns: None
        
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for i, node in enumerate(self.rfidViewModel.rfidData):
            if node.idVal == idVal:
                index = self.rfidViewModel.index(i, 0)
                self.rfidViewModel.setData(index, name, 0)
                self.rfidViewModel.setData(index, readerIp, 3)
                self.rfidViewModel.setData(index, readerPort, 4)
                self._dumpRfidNodes()
                return

    @Slot()
    def startSelected(self):
        """
        starts all RFID-Nodes.
        :returns: None
        
        """
        for row, node in enumerate(self.rfidViewModel.rfidData):
            if node.selected == True:
                index = self.rfidViewModel.createIndex(row, 0)
                self.rfid_service.start_node(node, index, self.rfidViewModel.roleNames())
    @Slot()
    def stopSelected(self):
        """
        stops all RFID-Nodes.
        :returns: None
        
        """
        for row, node in enumerate(self.rfidViewModel.rfidData):
            if node.selected == True:
                index = self.rfidViewModel.createIndex(row, 0)
                self.rfid_service.stop_node(node, index)

    @Slot()
    def removeSelected(self):
        """
        removes all selected RFID-Nodes.
        :returns: None
        
        """
        nodes = [node.idVal for node in self.rfidViewModel.rfidData]
        for i, node in enumerate(self.rfidViewModel.rfidData):
            if node.selected == True:
                index = self.rfidViewModel.index(i, 0)
                self.rfidViewModel.removeRow(index.row(), QModelIndex())

    def _loadRfidNodes(self):
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
        print(f"notify_opcua called with {online}")
        if not online:
            return
        for node in self.rfidViewModel.rfidData:
            self.create_opcua_node.emit(str(node.ipAddr), str(node.name) )

    @Slot(bool)    
    def update_opcua(self):
        print(f"update_opcua called with")
        for node in self.rfidViewModel.rfidData:
            self.data_to_opcua.emit(
                str(node.ipAddr), 
                str(node.timestamp), 
                str(node.iid), 
                str(node.dsfid), 
                str(node.last_valid_iid), 
                str(node.last_valid_dsfid), 
                str(node.last_valid_timestamp)
                )

    def _dumpRfidNodes(self):
        """
        Saves all RFID-Nodes from rfidViewModel to file RfidData.yaml.
        :returns: None
        """
        with open(self.constants.RFID_DATA, 'w') as file:
            dict = [record.__dict__ for record in self.rfidViewModel.rfidData]
            safe_dump(dict, file)

    
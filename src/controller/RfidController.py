from typing import Optional
from src.model.RfidModel import RfidModel
from src.viewmodel.RfidViewModel import RfidViewModel, RfidProxyViewModel
from src.constants.Constants import Constants
from PySide6.QtCore import QObject, Signal, Slot, Qt
from yaml import safe_load, safe_dump

class RfidController(QObject):

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.constants = Constants()
        self.rfidViewModel = RfidViewModel()
        self._loadRfidNodes()
        self.rfidProxyViewModel = RfidProxyViewModel()
        self.rfidProxyViewModel.setSourceModel(self.rfidViewModel)
    
    @Slot()
    def selectAll(self):
        """
        marks all RFID-Nodes as selected.
        :returns: None
        
        """
        rows = self.rfidViewModel.rowCount()
        for i in range(rows):
            oldValue = self.rfidViewModel.data(self.rfidViewModel.index(i), Qt.UserRole + 14)
            self.rfidViewModel.setData(self.rfidViewModel.index(i), True, Qt.UserRole + 14)
            newValue = self.rfidViewModel.data(self.rfidViewModel.index(i), Qt.UserRole + 14)
            print(f"Data changed from {oldValue} to {newValue} in index {i}")
    @Slot()
    def selectNone(self):
        """
        marks all RFID-Nodes as unselected.
        :returns: None
        
        """
        for element in self.rfidViewModel.rfidData:
            element.selected = False

    @Slot(int)
    def select(self, id: int):
        """
        marks RFID-Node with id as selected.
        :returns: None
        """
        for element in RfidViewModel.rfidData:
            if element.id == id:
                element.selected = True
                return

    @Slot()
    def startSelected(self):
        """
        starts all RFID-Nodes.
        :returns: None
        
        """
        print("not implemented yet")

    @Slot()
    def stopSelected(self):
        """
        stops all RFID-Nodes.
        :returns: None
        
        """
        print("not implemented yet")

    @Slot()
    def removeSelected(self):
        """
        removes all selected RFID-Nodes.
        :returns: None
        
        """
        print("not implemented yet")

    def _loadRfidNodes(self):
        """
        Loads all RFID-Nodes from file RfidData.yaml and overwrites data in rfidViewModel.
        :returns: None
        """

        with open(self.constants.RFID_DATA, 'r') as file:
            records = safe_load(file)
            rfidData = []
            if records is None:
                print("No RFID-Data found")
                return
            for record in records:
                rfidModel = RfidModel(
                    name= record['name'],
                    id= record['id'],
                    workingState= record['workingState'],
                    ipAddr= record['ipAddr'],
                    ipPort= record['ipPort'],
                    rfidStatus= record['rfidStatus'],
                    endPointipAddr= record['endPointipAddr'],
                    endPointipPort= record['endPointipPort'],
                    endPointModbus= record['endPointModbus'],
                    endPointStatus= record['endPointStatus'],
                    tagId= record['tagId'],
                    productID= record['productID'],
                    cupSize= record['cupSize']
                )
                rfidData.append(rfidModel)
            self.rfidViewModel.rfidData = rfidData

    def _dumpRfidNodes(self):
        """
        Saves all RFID-Nodes from rfidViewModel to file RfidData.yaml.
        :returns: None
        """
        with open(self.constants.RFID_DATA, 'w') as file:
            safe_dump(self.rfidViewModel.rfidData, file)


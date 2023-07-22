from PySide6.QtCore import QObject, Signal


class RfidModel(QObject):
    """
    This class is used to store data from RFID-Reader and RFID-Endpoint.
    It repensents a record in RfidViewModel class which is rendered in RFID Server plugin.
    """
    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.name : str 
        self.id : int = 0
        self.workingState : int = 0
        self.ipAddr : str = ""
        self.ipPort : int = 0
        self.rfidStatus : int = -1

        self.endPointipAddr : str = ""
        self.endPointipPort : int = 0
        self.endPointModbus : int = 0
        self.endPointStatus : int = -1

        self.tagId : int = 0
        self.productID : int = 0
        self.cupSize : int = 0

        self.selected : bool = False
from PySide6.QtCore import QObject, Signal
from dataclasses import dataclass


@dataclass
class RfidModel(QObject):
    """
    This class is used to store data from RFID-Reader and RFID-Endpoint.
    It represents a record in the RfidViewModel class, which is rendered in the RFID Server plugin.
    """
    name: str = ""
    id: int = 0
    workingState: int = 0
    ipAddr: str = ""
    ipPort: int = 0
    rfidStatus: int = 0
    endPointipAddr: str = ""
    endPointipPort: int = 0
    endPointModbus: int = 0
    endPointStatus: int = 0
    tagId: int = 0
    productID: int = 0
    cupSize: int = 0
    selected: bool = False

        
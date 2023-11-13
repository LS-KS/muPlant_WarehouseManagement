from PySide6.QtCore import QObject, Signal
from PySide6.QtGui import QStandardItemModel, QStandardItem
from dataclasses import dataclass
import datetime


@dataclass
class RfidModel(QStandardItem):
    """
    This class is used to store data from RFID-Reader and RFID-Endpoint.
    It represents a record in the RfidViewModel class, which is rendered in the RFID Server plugin.
    """
    name: str = ""
    idVal: int = 0
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
    reader = None
    data = None
    iid:str = None
    dsfid:str = None
    transponder_type:str = None
    timestamp: datetime.date = None
    last_valid_iid:str = None
    last_valid_dsfid:str = None
    last_valid_transponder_type:str = None
    last_valid_timestamp: datetime.date = None

        
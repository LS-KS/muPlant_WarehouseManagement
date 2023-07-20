from typing import Any, Dict, Optional, Union
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
from PySide6.QtCore import Qt, QObject
from src.model.RfidModel import RfidModel
class RfidViewModel(QtCore.QAbstractListModel):

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.rfidData :RfidModel = []

    def rowCount(self, parent=QModelIndex()):
        """
        Must be implemented.

        :param parent:
        :type parent: QModelIndex
        :return: returns number of rows from data at given index

        """
        return len(self.rfidData)
    
    def roleNames(self):
        """
        Must be implemented.
        :return: returns a dictionary of roles to index in data.
        """
        roles = {
            Qt.UserRole + 1: b'name',
            Qt.UserRole + 2: b'id',
            Qt.UserRole + 3: b'workingState',
            Qt.UserRole + 4: b'ipAddr',
            Qt.UserRole + 5: b'ipPort',
            Qt.UserRole + 6: b'rfidStatus',
            Qt.UserRole + 7: b'endPointipAddr',
            Qt.UserRole + 8: b'endPointipPort',
            Qt.UserRole + 9: b'endPointModbus',
            Qt.UserRole + 10: b'endPointStatus',
            Qt.UserRole + 11: b'tagId',
            Qt.UserRole + 12: b'productID',
            Qt.UserRole + 13: b'cupSize'
        }
        return roles
            
    
    def data(self, index: QModelIndex, role: int):
        """
        Returns Data from viewmodel.

        :param index: Used to index into the model
        :type index: QModelIndex
        :param role: Used to index into the model
        :type role: int
        :return: returns data from viewmodel at given index and role
        """
        if index < 0 or index >= self.rowCount():
            return None
        else:
            rfidData = self.rfidData[index]
            if role == Qt.UserRole + 1:
                return rfidData.name
            if role == Qt.UserRole + 2:
                return rfidData.id
            if role == Qt.UserRole + 3:
                return rfidData.workingState
            if role == Qt.UserRole + 4:
                return rfidData.ipAddr
            if role == Qt.UserRole + 5:
                return rfidData.ipPort
            if role == Qt.UserRole + 6:
                return rfidData.rfidStatus
            if role == Qt.UserRole + 7:
                return rfidData.endPointipAddr
            if role == Qt.UserRole + 8:
                return rfidData.endPointipPort
            if role == Qt.UserRole + 9:
                return rfidData.endPointModbus
            if role == Qt.UserRole + 10:
                return rfidData.endPointStatus
            if role == Qt.UserRole + 11:
                return rfidData.tagId
            if role == Qt.UserRole + 12:
                return rfidData.productID
            if role == Qt.UserRole + 13:
                return rfidData.cupSize
            return None
                

        
    

class RfidProxyViewModel(QtCore.QSortFilterProxyModel):

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
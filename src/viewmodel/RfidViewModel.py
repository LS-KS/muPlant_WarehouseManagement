from typing import Any, Dict, Optional, Union
from dataclasses import dataclass, fields
import typing
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
from PySide6.QtCore import Qt, QObject, QByteArray
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
        
    def roleNames(self) -> dict[int, QByteArray]:
        """
        Must be implemented.
        :return: returns a dictionary of roles to index in data.
        """
        d = {}
        for i, field in enumerate(fields(RfidModel)):
            d[Qt.DisplayRole + i] = field.name.encode()
        return d
            
    
    def data(self, index: QModelIndex, role: int = Qt.DisplayRole) -> typing.Any:
        """
        Returns Data from viewmodel.

        :param index: Used to index into the model
        :type index: QModelIndex
        :param role: Used to index into the model
        :type role: int
        :return: returns data from viewmodel at given index and role
        """
        
        if 0 <= index.row() < self.rowCount():
            node = self.rfidData[index.row()]
            field = self.roleNames().get(role)
            if field:
                return getattr(node, field.decode())

        
    def setData(self, index: QModelIndex, value: Any, role: int) -> bool:
        """

        Writes data to an index and returns true if success

        :param index: Index at which data shall be changed
        :type index: QModelIndex
        :param value: New value to be written at index
        :type value: int for any ID, string for products names and bool for pallet existance
        :param role: Rolename to be written to
        :return: returns False if writing was not successful. Otherwise, it returns the old value.

        """
        if index.row() >= self.rowCount() and not index.isvalid():
            return False
        if role == Qt.UserRole + 1:
            self.rfidData[index.row()].name = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 2:
            self.rfidData[index.row()].id = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 3:
            self.rfidData[index.row()].workingState = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 4:
            self.rfidData[index.row()].ipAddr = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 5:
            self.rfidData[index.row()].ipPort = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 6:
            self.rfidData[index.row()].rfidStatus = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 7:
            self.rfidData[index.row()].endPointipAddr = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 8:
            self.rfidData[index.row()].endPointipPort = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 9:
            self.rfidData[index.row()].endPointModbus = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 10:
            self.rfidData[index.row()].endPointStatus = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 11:
            self.rfidData[index.row()].tagId = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 12:
            self.rfidData[index.row()].productID = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 13:
            self.rfidData[index.row()].cupSize = value
            self.dataChanged.emit(index, index, [role])
            return True
        if role == Qt.UserRole + 14:
            self.rfidData[index.row()].selected = value
            self.dataChanged.emit(index, index, [role])
            return True
        return False



        
    

class RfidProxyViewModel(QtCore.QSortFilterProxyModel):

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
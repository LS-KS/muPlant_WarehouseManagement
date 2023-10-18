from typing import Any, Dict, Optional, Union
from dataclasses import dataclass, fields
import typing
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
from PySide6.QtCore import Qt, QObject, QByteArray, Signal, Slot
from src.model.RfidModel import RfidModel



class RfidViewModel(QtCore.QAbstractListModel):

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.rfidData : list[RfidModel] = []
        self.controller  = None

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
            # print("field: "+ str(field), "role: " + str(role))
            if field:
                return getattr(node, field.decode())

        
    def setData(self, index: QModelIndex, value: Any, role: int) -> bool:
        """
        Writes data to an index and returns true if success

        :param index: Index at which data shall be changed
            :type index: QModelIndex
            :param value: New value to be written at index
        :type value: int for any ID, string for products names and bool for pallet existence
        :param role: Rolename to be written to
        :return: returns False if writing was not successful. Otherwise, it returns the old value.
        """
        role = Qt. DisplayRole + role
        if index.row() >= self.rowCount() or not index.isValid():
            return False

        roleNames = self.roleNames()
        field = roleNames.get(role)
        # print(str(field))
        if field:
            setattr(self.rfidData[index.row()], field.decode(), value)
            self.dataChanged.emit(index, index, [role])
            return True
        #print("field not found for role " + str(role))
        return False
    
    @Slot()
    def add(self):
        row = self.rowCount()
        self.beginInsertRows(QModelIndex(), row, row)
        idVal = self._createNewID()
        self.rfidData.insert(row, RfidModel(idVal=idVal))
        self.endInsertRows()

    def removeRow(self, row: int, parent: QModelIndex) -> bool:
        """
        Removes a row from the model.
        :param row: Row to be removed
        :type row: int
        :param parent: parent index
        :type parent: QModelIndex
        :return: returns True if row was removed successfully
        """
        self.beginRemoveRows(parent, row, row)
        self.rfidData.pop(row)
        self.endRemoveRows()
        return True

    def _createNewID(self)-> int:
        """
        Creates the possible lowest integer as ID for a new RFID-Node.
        :returns: int
        """
        ids = [node.idVal for node in self.rfidData]
        ids.append(0)
        return min(i for i in range(len(ids)+1) if i not in ids)



        
    

class RfidProxyViewModel(QtCore.QSortFilterProxyModel):

    def __init__(self, parent: QObject | None = None) -> None:
        super().__init__(parent)
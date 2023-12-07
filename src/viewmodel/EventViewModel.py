from PySide6.QtCore import Signal, Slot, QObject
from PySide6.QtCore import Qt, QAbstractTableModel, QByteArray, QModelIndex, QSortFilterProxyModel
from src.model.EventModel import EventMessage
from typing import List, Dict, Any, Optional, Union


class EventViewModel(QAbstractTableModel):

    def __init__(self, messages):
        super().__init__()
        self.messages: List[EventMessage] = messages

    def rowCount(self, parent):
        return len(self.messages)

    def columnCount(self, parent):
        return 3

    def roleNames(self) -> Dict[int, QByteArray]:
        roles = {
            Qt.DisplayRole + 0: b"text",
            Qt.DisplayRole + 1: b"column",
        }
        return roles

    def add(self, msg : EventMessage):
        self.beginInsertRows(QModelIndex(), 0, 0)
        self.messages.insert(0, msg)
        self.endInsertRows()

    def data(self, index: QModelIndex, role: int) -> Any:
        if index.row() < 0 or index.row() >= len(self.messages):
            return "row out of range"
        if index.column() < 0 or index.column() >= 3:
            return "column out of range"
        row = index.row()
        col = index.column()
        if col == 0:
            msg = self.messages[row].time
            msg = msg.strftime("%d.%m.%Y, %H:%M:%S")
        elif col == 1:
            msg = self.messages[row].source
        elif col == 2:
            msg = self.messages[row].message
        else:
            return "None"
        if role == Qt.DisplayRole + 0:
            return str(msg)
        elif role == Qt.DisplayRole + 1:
            return col



    def headerData(self, section: int, orientation: Qt.Orientation, role: int):
        if orientation == Qt.Horizontal and role == Qt.DisplayRole:
            if section == 0:
                return "Time"
            elif section == 1:
                return "Source"
            elif section == 2:
                return "Message"
        return super().headerData(section, orientation, role)

    @Slot()
    def clear(self):
        """
        Method gets called from user GUI. 
        clears the Model. 
        """
        self.beginRemoveRows(QModelIndex(), 0, self.rowCount(QModelIndex())-1)
        self.messages.clear()
        self.endRemoveRows()
        print("Cleared eventModel")
    
class EventSortModel(QSortFilterProxyModel):
    
    def __init__(self, parent: QObject | None = None):
        super().__init__(parent)
        self.model: EventViewModel = None

    def lessThan(self, source_left: QModelIndex, source_right: QModelIndex ) -> bool:
        left_row = source_left.row()
        right_row = source_right.row()
        if left_row < 0 or left_row >= len(self.model.messages) or right_row < 0 or right_row >= len(self.model.messages):
            return False
        left_time = self.model.messages[left_row].time
        right_time = self.model.messages[right_row].time
        return left_time > right_time

    
    def setSourceModel(self, sourceModel: QAbstractTableModel):
        super().setSourceModel(sourceModel)
        self.model = sourceModel

    def filterAcceptsRow(self, source_row: int, source_parent: QModelIndex) -> bool:
        return True
        


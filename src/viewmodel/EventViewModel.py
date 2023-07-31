from PySide6.QtCore import Signal, Slot, QObject
from PySide6.QtCore import Qt, QAbstractTableModel, QByteArray, QModelIndex
from src.model.EventModel import EventMessage
from typing import List, Dict, Any, Union
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
        self.beginInsertRows(QModelIndex(), 0, 1)
        self.messages.append(msg)
        self.endInsertRows()
    def data(self, index: QModelIndex, role: int) -> Any:
        if index.row() < 0 or index.row() >= len(self.messages):
            return None
        if index.column() < 0 or index.column() >= 3:
            return None
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
            return None
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


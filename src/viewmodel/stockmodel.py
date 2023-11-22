from typing import Union
import PySide6
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex


class stockmodel(QtCore.QAbstractTableModel):

    def __init__(self, parent = None):
        super().__init__(parent)

    def data(self, index: QModelIndex):
        return "0"

    def rowCount(self, index: QModelIndex):
        return 1
    def columnCount(self, index:QModelIndex):
        return 1
    def roleNames(self):
        return {b'none'}
    
class tablemodel(QtCore.QAbstractListModel):

    def __init__(self, parent = None):
        super().__init__(parent)

    def data(self, index: QModelIndex):
        return "none"
    
    def rowCount(self, parent: QModelIndex) -> int:
        return 1
from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex


class CommissionViewModel(QtCore.QAbstractListModel):

    def __int__(self):
        super().__init__()
        self.commissionData = []
        self.loadCommissionData()

    def loadCommissionData(self):
        pass

    def rowCount(self, parent=QModelIndex()):
        return len(self.commissionData)

    def data(self, index, role):
        pass

    def roleNames(self):
        pass



class CommissionFilterProxyModel(QSortFilterProxyModel):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.filterString = ""

    def filterAcceptsRow(self, sourceRow, sourceParent):
        pass

    @Slot(str)
    def setFilterString(self, filterString):
        pass

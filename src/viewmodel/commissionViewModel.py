from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt, QModelIndex
from PySide6 import QtCore

class CommissionViewModel(QtCore.QAbstractTableModel):
    lastId = 0
    commissionData = []
    def __init__(self, commissionData, parent=None):
        super().__init__()
        self.commissionData = commissionData
        self._headers = ["ID", "Source", "Target", "Object", "Cup", "Pallet", "State"]

    def headerData(self, section: int, orientation: QtCore.Qt.Orientation, role: int = Qt.DisplayRole):
            if role == Qt.DisplayRole and orientation == Qt.Horizontal:
                return self._headers[section]

    def setHeaderData(self, section, orientation, data, role=Qt.EditRole):
        if orientation == Qt.Horizontal and role in (Qt.DisplayRole, Qt.EditRole):
            try:
                self._headers[section] = data
                return True
            except:
                return False
        return super().setHeaderData(section, orientation, data, role)

    def rowCount(self, parent=QModelIndex()):
        return len(self.commissionData)

    def columnCount(self, parent= None) -> int:
        return 7

    def data(self, index, role):
        """
        Returns an appropriate value for the requested data.
        If the view requests an invalid index, an invalid variant is returned.
        Any valid index that corresponds to a string in the list causes that
        string to be returned
        :param index: index used to obtain data from model
        :type index: QModelIndex
        :param role: used to obtain field value from data at index
        :type role: QtUserRole +1 per column
        :return: returns data at index and role or None if not successful
        """
        row = index.row()
        col = index.column()
        if not index.isValid() or row >= self.rowCount() or col >= self.columnCount():
            return None
        else:
            match col:
                case 0: return self.commissionData[row].id
                case 1: return self.commissionData[row].source.value
                case 2: return self.commissionData[row].target.value
                case 3: return self.commissionData[row].object
                case 4: return self.commissionData[row].cup
                case 5: return self.commissionData[row].pallet
                case 6: return self.commissionData[row].state
                case _: return None

    def roleNames(self):
        """
        Must be implemendted.
        Creates a dictionary with rolenames and roles.
        :return: dictionary with rolenames and roles
        """
        roles = {
            QtCore.Qt.UserRole + 1: b'text',
        }
        return roles

    def indexOf(self, commissionID):
        """

        :param commissionID: commission ID
        :type commissionID: int
        :return: returns index of given commission ID

        """

        for index, commission in enumerate(self.commissionData):
            if commissionID == commission:
                return index



class CommissionFilterProxyModel(QSortFilterProxyModel):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.filterString = ""

    def filterAcceptsRow(self, sourceRow, sourceParent):
        return True

    @Slot(str)
    def setFilterString(self, filterString):
        self.filterString = filterString






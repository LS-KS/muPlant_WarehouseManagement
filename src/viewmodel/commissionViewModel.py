from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
from src.constants.Constants import Constants
from src.model.CommissionModel import CommissionData, CommissionState
class CommissionViewModel(QtCore.QAbstractListModel):
    lastId = 0
    commissionData = []
    def __int__(self):
        super().__init__()
        self.loadCommissionData()

    def loadCommissionData(self):
        if self.commissionData:
            self.commissionData.clear()
        with open(Constants().COMMISSIONDATA)as file:
            try:
                for line in file:
                    line = line.strip()
                    if line:
                        id, source, target, object,cup, pallet, state = line.split(",")
                        commission = CommissionData(id, source, target, object)
                        commission.state = CommissionState.OPEN
                        self.commissionData.append(commission)
                        self.lastId = id
            except FileNotFoundError:
                print("Commission Data File not found")



    def rowCount(self, parent=QModelIndex()):
        return len(self.commissionData)

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
        if not index.isValid() or row >= self.rowCount():
            return None
        commission = self.commissionData[row]
        if role == QtCore.Qt.UserRole + 1:
            return commission.id
        elif role == QtCore.Qt.UserRole + 2:
            return commission.source
        elif role == QtCore.Qt.UserRole + 3:
            return commission.target
        elif role == QtCore.Qt.UserRole + 4:
            return commission.object
        elif role == QtCore.Qt.UserRole + 5:
            return commission.state
        return None

    def roleNames(self):
        """
        Must be implemendted.
        Creates a dictionary with rolenames and roles.
        :return: dictionary with rolenames and roles
        """
        roles = {
            QtCore.Qt.UserRole + 1: b'id',
            QtCore.Qt.UserRole + 2: b'source',
            QtCore.Qt.UserRole + 3: b'target',
            QtCore.Qt.UserRole + 4: b'object',
            QtCore.Qt.UserRole + 5: b'state'
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
        pass

    @Slot(str)
    def setFilterString(self, filterString):
        pass






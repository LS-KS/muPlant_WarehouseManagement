from typing import Union
from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt, QModelIndex
from PySide6 import QtCore

class CommissionViewModel(QtCore.QAbstractTableModel):

    """
    ViewModel für Kommissionsdaten. Stellt die Kommissionsdaten in einer Tabelle für 
    die QML Engine bereit. 
    Achtung: im QML Type wird das ProxyModel verwendet, nicht das ViewModel direkt.

    :param commissionData: Kommissionsdaten
    :type commissionData: list
    :param parent: parent
    :type parent: QObject
    """
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
                case 4: return "Cup" if self.commissionData[row].cup else ""
                case 5: return "Pallet" if self.commissionData[row].pallet else ""
                case 6: return self.commissionData[row].state.value
                case _: return None



    def roleNames(self):
        """
        Must be implemendted.
        Creates a dictionary with rolenames and roles.
        :return: dictionary with rolenames and roles
        """
        roles = {
            QtCore.Qt.UserRole + 1: b'text',
            QtCore.Qt.UserRole + 2: b'state',
        }
        return roles

    def indexOf(self, commissionID):
        """
        Returns index of given commission ID

        :param commissionID: commission ID
        :type commissionID: int
        :return: returns index of given commission ID

        """

        for index, commission in enumerate(self.commissionData):
            if commissionID == commission:
                return index



class CommissionFilterProxyModel(QSortFilterProxyModel):
    """
    ProxyModel für Kommissionsdaten. Stellt die Kommissionsdaten in einer Tabelle für 
    die QML Engine bereit.
    Die Liste ist nach dem Bearbeitungsstatus sortiert.
    """
    def __init__(self, parent=None):
        super().__init__(parent)
        self.filterString = ""

    def filterAcceptsRow(self, sourceRow, sourceParent):
        return True

    @Slot(str)
    def setFilterString(self, filterString):
        self.filterString = filterString

    def lessThan(self, left_index, right_index):
            if left_index.column() == 6:
                left_data = self.sourceModel().data(left_index, QtCore.Qt.UserRole +1)
                right_data = self.sourceModel().data(right_index, QtCore.Qt.UserRole +1)

                # Define the desired sorting order
                status_order = ["in progress", "pending", "open", "done"]              
                # Compare the status values based on the desired sorting order
                return status_order.index(left_data) < status_order.index(right_data)
                
            # For other columns, use the default sorting behavior
            return super().lessThan(left_index, right_index)
    
    def mapToSource(self, proxyIndex: QModelIndex ) -> QModelIndex:
        """
        Maps the sorted inices back to the source model.
        """
        return super().mapToSource(proxyIndex)
        

    







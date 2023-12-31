from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
from PySide6.QtCore import Qt


class StorageViewModel(QtCore.QAbstractTableModel):
    """
    implements Qt's QAbstractTableModel to share inventoryControllers Inventory 
    data with qml engine. This Viewmodel is populated and updated by inventoryController. 

    """

    def __init__(self, storageData, parent=None):
        """

        Init QAbstractTableModel class and writes data given to constructor

        :param storageData: Data holded in viewModel.
        :type storageData: StorageData
        :param parent:  Must be set but is (almost?) always None.

        """
        super().__init__(parent)
        self.storageData = storageData

    def rowCount(self, parent=QModelIndex()):
        """

        Must be implemented.

        :param parent:
        :type parent: QModelIndex
        :return: returns number of rows from data at given index

        """
        return len(self.storageData)

    def columnCount(self, parent=QModelIndex()):
        """

        Must be implemented.

        :param parent:
        :type parent: QModelIndex
        :return:  returns number of columns in model.

        """
        return 6

    def roleNames(self):
        """

        Must be implemented.

        :return: returns a dictionary of roles to index in data.

        """
        roles = {
            QtCore.Qt.DisplayRole + 1: b'isPallet',
            QtCore.Qt.DisplayRole + 2: b'a_CupID',
            QtCore.Qt.DisplayRole + 3: b'a_ProductID',
            QtCore.Qt.DisplayRole + 4: b'a_Name',
            QtCore.Qt.DisplayRole + 5: b'b_CupID',
            QtCore.Qt.DisplayRole + 6: b'b_ProductID',
            QtCore.Qt.DisplayRole + 7: b'b_Name',
            QtCore.Qt.DisplayRole + 8: b'row',
            QtCore.Qt.DisplayRole + 9: b'col',

        }
        return roles

    def data(self, index, role):
        """

        Returns Data from viewmodel.

        :param index: Used to index into the model
        :type index: QModelIndex
        :param role: Rolename used to get data from index
        :type role: QtDisplayRole +1 byte for each field
        :return: returns model data in field or None

        """
        row = index.row()
        col = index.column()
        if not index.isValid() or row >= self.rowCount() or col >= self.columnCount():
            return None
        inventory = self.storageData[row][col]
        if role == QtCore.Qt.DisplayRole + 1:
            print(f"storageviemodel: data() called and is about to return: isPallet: {inventory[0]} at index: {index.row()}/{index.column()}")
            return inventory[0]
        if role == QtCore.Qt.DisplayRole + 2:
            print(f"storageviemodel: data() called and is about to return: a_CupID: {inventory[1]} at index: {index.row()}/{index.column()}")
            return inventory[1]
        if role == QtCore.Qt.DisplayRole + 3:
            print(f"storageviemodel: data() called and is about to return: a_ProductID: {inventory[2]} at index: {index.row()}/{index.column()}")
            return inventory[2]
        if role == QtCore.Qt.DisplayRole + 4:
            print(f"storageviemodel: data() called and is about to return: a_Name: {inventory[3]} at index: {index.row()}/{index.column()}")
            return inventory[3]
        if role == QtCore.Qt.DisplayRole + 5:
            print(f"storageviemodel: data() called and is about to return: b_CupID: {inventory[4]} at index: {index.row()}/{index.column()}")
            return inventory[4]
        if role == QtCore.Qt.DisplayRole + 6:
            print(f"storageviemodel: data() called and is about to return: b_ProductID: {inventory[5]} at index: {index.row()}/{index.column()}")
            return inventory[5]
        if role == QtCore.Qt.DisplayRole + 7:
            print(f"storageviemodel: data() called and is about to return: b_Name: {inventory[6]} at index: {index.row()}/{index.column()}")
            return inventory[6]
        if role == QtCore.Qt.DisplayRole + 8:
            return inventory[7]
        if role == QtCore.Qt.DisplayRole + 9:
            return inventory[8]
        return None

    def setData(self, index, value, role)->bool:
        """

        Writes data to an index and returns the old value if success

        :param index: Index at which data shall be changed
        :type index: QModelIndex
        :param value: New value to be written at index
        :type value: int for any ID, string for products names and bool for pallet existance
        :param role: Rolename to be written to
        :return: returns False if writing was not successful. Otherwise, it returns the old value.
                Important Note: If isPallet is written, it maybe returns False in any case.

        """
        row = index.row()
        col = index.column()
        if not index.isValid() or row >= self.rowCount() or col >= self.columnCount():
            return False
        if role == Qt.DisplayRole + 1:  # isPallet
            oldValue = self.storageData[row][col][0]
            self.storageData[row][col][0] = value
            return True
        if role == Qt.DisplayRole + 2:  # a_CupID
            oldValue = self.storageData[row][col][1]
            self.storageData[row][col][1] = value
            return True
        if role == Qt.DisplayRole + 5:  # b_CupID
            oldValue = self.storageData[row][col][4]
            self.storageData[row][col][4] = value
            return True
        if role == Qt.DisplayRole + 3:  # a_productID
            oldValue = self.storageData[row][col][2]
            self.storageData[row][col][2] = value
            return True
        if role == Qt.DisplayRole + 6:  # b_productID
            oldValue = self.storageData[row][col][5]
            self.storageData[row][col][5] = value
            return True
        if role == Qt.DisplayRole + 4:  # a_Name
            oldValue = self.storageData[row][col][3]
            self.storageData[row][col][3] = value
            return True
        if role == Qt.DisplayRole + 7:  # b_Name
            oldValue = self.storageData[row][col][6]
            self.storageData[row][col][6] = value
            return True
        self.dataChanged.emit(index, index, [role])
        return False


# Data class for Inventory:
class StorageData:
    """

    Basic subclass which represents a spot in Storage visualisation.

    :param row: represents row in storage rack
    :type row: int
    :param col: represents column in storage rack
    :type col: int
    :param isPallet: True: Pallet is in spot, False: No pallet in spot
    :type isPallet: bool
    :param a_CupID: Cup ID in front of pallet
    :type a_CupID: int
    :param a_ProductID: Product ID in front of pallet
    :type a_ProductID: int
    :param a_Name: Name of product in front of pallet
    :type a_Name: str
    :param b_CupID: Cup ID in rear of pallet
    :type b_CupID: int
    :param b_ProductID: Product ID in rear of pallet
    :type b_ProductID: int
    :param b_Name: Name of product in rear of pallet
    :type b_Name: str

    """
    row: int
    col: int
    isPallet: bool
    a_CupID: int
    a_ProductID: int
    a_Name: str
    b_CupID: int
    b_ProductID: int
    b_Name: str

    def __init__(self, row, col, isPallet, a_CupID, a_ProductID, a_Name, b_CupID, b_ProductID, b_Name):
        """

        Basic subclass which represents a spot in Storage visualisation.

        :param row: represents row in storage rack
        :type row: int
        :param col: represents column in storage rack
        :type col: int
        :param isPallet: True: Pallet is in spot, False: No pallet in spot
        :type isPallet: bool
        :param a_CupID: Cup ID in front of pallet
        :type a_CupID: int
        :param a_ProductID: Product ID in front of pallet
        :type a_ProductID: int
        :param a_Name: Name of product in front of pallet
        :type a_Name: str
        :param b_CupID: Cup ID in rear of pallet
        :type b_CupID: int
        :param b_ProductID: Product ID in rear of pallet
        :type b_ProductID: int
        :param b_Name: Name of product in rear of pallet
        :type b_Name: str

        """
        self.row = row
        self.col = col
        self.isPallet = isPallet
        self.a_CupID = a_CupID
        self.a_ProductID = a_ProductID
        self.a_Name = a_Name
        self.b_CupID = b_CupID
        self.b_ProductID = b_ProductID
        self.b_Name = b_Name

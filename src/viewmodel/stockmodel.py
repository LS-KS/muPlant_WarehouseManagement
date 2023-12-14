from typing import Union
import PySide6
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex, QObject, Signal, Slot
from dataclasses import dataclass, fields
from src.controller.invController import invController
from src.model.DataModel import Pallet, Cup, Product

class stock_delegate(QObject):
    """
    Delegate class for viewmodels stockmodel and tablemodel.
    This class is used to represent the datamodel's data in a way to control QML-properties for rendering the stocktaking process.

    Attributes:
        previous_pallet (bool): Flag indicating the previous pallet status (pallet present in datamodel before stocktaking).
        previous_cupA (int): Previous value of cupA-ID (=0 if no cup was present before stocktaking).
        previous_cupB (int): Previous value of cupB-ID (=0 if no cup was present before stocktaking).
        new_pallet (bool): Flag indicating the new pallet status (pallet present in datamodel after stocktaking).
        new_cupA (int): New value of cupA-ID (=0 if no cup was present after stocktaking).
        new_cupB (int): New value of cupB-ID (=0 if no cup was present after stocktaking).
        tested (bool): Flag indicating if the stock has been tested.

    """
    previous_pallet = False
    previous_cupA = 0
    previous_cupB = 0
    new_pallet = False
    new_cupA = 0
    new_cupB = 0
    tested = False

    def __init__(self, parent = None):
        super().__init__(parent)


class stockmodel(QtCore.QAbstractTableModel):
    """
    A view model class for rendering the stocktaking process.

    This class inherits from QtCore.QAbstractTableModel and provides the necessary methods
    to display and manipulate data in a table view. It represents the stock model used in
    the warehouse management system.

    Attributes:
        invController (invController): The inventory controller object.
        model (list[list[stock_delegate]]): The data model for the stock table.
    """

    def __init__(self, parent = None, inv_controller: invController = None):
        super().__init__(parent)
        self.invController = inv_controller
        self.model: list[list[stock_delegate]] = [[stock_delegate()for _ in range(6)] for _ in range(3)]
        self._loadData()

    def rowCount(self, parent:QModelIndex = None) -> int:
        """
        Must be implemented for inherited viewmodel class.
        Returns the number of rows of this viewmodel's table data.
        
        :param parent: The parent index.
        :type parent: QModelIndex
        :return: The number of rows of this viewmodel's table data.
        :rtype: int
        """
        return 3
    
    def columnCount(self, parent: QModelIndex = None) -> int:
        """
        Must be implemented for inherited viewmodel class.
        Returns the number of columns of this viewmodel's table data.

        :param parent: The parent index. Must exist as argument for this method but is unused in this case.
        :type parent: QModelIndex
        :return: The number of columns of this viewmodel's table data.
        :rtype: int
        """
        return 6

    def data(self, index: QModelIndex, role: int) -> Union[str, int, bool, None]:
        """
        Must be implemented for inherited viewmodel class.
        Returns the data to be displayed in the specified index and role.
        You can get the role name by calling roleNames() method of this viewmodel.

        :param index: The index of the item. Must exist as argument for this method but is unused in this case.
        :type index: QModelIndex
        :param role: The role of the item (not roleName).
        :type role: int
        :return: The data to be displayed.
        :rtype: Union[str, int, bool, None]

        """
        print(f"stockmodel.data: {index.row()}, {index.column()}, {role}")
        if index.row()> self.rowCount() or index.column() > self.columnCount():
            return None
        if role == QtCore.Qt.DisplayRole + 1:
            val =  self.model[index.row()][index.column()].previous_pallet
        if role == QtCore.Qt.DisplayRole + 2:
            val =  self.model[index.row()][index.column()].previous_cupA
        if role == QtCore.Qt.DisplayRole + 3:
            val =  self.model[index.row()][index.column()].previous_cupB
        if role == QtCore.Qt.DisplayRole + 4:
            val =  self.model[index.row()][index.column()].new_pallet
        if role == QtCore.Qt.DisplayRole + 5:
            val =  self.model[index.row()][index.column()].new_cupA
        if role == QtCore.Qt.DisplayRole + 6:
            val =  self.model[index.row()][index.column()].new_cupB
        if role == QtCore.Qt.DisplayRole + 7:
            val =  self.model[index.row()][index.column()].tested
        print(f" -> returned: {val}")
        return val
    
    def setData(self, index: QModelIndex, value: Union[str, int, bool, None], role: int) -> bool:
        """
        Must be implemented for inherited viewmodel class.
        Sets the data for the specified index with the given value and role.
        You can get the role name by calling roleNames() method of this viewmodel.
        
        :param index: The index of the item to set the data for.
        :type index: QModelIndex
        :param value: The new value to set.
        :type value: Union[str, int, bool, None]
        :param role: The role of the data.
        :type role: int
        :return: True if the data was successfully set, False otherwise.
        :rtype: bool
        """
        if index.row> self.rowCount() or index.column() > self.columnCount():
            return False
        if role == QtCore.Qt.DisplayRole + 1:
            self.model[index.row()][index.column()].previous_pallet = value
            return True
        if role == QtCore.Qt.DisplayRole + 2:
            self.model[index.row()][index.column()].previous_cupA = value
            return True
        if role == QtCore.Qt.DisplayRole + 3:
            self.model[index.row()][index.column()].previous_cupB = value
            return True
        if role == QtCore.Qt.DisplayRole + 4:
            self.model[index.row()][index.column()].new_pallet = value
            return True
        if role == QtCore.Qt.DisplayRole + 5:
            self.model[index.row()][index.column()].new_cupA = value
            return True
        if role == QtCore.Qt.DisplayRole + 6:
            self.model[index.row()][index.column()].new_cupB = value
            return True
        if role == QtCore.Qt.DisplayRole + 7:
            self.model[index.row()][index.column()].tested = value
            return True
        return False

    def roleNames(self):
        """
        Must be implemented for inherited viewmodel class.
        Returns a dictionary mapping role names to their corresponding role values.
        
        :return roles : A dictionary mapping role names to their corresponding role values.
        :rtype: dict [int, QByteArray]
        """
        roles = {
            QtCore.Qt.DisplayRole + 1: b'previous_pallet',
            QtCore.Qt.DisplayRole + 2: b'previous_cupA',
            QtCore.Qt.DisplayRole + 3: b'previous_cupB',
            QtCore.Qt.DisplayRole + 4: b'new_pallet',
            QtCore.Qt.DisplayRole + 5: b'new_cupA',
            QtCore.Qt.DisplayRole + 6: b'new_cupB',
            QtCore.Qt.DisplayRole + 7: b'tested',
        }
        return roles

    def _loadData(self):
        """
        Load data from applications datamodel into the stockmodel which is used to render the stocktaking process.

        This method retrieves data from the inventory controller and populates the stockmodel.
        It iterates over the rows and columns of the stock model and checks if there is a pallet at each position.
        If a pallet is found, it updates the corresponding attributes in the stockmodel_delegate object.
        """
        if self.invController is None:
            return
        for row in range(3):
            for col in range(6):
                pallet = self.invController.inventory.getStoragePallet(row=row, col=col)
                if pallet is not None:
                    self.model[row][col].previous_pallet = True
                    if pallet.slotA is not None:
                        self.model[row][col].previous_cupA = pallet.slotA.getID()
                    if pallet.slotB is not None:
                        self.model[row][col].previous_cupB = pallet.slotB.getID()
                
class tablemodel(QtCore.QAbstractListModel):

    def __init__(self, inv_controller: invController, parent = None):
        super().__init__(parent)
        self.inv_controller: invController = inv_controller
        self.model: list[stock_delegate] = [stock_delegate() for _ in range(2)]
    
    def rowCount(self, parent: QModelIndex = None) -> int:
        return 2

    def data(self, index: QModelIndex, role: int) -> Union[str, int, bool, None]:
        """
        Must be implemented for inherited viewmodel class.
        Returns the data to be displayed in the specified index and role.
        You can get the role name by calling roleNames() method of this viewmodel.

        :param index: The index of the item.
        :type index: QModelIndex
        :param role: The role of the item (not roleName).
        :type role: int
        :return: The data to be displayed.
        :rtype: Union[str, int, bool, None]

        """
        print(f"\ttablemodel.data: {index.row()}, {index.column()}, {role}")
        if index.row()> self.rowCount():
            return None
        if role == QtCore.Qt.DisplayRole + 1:
            val = self.model[index.row()].previous_pallet
        if role == QtCore.Qt.DisplayRole + 2:
            val =  self.model[index.row()].previous_cupA
        if role == QtCore.Qt.DisplayRole + 3:
            val =  self.model[index.row()].previous_cupB
        if role == QtCore.Qt.DisplayRole + 4:
            val =  self.model[index.row()].new_pallet
        if role == QtCore.Qt.DisplayRole + 5:
            val =  self.model[index.row()].new_cupA
        if role == QtCore.Qt.DisplayRole + 6:
            val =  self.model[index.row()].new_cupB
        if role == QtCore.Qt.DisplayRole + 7:
            val =  self.model[index.row()].tested
        print(f"\t -> returned: {val}")
        return val
    
    def setData(self, index: QModelIndex, value: Union[str, int, bool, None], role: int) -> bool:
        """
        Must be implemented for inherited viewmodel class.
        Sets the data for the specified index with the given value and role.
        You can get the role name by calling roleNames() method of this viewmodel.
        
        :param index: The index of the item to set the data for.
        :type index: QModelIndex
        :param value: The new value to set.
        :type value: Union[str, int, bool, None]
        :param role: The role of the data.
        :type role: int
        :return: True if the data was successfully set, False otherwise.
        :rtype: bool
        """
        if index.role> self.rowCount() > self.columnCount():
            return False
        if role == QtCore.Qt.DisplayRole + 1:
            self.model[index.row()].previous_pallet = value
            return True
        if role == QtCore.Qt.DisplayRole + 2:
            self.model[index.row()].previous_cupA = value
            return True
        if role == QtCore.Qt.DisplayRole + 3:
            self.model[index.row()].previous_cupB = value
            return True
        if role == QtCore.Qt.DisplayRole + 4:
            self.model[index.row()][index.column()].new_pallet = value
            return True
        if role == QtCore.Qt.DisplayRole + 5:
            self.model[index.row()].new_cupA = value
            return True
        if role == QtCore.Qt.DisplayRole + 6:
            self.model[index.row()].new_cupB = value
            return True
        if role == QtCore.Qt.DisplayRole + 7:
            self.model[index.row()].tested = value
            return True
        return False
    
    def roleNames(self):
        """
        Must be implemented for inherited viewmodel class.
        Returns a dictionary mapping role names to their corresponding role values.
        
        :return roles : A dictionary mapping role names to their corresponding role values.
        :rtype: dict [int, QByteArray]
        """
        roles = {
            QtCore.Qt.DisplayRole + 1: b'previous_pallet',
            QtCore.Qt.DisplayRole + 2: b'previous_cupA',
            QtCore.Qt.DisplayRole + 3: b'previous_cupB',
            QtCore.Qt.DisplayRole + 4: b'new_pallet',
            QtCore.Qt.DisplayRole + 5: b'new_cupA',
            QtCore.Qt.DisplayRole + 6: b'new_cupB',
            QtCore.Qt.DisplayRole + 7: b'tested',
        }
        return roles

    def _loadData(self):
        """
        Load data from applications datamodel into the stockmodel which is used to render the stocktaking process.

        This method retrieves data from the inventory controller and populates the stockmodel.
        It iterates over the rows of the tablemodel and checks if there is a pallet at each position.
        If a pallet is found, it updates the corresponding attributes in the stockmodel_delegate object.
        """
        for row in range(2):
            pallet = self.invController.workbench.k1 if row == 0 else self.invController.workbench.k2
            if pallet is not None:
                self.model[row].previous_pallet = True
                if pallet.slotA is not None:
                    self.model[row].previous_cupA = pallet.slotA.getID()
                if pallet.slotB is not None:
                    self.model[row].previous_cupB = pallet.slotB.getID()
        
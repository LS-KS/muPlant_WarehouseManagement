import PySide6
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
class ProductListViewModel(QtCore.QAbstractListModel):
    """

    implements Qt's QAbstractListModel to share product data
    with qml engine. This Viewmodel is populated and updated by inventoryController.

    """
    def __init__(self, products, parent=None):
        """
        Initializes Model with given data.
        :param products: data stored in ListModel
        :type: List of ProductData objects
        :param parent: Must be set and is (almost?) always None
        """
        super().__init__(parent)
        self.products = products

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
        product = self.products[row]
        if role == QtCore.Qt.UserRole + 1:
            return product.id
        elif role == QtCore.Qt.UserRole + 2:
            return product.name
        elif role == QtCore.Qt.UserRole + 3:
            return product.quantity
        return None

    def headerData(self, section, orientation, role=QtCore.Qt.DisplayRole):
        """

        Returns the appropriate header string depending on the orientation of
        the header and the section. If anything other than the display role is
        requested, we return an invalid variant.

        :param section:
        :param orientation:
        :param role:
        :return:

        """
        if role != QtCore.Qt.DisplayRole:
            return None
        if orientation == QtCore.Qt.Horizontal:
            return f"Column {section}"
        return f"Row {section}"

    def rowCount(self, parent: QModelIndex() = None):
        """

        returns number of rows at index
        :param parent:
        :type: QModelIndex
        :return: number of rows
        :type return: int

        """
        return len(self.products)

    def roleNames(self):
        """
        Must be implemendted.
        Creates a dictionary with rolenames and roles.

        :return: returns a Dictionary containing roles and rolenames

        """
        roles = {
            QtCore.Qt.UserRole + 1: b'id',
            QtCore.Qt.UserRole + 2: b'name',
            QtCore.Qt.UserRole + 3: b'quantity',
        }
        return roles

    def indexOf(self, productID):
        """

        :param productID: product ID
        :type productID: int
        :return: returns index of given product ID

        """

        for index, product in enumerate(self.products):
            if product == productID:
                return index

class ProductData:
    """

    A simple subclass to provide product id, name and stored quantity to qml engine
    by productlistViewModel and productSummaryViewModel

    """
    def __init__(self, id: int, name: str, quantity: int = 0):
        """

        Initializes ProductData class.
        :param id: product id to corresponding name
        :type id: int
        :param name:  product name to corresponding name
        :type name: str
        :param quantity: stored quantity in Storage
        :type quantity: int

        """
        self.id = id
        self.name = name
        self.quantity = quantity

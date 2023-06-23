
from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt


class ProductSummaryViewModel (QSortFilterProxyModel):
    """
    This class is used to provide a viewModel which can be filtered.
    It is used to give the user the ability to filter products with no stored quantity.

    """
    def __init__(self, model, parent=None):
        """
        Iitialize QSortFilterProxyModel with default setting
        so that all records are shown.
        :param model: model which is meant to be filtered
        :type model: ProductlistViewModel
        :param parent: Must be set to (almost always?) None
        """
        super().__init__(parent)
        self.showZeroQuantity = True
        self.setSourceModel(model)

    @Slot(bool)
    def setShowZero(self,bool):
        """
        Slot to either show or hide products with zero quantity
        :param bool: True = Show zero quantity, False = Hide zero quantity
        :type bool: bool
        :return: None
        """
        self.showZeroQuantity = bool
        self.invalidateFilter()
        self.revert

    def filterAcceptsRow(self, sourceRow, sourceParent):
        """
        Implements the filter logic.
        First sets the index of the sourceModel and determines the quantity field to filter.
        :param sourceRow:
        :param sourceParent:
        :return:
        """
        index = self.sourceModel().index(sourceRow, 0, sourceParent)
        quantity = self.sourceModel().data(index, Qt.UserRole +3)
        if quantity == 0 and not self.showZeroQuantity:
                    return False
        return super().filterAcceptsRow(sourceRow, sourceParent)




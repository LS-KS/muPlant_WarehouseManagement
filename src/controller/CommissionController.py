from src.viewmodel.commissionViewModel import CommissionViewModel, CommissionFilterProxyModel

from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex

class CommissionController:
    """
    This class is used to provide a viewModel for all commission data
    commission data source is a database file where all commissions are saved.
    While operating commissions will be passed to CommisioonController by ModbusService or
    OPCUAService.
    """
    def __init__(self):
        self.commissionViewModel = CommissionViewModel()
        self.commissionViewModel.loadCommissionData()
        self.commissionFilterProxyModel = CommissionFilterProxyModel()
        self.commissionFilterProxyModel.setSourceModel(self.commissionViewModel)
        self.commissionFilterProxyModel.setSourceModel(self.commissionViewModel)
        self.commissionFilterProxyModel.setFilterCaseSensitivity(Qt.CaseInsensitive)
        self.commissionFilterProxyModel.setFilterKeyColumn(0)
        self.commissionFilterProxyModel.setFilterRole(Qt.UserRole + 1)
        self.commissionFilterProxyModel.setFilterString("")

    
from src.viewmodel.commissionViewModel import CommissionViewModel, CommissionFilterProxyModel

from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
from src.model.CommissionModel import CommissionData, CommissionState, Locations
from src.constants.Constants import Constants
from yaml import safe_load, safe_dump

class CommissionController:
    """
    This class is used to provide a viewModel for all commission data
    commission data source is a database file where all commissions are saved.
    While operating commissions will be passed to CommisioonController by ModbusService or
    OPCUAService.
    """
    def __init__(self):
        self.constants = Constants()
        self.commissionViewModel = CommissionViewModel(self.loadCommissionData())
        self.commissionFilterProxyModel = CommissionFilterProxyModel()
        self.commissionFilterProxyModel.setSourceModel(self.commissionViewModel)
        self.commissionFilterProxyModel.setFilterCaseSensitivity(Qt.CaseInsensitive)
        self.commissionFilterProxyModel.setFilterKeyColumn(0)
        self.commissionFilterProxyModel.setFilterRole(Qt.UserRole + 1)
        self.commissionFilterProxyModel.setFilterString("")

    def loadCommissionData(self):
        commissionData = []
        with open(Constants().COMMISSIONDATA, 'r') as file:
            data = safe_load(file)
            for line in data:
                source = Locations[line['CommissionData']['source']]
                target = Locations[line['CommissionData']['target']]
                state = CommissionState[line['CommissionData']['state']]
                cup = bool(line['CommissionData']['cup'])
                pallet = bool(line['CommissionData']['pallet'])
                commissionData.append(CommissionData(
                    int(line['CommissionData']['id']),
                    source,
                    target,
                    int(line['CommissionData']['object']),
                    cup,
                    pallet,
                    state.value
                ))
                #print(commissionData[-1].source.value)
        return  commissionData

    def dumpCommissionData(self):
        data = []
        for commission in self.commissionData:
            data.append({
                'CommissionData': {
                    'id': commission.id,
                    'source': commission.source,
                    'target': commission.target,
                    'object': commission.object,
                    'cup': commission.cup,
                    'pallet': commission.pallet,
                    'state': commission.state
                }
            })
        with open(Constants().COMMISSIONDATA, 'w') as file:
            safe_dump(data, file)

    
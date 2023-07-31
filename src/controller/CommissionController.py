from src.viewmodel.commissionViewModel import CommissionViewModel, CommissionFilterProxyModel

from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex
from src.model.CommissionModel import CommissionData, CommissionState, Locations
from src.constants.Constants import Constants
from src.controller.invController import invController
from yaml import safe_load, safe_dump
from src.model.DataModel import Cup, Pallet, Product, StorageElement, Inventory, Workbench
from src.service.EventlogService import EventlogService

class CommissionController:
    """
    This class is used to provide a viewModel for all commission data
    commission data source is a database file where all commissions are saved.
    While operating commissions will be passed to CommisioonController by ModbusService or
    OPCUAService.
    """
    def __init__(self, inventoryController: invController, eventlogService : EventlogService):
        self.constants = Constants()
        self.inventoryController = inventoryController
        self.eventlogService = eventlogService
        self.commissionViewModel = CommissionViewModel(self.loadCommissionData())
        self.dumpCommissionData()
        self.commissionFilterProxyModel = CommissionFilterProxyModel()
        self.commissionFilterProxyModel.setSourceModel(self.commissionViewModel)
        self.commissionFilterProxyModel.setFilterCaseSensitivity(Qt.CaseInsensitive)
        self.commissionFilterProxyModel.setFilterKeyColumn(0)
        self.commissionFilterProxyModel.setFilterRole(Qt.UserRole + 1)
        self.commissionFilterProxyModel.setFilterString("")
        self.commissionFilterProxyModel.sort(6, QtCore.Qt.AscendingOrder)
        self.validateCommissionData()


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
                    state
                ))
                #print(commissionData[-1].source.value)
            self.sortComissionData(commissionData)

        return  commissionData

    def sortComissionData(self, commissionData):
        statusOrder = ["in progress", "pending", "open", "done"]
        commissionData.sort(key=lambda commission: statusOrder.index(commission.state.value))

    def dumpCommissionData(self):
        data = []
        for commission in self.commissionViewModel.commissionData:
            data.append({
                'CommissionData': {
                    'id': commission.id,
                    'source': commission.source.name,
                    'target': commission.target.name,
                    'object': commission.object,
                    'cup': commission.cup,
                    'pallet': commission.pallet,
                    'state': commission.state.name
                }
            })
        with open(Constants().COMMISSIONDATA, 'w') as file:
            safe_dump(data, file)

    def validateCommissionData(self) -> bool:
        """
        This function validates the commission data.
        It makes a copy of the inventory and simulates all commissions.
        Through structure a whole new instance has to be created the hard way. 

        Writes an event in event log if a commission is invalid.

        Returns: True if all commissions are valid, False if not
        """
        inventory = self._setupInventoryCopy()
        workbench = self._setupWorkbenchCopy()
        valid = True
        for commission in self.commissionViewModel.commissionData:
            [source, target, cup, pallet, object] = [commission.source, commission.target, commission.cup, commission.pallet, commission.object]
            if cup & pallet:
                self.eventlogService.writeEvent("CommissionController", f"Commission {commission.id} is invalid: cup and pallet are set")
                valid = False
            elif cup == False and pallet == False:
                self.eventlogService.writeEvent("CommissionController", f"Commission {commission.id} is invalid: nor cup or pallet are set")
                valid = False
            if source == target:
                self.eventlogService.writeEvent("CommissionController", f"Commission {commission.id} is invalid: source and target are the same")
                valid = False
            if source == Locations.ROBOT:
                # always assume that robot delivers correct object
                pass
            elif source == Locations.STORAGE:
                # TODO: check if object is in storage
                # TODO: optional: check if future commissions target possible locations
                pass
            elif source.name[0] == 'L': # source is a Storage-Location
                valid = self._verifyStorageElementSource(commission, cup, inventory, object, pallet, source, valid)
            elif source.name[0] == 'K': # source is a Workbench-Location
                valid = self._verifyWorkbenchSource(commission, object, source, valid, workbench, )
            else:
                self.eventlogService.writeEvent("CommissionController", f"Commission {commission.id} is invalid: source is not valid")
                valid = False
            # check target location
            if target == Locations.ROBOT:
                pass
            elif target == Locations.STORAGE:
                # TODO: check if object is in storage
                # TODO: optional: check if future commissions target possible locations
                pass
            elif target.name[0] == 'L': # target is a Storage-Location
                valid = self._verifyStorageElementTarget(commission,cup, pallet, target, valid, inventory)
            elif target.name[0] == 'K': # target is a Workbench-Location
                valid = self._verifyWorkbenchTarget(commission,cup,pallet, target, valid, workbench)
            # transform Location
        return valid

    def _verifyStorageElementSource(self, commission : CommissionData, cup: bool, inventory: Inventory, object: int, pallet: bool, source : Locations, valid : bool) -> bool:
        """
        Verifies the storage element for a given commission.
        This method checks the specified storage element (cup or pallet) at the source location to validate the commission.

        :param commission: The commission being verified.
        :type commission: CommissionData
        :param cup: If True, the storage element is a cup; otherwise, it's a pallet.
        :type cup: bool
        :param inventory: Copy of invController's inventory object.
        :type: Inventory
        :param object: The ID of the cup or pallet being verified.
        :type object: int
        :param pallet: If True, the storage element is a pallet; otherwise, it's a cup.
        :type pallet: bool
        :param source: The source location of the storage element to be verified.
        :type source: Location
        :param valid: The current validity status of the commission being verified.
        :type valid: bool
        :return bool: The updated validity status of the commission after the verification process.
        """

        source_row = int(source.name[1:-1]) // 6
        source_col = int(source.name[1:-1]) % 6
        slot = source.name[-1] # claclulate slot from StrEnum name
        sE = inventory.pallets[source_row][source_col] # get the StorageElement at the dest location

        if cup:
            slot = sE.pallet.slotA if slot == 'A' else sE.pallet.slotB # get the slot of the pallet
            # check source location for cup
            if slot is None: # StorageElement maybe empty
                valid = False
                self.eventlogService.writeEvent("CommissionController", f"Commission {commission.id} is invalid: source location {source.name} is empty")
                return valid
            if not slot.id == object:
                self.eventlogService.writeEvent("CommissionController",
                                                f"Commission {commission.id} is invalid: cup -id at row, col, slot = [{source_row + 1}, {source_col + 1}, {slot}] does not match with source")
                valid = False
        if pallet:
            # check source location for pallet
            if sE.pallet is None: # StorageElement maybe empty
                valid = False
                self.eventlogService.writeEvent("CommissionController", f"Commission {commission.id} is invalid: source location is empty")
                return valid
        return valid

    def _verifyWorkbenchSource(self, commission: CommissionData, object: int, loc: Locations, valid: bool, workbench: Workbench):
        """
        Verifies the workbench element for a given commission.
        This method checks the specified storage element (cup or pallet) at the source location to validate the commission.

        :param commission: The commission being verified.
        :type commission: CommissionData
        :param object: The object being verified (cup or pallet).
        :type object: int
        :param loc: The source location of the object.
        :type loc: Locations
        :param valid: The current validity status of the commission.
        :type valid: bool
        :param workbench: The workbench object.
        :type workbench: Workbench


        :return bool: The updated validity status of the commission after the verification process.
        """
        if int(loc.name[1]) == 1:
            if workbench.k1 is not None:
                if loc.name[-1] == 'A':
                    if workbench.k1.slotA is None:
                        if not workbench.k1.slotA.id == object:
                            self.eventlogService.writeEvent("CommissionController",
                                                            f"Commission {commission.id} is invalid: cup -id at workbench slot 1A does not match with source")
                            valid = False
                    else:
                        self.eventlogService.writeEvent("CommissionController",
                                                        f"Commission {commission.id} is invalid: No cup at workbench slot {loc.name}")
                        valid = False
                elif loc.name[-1] == 'B':
                    if workbench.k1.slotB is None:
                        if not workbench.k1.slotB.id == object:
                            self.eventlogService.writeEvent("CommissionController",
                                                            f"Commission {commission.id} is invalid: cup -id at workbench slot 1B does not match with source")
                            valid = False
                    else:
                        self.eventlogService.writeEvent("CommissionController",
                                                        f"Commission {commission.id} is invalid: No cup at workbench slot {loc.name}")
                        valid = False
                else:
                    self.eventlogService.writeEvent("CommissionController",
                                                    f"Commission {commission.id} is invalid: Could not resolve source slot")
                    valid = False
            else:
                self.eventlogService.writeEvent("CommissionController",
                                                f"Commission {commission.id} is invalid: No pallet at {loc.name}")
                valid = False
        elif int(loc.name[1]) == 2:
            if workbench.k2 is not None:
                if loc.name[-1] == 'A':
                    if workbench.k2.slotA is None:
                        if not workbench.k2.slotA.id == object:
                            self.eventlogService.writeEvent("CommissionController",
                                                            f"Commission {commission.id} is invalid: cup -id at workbench slot {loc.name} does not match with source")
                            valid = False
                    else:
                        self.eventlogService.writeEvent("CommissionController",
                                                        f"Commission {commission.id} is invalid: No cup at workbench slot {loc.name}")
                        valid = False
                elif loc.name[-1] == 'B':
                    if workbench.k2.slotB is None:
                        if not workbench.k2.slotB.id == object:
                            self.eventlogService.writeEvent("CommissionController",
                                                            f"Commission {commission.id} is invalid: cup -id at workbench slot {loc.name} does not match with source")
                            valid = False
                    else:
                        self.eventlogService.writeEvent("CommissionController",
                                                        f"Commission {commission.id} is invalid: No cup at workbench slot {loc.name}")
                        valid = False
                else:
                    self.eventlogService.writeEvent("CommissionController",
                                                    f"Commission {commission.id} is invalid: Could not resolve source slot")
                    valid = False
            else:
                self.eventlogService.writeEvent("CommissionController",
                                                f"Commission {commission.id} is invalid: No pallet at {loc.name}")
                valid = False
        else:
            self.eventlogService.writeEvent("CommissionController",
                                            f"Commission {commission.id} is invalid: Workbench slot {loc.name} could not be resolved")
            valid = False
        return valid

    def _verifyWorkbenchTarget(self, commission: CommissionData, cup: bool, pallet: bool, loc: Locations, valid: bool, workbench: Workbench) -> bool:
        """
        Verifies the workbench element for a given commission target.
        This method checks the specified target:
        If cup is True, the target must contain a pallet object and the targeted slot must be empty.
        If pallet is True, the target must not contain a pallet.

        :param commission: The commission being verified.
        :type commission: CommissionData
        :param cup: True if the commission is a cup, False otherwise.
        :type cup: bool
        :param pallet: True if the commission is a pallet, False otherwise.
        :type pallet: bool
        :param loc: The target location of the object.
        :type loc: Locations
        :param valid: The current validity status of the commission.
        :type valid: bool
        :param workbench: The workbench object.
        :type workbench: Workbench
        :return valid: The updated validity status of the commission after the verification process.
        :rtype: bool
        """

        sE = workbench.k1 if int(loc.name[1]) == 1 else workbench.k2
        if pallet and sE is not None:
            self.eventlogService.writeEvent("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {loc.name} is not empty.")
            valid = False
            return valid
        elif cup and sE is None:
            self.eventlogService.writeEvent("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {loc.name} is empty.")
            valid = False
            return valid
        slot = sE.slotA if loc.name[-1] == 'A' else sE.slotB
        if cup and slot is not None:
            self.eventlogService.writeEvent("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {loc.name} is not empty.")
            valid = False
            return valid
        return valid

    def _verifyStorageElementTarget(self, commission: CommissionData, cup: bool, pallet: bool, target: Locations, valid: bool, inventory: Inventory) -> bool:
        """
        Verifies the storage element for a given commission target.
        This method checks the specified target:
        If cup is True, the target must contain a pallet object and the targeted slot must be empty.
        If pallet is True, the target must not contain a pallet.

        :param commission: The commission being verified.
        :type commission: CommissionData
        :param cup: True if the commission is a cup, False otherwise.
        :type cup: bool
        :param pallet: True if the commission is a pallet, False otherwise.
        :type pallet: bool
        :param target: The target location of the object.
        :type target: Locations
        :param valid: The current validity status of the commission.
        :type valid: bool
        :param inventory: copy of invController's inventory.
        :type inventory: Inventory
        :return valid: The updated validity status of the commission after the verification process.
        :rtype: bool
        """
        locName = target.name
        number = int(locName[1:-1])
        row = int(locName[1:-1])//6 -1
        col = int(locName[1:-1])%6
        sE = inventory.pallets[row][col].pallet
        if pallet and sE is not None:
            self.eventlogService.writeEvent("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {target.name} is not empty.")
            valid = False
            return valid
        elif cup and sE is None:
            self.eventlogService.writeEvent("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {target.name} has no pallet.")
            valid = False
            return valid
        slot = sE.slotA if target.name[-1] == 'A' else sE.slotB
        if cup and slot is not None:
            self.eventlogService.writeEvent("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {target.name} is not empty.")
            valid = False
            return valid
        return valid

    def _setupWorkbenchCopy(self):
        """
        Creates a copy of invController's workbench object.
        """
        workbench = Workbench()
        if self.inventoryController.workbench.k1 is not None:
            workbench.k1 = Pallet()
            if self.inventoryController.workbench.k1.slotA is not None:
                workbench.k1.slotA = Cup(
                    id=self.inventoryController.workbench.k1.slotA.id,
                    product=Product(
                        id=self.inventoryController.workbench.k1.slotA.product.id,
                        name=""
                    )
                )
            if self.inventoryController.workbench.k1.slotB is not None:
                workbench.k1.slotB = Cup(
                    id=self.inventoryController.workbench.k1.slotB.id,
                    product=Product(
                        id=self.inventoryController.workbench.k1.slotB.product.id,
                        name=""
                    )
                )
        if self.inventoryController.workbench.k2 is not None:
            workbench.k2 = Pallet()
            if self.inventoryController.workbench.k2.slotA is not None:
                workbench.k2.slotA = Cup(
                    id=self.inventoryController.workbench.k2.slotA.id,
                    product=Product(
                        id=self.inventoryController.workbench.k2.slotA.product.id,
                        name=""
                    )
                )
            if self.inventoryController.workbench.k2.slotB is not None:
                workbench.k2.slotB = Cup(
                    id=self.inventoryController.workbench.k2.slotB.id,
                    product=Product(
                        id=self.inventoryController.workbench.k2.slotB.product.id,
                        name=""
                    )
                )
        return workbench

    def _setupInventoryCopy(self):
        """
        Creates a copy of invController's inventory object.
        """
        inventory = Inventory(None)
        for row in range(3):
            for col in range(6):
                sE: StorageElement = self.inventoryController.inventory.pallets[row][col]
                pallet = sE.pallet
                loc = sE.locations
                prodA = None
                prodB = None
                cupA = None
                cuB = None
                if pallet is not None:
                    if pallet.slotA is not None:
                        cupA = pallet.slotA.id
                        if pallet.slotA.product is not None:
                            prodA = pallet.slotA.product.id
                    if pallet.slotB is not None:
                        cupB = pallet.slotB.id
                        if pallet.slotB.product is not None:
                            prodB = pallet.slotB.product.id
                    nSE = inventory.pallets[row][col]
                    nSE.locations = loc
                    nSE.pallet = Pallet()
                    slotA = Cup(id=cupA, product=Product(id=prodA, name=""))
                    slotB = Cup(id=cupB, product=Product(id=prodB, name=""))
                    nSE.pallet.setSlotA(slotA)
                    nSE.pallet.setSlotB(slotB)
        return inventory



    

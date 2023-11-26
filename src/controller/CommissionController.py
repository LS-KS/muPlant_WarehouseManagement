from typing import Union

from src.viewmodel.commissionViewModel import CommissionViewModel, CommissionFilterProxyModel

from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex, QObject, Signal, Slot
from src.model.CommissionModel import CommissionData, CommissionState, Locations
from src.constants.Constants import Constants
from src.controller.invController import invController
from yaml import safe_load, safe_dump
from src.model.DataModel import Cup, Pallet, Product, StorageElement, Inventory, Workbench
from src.service.EventlogService import EventlogService

class CommissionController(QObject):
    """
    This class is used to provide a viewModel for all commission data source is a database file where all commissions are saved.
    While operating commissions will be passed to CommisioonController by ModbusService or
    OPCUAService.
    """
    def __init__(self, inventoryController: invController, eventlogService : EventlogService):
        super().__init__(None)
        self.constants = Constants()
        self.inventoryController: invController = inventoryController
        self.eventlogService: EventlogService = eventlogService
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


    @Slot(str, str, str, result=bool)
    def check_commission(self, source: str, target: str, cup_or_pallet: str) -> bool:
        """
        Checks if a new commission would be valid. This method just checks if the source and target could be valid.
        It does not check if the source and target are empty or if the source and target are the same.

        :param source: source location
        :type source: str
        :param target: target location
        :type target: str
        :param cup_or_pallet: "Cup" for cup or "Pallet" for pallet
        :type cup_or_pallet: str
        :return: True if valid, False if not
        :rtype: bool
        """
        print(f"check_commission called with source: {source}, target: {target}, object: {cup_or_pallet}")
        source = Locations[source]
        target = Locations[target]
        cup = True if cup_or_pallet == "Cup" else False
        pallet = True if cup_or_pallet == "Pallet" else False
        valid = [False, False]
        if cup and source.name[-1] in ['A', 'B']:
            valid[0] = True 
        elif pallet and source.name[-1] not in ['A', 'B']:
            valid[0] = True 
        if cup and target.name[-1] in ['A', 'B']:
            valid[1] = True
        elif pallet and target.name[-1] not in ['A', 'B']:
            valid[1] = True
        if pallet and source.name[0] == 'K' and target.name[0] == 'K':    
            self.eventlogService.write_event("CommissionController", f"Note! Workbench -> Workbench is only valiid for cups.")
        result = all(valid)
        return result




    @Slot(str, str, str)
    def create_new_commission(self, source: str, target: str, cup_or_pallet: str):
        """
        Creates a new commission and adds it to the commissionViewModel.
        Cases: 
        1.) robot -> workbench (vice versa, cup only) : 1 commission
        2.) workbench -> workbench (cup only, 2 pallets at workbench, target empty) : 1 commissions
        3.) workbench -> storage (vice versa, pallet only, with empty target) : 1 commissions
        4.) workbench -> storage (cup) : 3 commissions (1. storage -> workbench (pallet with empty slot), 2. workbench-> workbench(cup) 3. workbench -> storage (pallet together with cup))
        5.) storage -> workbench (cup | pallet, at least one slot for pallet in workbench empty) : 1 commission
        6.) storage -> storage (pallet only, with empty workbench) : 4 commissions (1. storage -> workbench, 2. storage -> workbench, 3. workbench -> storage, 4. workbench -> storage)
        7.) storage -> storage (cup only, empty workbench, target pallet slot is empty) : 5 commissions (1. storage -> workbench (pallet), 2. storage -> workbench (pallet), 3. workbench -> workbench (cup), 4. workbench -> storage (pallet), 5. workbench -> storage (pallet))
        :param source: source location
        :type source: str
        :param target: target location
        :type target: str
        :param cup_or_pallet: "Cup" for cup or "Pallet" for pallet
        :type cup_or_pallet: str
        """
        src = Locations[source]
        trg = Locations[target]
        source_object = self._get_object_from_location(src)
        target_object = self._get_object_from_location(trg)
        cup = True if cup_or_pallet == "Cup" else False
        pallet = True if cup_or_pallet == "Pallet" else False

        # case 1
        if src == Locations.ROBOT and trg.name[0] == 'K' and cup:
            if target_object is None:
                self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                )
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {trg.value} created")
        elif trg == Locations.ROBOT and src.name[0] == 'K' and cup:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object is None:
                self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(target_object, 'id', 0),
                )
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {src.value} created")

        # case 2
        elif src.name[0] == 'K' and trg.name[0] == 'K' and cup:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object is None:
                self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                )
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {src.value} created")

        # case 3
        elif src.name[0] == 'K' and trg.name[0] == 'L' and pallet:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object is None:
                self._create_new_commission(
                    source= src.name,
                    target= trg.name,
                    cup= cup,
                    pallet= pallet,
                    object= 0,
                )
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {src.value} created")

        # case 4
        elif src.name[0] == 'K' and trg.name[0] == 'L' and cup:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            other_workbench = 'K' + (1 if target.name[1] == '2' else 1)
            other_workbenchslot = other_workbench + ('A' if target.name[-1] == 'A' else 'B')
            # create first commission storage -> workbench
            if target_object.location is not None and other_workbenchslot is not None:
                self._create_new_commission(
                    source= Locations[target[0:-1]], # pull pallet from storage
                    target= Locations[other_workbench],
                    cup= False,
                    pallet= True,
                    object= 0,
                )
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {source} to {target} created")
            # create second commission workbench -> workbench
            self._create_new_commission(
                source = Locations[source],
                target = Locations[other_workbenchslot],
                cup = True,
                pallet = False,
                object = getattr(self._get_object_from_location(source).id,0),
            )
            self.eventlogService.write_event("CommissionController", f"New sub-commission from {source} to {target} created")
            # create third commission workbench -> storage
            self._create_new_commission(
                source = Locations[other_workbenchslot[0:-1]],
                target = Locations[target[0:-1]],
                cup = False,
                pallet = True,
                object = 0,
            )
            self.eventlogService.write_event("CommissionController", f"Final sub-commission from {source} to {target} created")
    
        # case 5
        elif src.name[0] == 'L' and trg.name[0] == 'K' and pallet:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object is None:
                self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                )
                self.eventlogService.write_event("CommissionController", f"New commission from {source} to {target} created")
        
        # case 6
        elif src.name[0] == 'L' and trg.name[0] == 'L' and pallet:
            if self._get_object_from_location(Locations['K1']) is None and self._get_object_from_location(Locations['K2']) is None:
                self._create_new_commission(
                    source= src,
                    target= Locations.K1,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                )
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K1'].value} created")
                if target_object is not None:
                    self._create_new_commission(
                        source = trg,
                        target = Locations.K2,
                        cup = cup,
                        pallet = pallet,
                        object = getattr(source_object, 'id', 0),
                    )
                    self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K2'].value} created")
                    self._create_new_commission(
                        source = Locations.K2,
                        target = src,
                        cup = cup,
                        pallet = pallet,
                        object = getattr(source_object, 'id', 0),
                    )
                    self.eventlogService.write_event("CommissionController", f"New sub-commission from {Locations['K2']} to {src} created")
                self._create_new_commission(
                    source = Locations.K1,
                    target = trg,
                    cup = cup,
                    pallet = pallet,
                    object = getattr(source_object, 'id', 0),
                )
                self.eventlogService.write_event("CommissionController", f"Final sub-commission from {Locations['K1'].value} to {src.value} created")
                
        # case 7
        elif src.name[0] == 'L' and trg.name[0] == 'L' and cup:
            if self._get_object_from_location(trg) is None and self._get_object_from_location(Locations['K1'].name) is None and self._get_object_from_location(Locations['K2'].name) is None:
                self._create_new_commission(
                    source= src,
                    target= Locations['K1'].name,
                    cup= False,
                    pallet= True,
                    object= 0,
                )
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K1'].value} created")
                self._create_new_commission(
                    source = trg,
                    target = Locations['K2'].name,
                    cup = False,
                    pallet = True,
                    object = 0,
                )
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K2'].value} created")
                self._create_new_commission(
                    source = Locations['K1'+source[-1]].name,
                    target = Locations['K2'+target[-1]].name,
                    cup = True,
                    pallet = False,
                    object = getattr(source_object, 'id', 0),
                )
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {Locations['K1'+ source[-1]].value} to {Locations['K2'+ target[-1]].value} created")
                self._create_new_commission(
                    source = Locations['K2'].name,
                    target = Locations[trg[0:-1]],
                    cup = False,
                    pallet = True,
                    object = 0,
                )
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {Locations['K2'].value} to {Locations[trg[0:-1]].value} created")
                self._create_new_commission(
                    source = Locations['K1'].name,
                    target = Locations[src[0:-1]].name,
                    cup = False,
                    pallet = True,
                    object = 0,
                )
                self.eventlogService.write_event("CommissionController", f"Final sub-commission from {Locations['K1'].name} to {Locations[src[0:-1]].value} created")
        check =self.validateCommissionData()
        if check:
            self.dumpCommissionData()
            self.eventlogService.write_event("CommissionController", f"All commissions valid.")
        else:
            self.eventlogService.write_event("CommissionController", f"Error! Commission invalid.")

    def _get_object_from_location(self, location: Locations) -> Union[Cup, Pallet]:
        """
        Returns the object at the specified location.
        Parameters
        :param location: location to get object from
        :type location: Locations
        """
        default = None
        match location:
            case Locations.ROBOT:
                return getattr(self.inventoryController.mobileRobot, 'cup', default)
            case Locations.K1A:
                return getattr(self.inventoryController.workbench.k1, 'slotA', default)
            case Locations.K1B:
                return getattr(self.inventoryController.workbench.k1, 'slotB', default)
            case Locations.K2A:
                return getattr(self.inventoryController.workbench.k2, 'slotA', default)
            case Locations.K2B:
                return getattr(self.inventoryController.workbench.k2, 'slotB', default)
            case Locations.GRIPPER:
                return self.inventoryController.gripper.object
            case Locations.STORAGE:
                return None
            case Locations.L1:
                return self.inventoryController.inventory.getStoragePallet(0, 0)
            case Locations.L1A:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 0), 'slotA', default)
            case Locations.L1B:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 0), 'slotB', default)
            case Locations.L2:
                return self.inventoryController.inventory.getStoragePallet(0, 1)
            case Locations.L2A:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 1), 'slotA', default)
            case Locations.L2B:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 1), 'slotB', default)
            case Locations.L3:
                return self.inventoryController.inventory.getStoragePallet(0, 2)
            case Locations.L3A:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 2), 'slotA', default)
            case Locations.L3B:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 2), 'slotB', default)
            case Locations.L4:
                return self.inventoryController.inventory.getStoragePallet(0, 3)
            case Locations.L4A:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 3), 'slotA', default)
            case Locations.L4B:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 3), 'slotB', default)
            case Locations.L5:
                return self.inventoryController.inventory.getStoragePallet(0, 4)
            case Locations.L5A:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 4), 'slotA', default)
            case Locations.L5B:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 4), 'slotB', default)
            case Locations.L6:
                return self.inventoryController.inventory.getStoragePallet(0, 5)
            case Locations.L6A:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 5), 'slotA', default)
            case Locations.L6B:
                return getattr(self.inventoryController.inventory.getStoragePallet(0, 5), 'slotB', default)
            case Locations.L7:
                return self.inventoryController.inventory.getStoragePallet(1, 0)
            case Locations.L7A:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 0), 'slotA', default)
            case Locations.L7B:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 0), 'slotB', default)
            case Locations.L8:
                return self.inventoryController.inventory.getStoragePallet(1, 1)
            case Locations.L8A:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 1), 'slotA', default)
            case Locations.L8B:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 1), 'slotB', default)
            case Locations.L9:
                return self.inventoryController.inventory.getStoragePallet(1, 2)
            case Locations.L9A:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 2), 'slotA', default)
            case Locations.L9B:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 2), 'slotB', default)
            case Locations.L10:
                return self.inventoryController.inventory.getStoragePallet(1, 3)
            case Locations.L10A:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 3), 'slotA', default)
            case Locations.L10B:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 3), 'slotB', default)
            case Locations.L11:
                return self.inventoryController.inventory.getStoragePallet(1, 4)
            case Locations.L11A:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 4), 'slotA', default)
            case Locations.L11B:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 4), 'slotB', default)
            case Locations.L12:
                return self.inventoryController.inventory.getStoragePallet(1, 5)
            case Locations.L12A:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 5), 'slotA', default)
            case Locations.L12B:
                return getattr(self.inventoryController.inventory.getStoragePallet(1, 5), 'slotB', default)
            case Locations.L13:
                return self.inventoryController.inventory.getStoragePallet(2, 0)
            case Locations.L13A:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 0), 'slotA', default)
            case Locations.L13B:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 0), 'slotB', default)
            case Locations.L14:
                return self.inventoryController.inventory.getStoragePallet(2, 1)
            case Locations.L14A:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 1), 'slotA', default)
            case Locations.L14B:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 1), 'slotB', default)
            case Locations.L15:
                return self.inventoryController.inventory.getStoragePallet(2, 2)
            case Locations.L15A:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 2), 'slotA', default)
            case Locations.L15B:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 2), 'slotB', default)
            case Locations.L16:
                return self.inventoryController.inventory.getStoragePallet(2, 3)
            case Locations.L16A:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 3), 'slotA', default)
            case Locations.L16B:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 3), 'slotB', default)
            case Locations.L17:
                return self.inventoryController.inventory.getStoragePallet(2, 4)
            case Locations.L17A:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 4), 'slotA', default)
            case Locations.L17B:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 4), 'slotB', default)
            case Locations.L18:
                return self.inventoryController.inventory.getStoragePallet(2, 5)
            case Locations.L18A:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 5), 'slotA', default)
            case Locations.L18B:
                return getattr(self.inventoryController.inventory.getStoragePallet(2, 5), 'slotB', default)

    def _create_new_commission(self, **kwargs):
        """
        Creates a new commission and adds it to the commissionViewModel.
        Parameters

        """
        comission = CommissionData(
            id=self.commissionViewModel.new_comission_id(),
            source=kwargs.get('source'),
            target=kwargs.get('target'),
            object=kwargs.get('object'),
            cup=kwargs.get('cup'),
            pallet=kwargs.get('pallet'))
        self.commissionViewModel.add(comission)


    def loadCommissionData(self):
        commissionData = []
        with open(Constants().COMMISSIONDATA, 'r') as file:
            data = safe_load(file)
            if data is None:
                return []
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
        return commissionData

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
                    'state': commission.state.name,
                }
            })
        with open(Constants().COMMISSIONDATA, 'w') as file:
            safe_dump(data, file)
    def get_commissionData(self)-> list[CommissionData]:
        """
        returns commission data stored in CommissionViewModel.
        """
        data = self.commissionViewModel.commissionData
        return data
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
            source, target, cup, pallet, object = commission.source, commission.target, commission.cup, commission.pallet, commission.object
            data = {
                'commission': commission,
                'cup': cup,
                'inventory': inventory,
                'object': object,
                'pallet': pallet,
                'source': source,
                'valid': valid,
                'target': target,
                'workbench': workbench
            }

            # Check for obvious errors
            if cup & pallet:
                self.eventlogService.write_event("CommissionController", f"Commission {commission.id} is invalid: cup and pallet are set")
                valid = False
            elif cup == False and pallet == False:
                self.eventlogService.write_event("CommissionController", f"Commission {commission.id} is invalid: nor cup or pallet are set")
                valid = False
            if source == target:
                self.eventlogService.write_event("CommissionController", f"Commission {commission.id} is invalid: source and target are the same")
                valid = False
            # check source location
            valid = self._commissioncheck_source_location(**data)
            # check target location
            valid = self._commissioncheck_target_location(**data)

            # perform commission if valid
            self._commissioncheck_peform(**data)
            if valid is False:
                break
        return valid


    def _commissioncheck_peform(self, **kwargs):
        """
        This sub-method of validateCommissionData performs the commission if it is valid.

        :param cup: True if Commission is a cup, False if not
        :param inventory: Inventory copy
        :param pallet: True if Commission is a pallet, False if not
        :param source:
        :param target:
        :param valid:
        :param workbench:
        :return:
        """
        valid = kwargs.get('valid')
        source = kwargs.get('source')
        target = kwargs.get('target')
        pallet = kwargs.get('pallet')
        inventory = kwargs.get('inventory')
        workbench = kwargs.get('workbench')
        cup = kwargs.get('cup')
        # commission = kwargs.get('commission')
        # object = kwargs.get('object')

        if valid:
            if pallet:
                sEPallet = None
                if source.name[0] == 'L':
                    source_row = int(source.name[1]) // 6 - 1
                    source_col = int(source.name[1]) % 6
                    sEPallet = inventory.pallets[source_row][source_col].pallet
                elif source.name[0] == 'K':
                    sEPallet = workbench.k1 if source.name[1] == '1' else workbench.k2
                if target.name[0] == 'L':
                    target_row = int(target.name[1:-1]) // 6 - 1
                    target_col = int(target.name[1:-1]) % 6
                    inventory.pallets[target_row][target_col].pallet = sEPallet
                elif target.name[0] == 'K':
                    if target.name[1] == '1':
                        workbench.k1 = sEPallet
                    else:
                        workbench.k2 = sEPallet
            elif cup:
                sECup = None
                if source.name[0] == 'L':
                    source_row = int(source.name[1:-1]) // 6 - 1
                    source_col = int(source.name[1:-1]) % 6
                    sECup = inventory.pallets[source_row][source_col].pallet.slotA if source.name[-1] == 'A' else \
                    inventory.pallets[source_row][source_col].pallet.slotB
                elif source.name[0] == 'K':
                    if source.name[1] == '1':
                        if source.name[-1] == 'A':
                            sECup = workbench.k1.slotA
                        if source.name[-1] == 'B':
                            sECup = workbench.k1.slotB
                    else:
                        sECup = workbench.k2.slotA if source.name[-1] == 'A' else workbench.k2.slotB
                if target.name[0] == 'L':
                    target_row = int(target.name[1]) // 6 - 1
                    target_col = int(target.name[1]) % 6
                    if target.name[-1] == 'A':
                        inventory.pallets[target_row][target_col].pallet.slotA = sECup
                    else:
                        inventory.pallets[target_row][target_col].pallet.slotB = sECup
                elif target.name[0] == 'K':
                    if target.name[1] == '1':
                        if target.name[-1] == 'A':
                            workbench.k1.slotA = sECup
                        if target.name[-1] == 'B':
                            workbench.k1.slotB = sECup
                    else:
                        if target.name[-1] == 'A':
                            workbench.k2.slotA = sECup
                        else:
                            workbench.k2.slotB = sECup

    def _commissioncheck_source_location(self, **kwargs):
        valid = kwargs.get('valid')
        source: Locations = kwargs.get('source')
        target: Locations = kwargs.get('target')
        pallet = kwargs.get('pallet')
        inventory = kwargs.get('inventory')
        workbench = kwargs.get('workbench')
        cup = kwargs.get('cup')
        commission = kwargs.get('commission')
        object = kwargs.get('object')

        data = {
            'commission': commission,
            'cup': cup,
            'inventory': inventory,
            'object': object,
            'pallet': pallet,
            'source': source,
            'valid': valid,
            'target': target,
            'workbench': workbench
        }
        if source == Locations.ROBOT:
            # always assume that robot delivers correct object
            pass
        elif source == Locations.STORAGE:
            # TODO: check if object is in storage
            # TODO: optional: check if future commissions target possible locations
            pass
        elif source.name[0] == 'L':  # source is a Storage-Location
            valid = self._verifyStorageElementSource(**data)
        elif source.name[0] == 'K':  # source is a Workbench-Location
            valid = self._verifyWorkbenchSource(**data)
        else:
            self.eventlogService.write_event("CommissionController",
                                            f"Commission {commission.id} is invalid: source is not valid")
            valid = False
        return valid

    def _commissioncheck_target_location(self, **kwargs):
        valid = kwargs.get('valid')
        source: Locations = kwargs.get('source')
        target: Locations = kwargs.get('target')
        pallet = kwargs.get('pallet')
        inventory = kwargs.get('inventory')
        workbench = kwargs.get('workbench')
        cup = kwargs.get('cup')
        commission = kwargs.get('commission')
        object = kwargs.get('object')

        data = {
            'commission': commission,
            'cup': cup,
            'inventory': inventory,
            'object': object,
            'pallet': pallet,
            'source': source,
            'valid': valid,
            'target': target,
            'workbench': workbench
        }
        if target == Locations.ROBOT:
            pass
        elif target == Locations.STORAGE:
            # TODO: check if object is in storage
            # TODO: optional: check if future commissions target possible locations
            pass
        elif target.name[0] == 'L':  # target is a Storage-Location
            valid = self._verifyStorageElementTarget(**data)
        elif target.name[0] == 'K':  # target is a Workbench-Location
            valid = self._verifyWorkbenchTarget(**data)
        return valid

    def _verifyStorageElementSource(self, **kwargs) -> bool:
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
        source: Locations = kwargs.get('source')
        valid = kwargs.get('valid')
        inventory: Inventory = kwargs.get('inventory')
        cup = kwargs.get('cup')
        commission = kwargs.get('commission')
        pallet = kwargs.get('pallet')

        

        if cup:
            source_row = (int(source.name[1:-1])-1) // 6
            source_col = (int(source.name[1:-1])-1) % 6
            slot = source.name[-1] # calculate slot from StrEnum name
            sE = inventory.pallets[source_row][source_col] # get the StorageElement at the dest location
            slot = sE.pallet.slotA if slot == 'A' else sE.pallet.slotB # get the slot of the pallet
            # check source location for cup
            if slot is None: # StorageElement maybe empty
                valid = False
                self.eventlogService.write_event("CommissionController", f"Commission {commission.id} is invalid: source location {source.name} is empty")
                return valid
            if not slot.id == object:
                self.eventlogService.write_event("CommissionController",
                                                f"Commission {commission.id} is invalid: cup -id at row, col, slot = [{source_row + 1}, {source_col}, {slot.id}] does not match with source")
                valid = False
        elif pallet:
            # check source location for pallet
            source_row = (int(source.name[1:])-1) // 6
            source_col = (int(source.name[1:])-1) % 6
            sE = inventory.pallets[source_row][source_col] # get the StorageElement at the dest location
            if sE.pallet is None: # StorageElement maybe empty
                valid = False
                self.eventlogService.write_event("CommissionController", f"Commission {commission.id} is invalid: source location is empty")
                return valid
        return valid

    def _verifyWorkbenchSource(self, **kwargs) -> bool:
        """
        Verifies the workbench element for a given commission.
        This method checks the specified storage element (cup or pallet) at the source location to validate the commission.

        :param commission: The commission being verified.
        :type commission: CommissionData
        :param object: The object being verified (cup or pallet).
        :type object: int
        :param source: The source location of the object.
        :type source: Locations
        :param valid: The current validity status of the commission.
        :type valid: bool
        :param workbench: The workbench object.
        :type workbench: Workbench
        :return bool: The updated validity status of the commission after the verification process.
        """
        source = kwargs.get('source')
        workbench = kwargs.get('workbench')
        commission = kwargs.get('commission')
        valid = kwargs.get('valid')
        object = kwargs.get('object')
        cup = kwargs.get('cup')
        pallet = kwargs.get('pallet')

        pallet_object:Pallet = workbench.k1 if source.name[1] == '1' else workbench.k2
        if pallet:
            if pallet_object is None:
                self.eventlogService.write_event("CommissionController",f"Commission {commission.id} is invalid: source location {source.name} is has no pallet.")
                valid = False
        elif cup:
            if pallet_object is None:
                self.eventlogService.write_event("CommissionController",f"Commission {commission.id} is invalid: source location {source.name} is has no pallet.")
                valid = False
            else:
                slot = pallet_object.slotA if source.name[-1] == 'A' else pallet_object.slotB
                if slot is None:
                    self.eventlogService.write_event("CommissionController",f"Commission {commission.id} is invalid: source location {source.name} is has no cup.")
                    valid = False
                elif slot.id != object:
                    self.eventlogService.write_event("CommissionController",f"Commission {commission.id} is invalid: cup -id at slot {source.name[-1]} does not match with source.")
                    valid = False
        return valid

    def _verifyWorkbenchTarget(self, **kwargs) -> bool:
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
        workbench = kwargs.get('workbench')
        loc: Locations = kwargs.get('target')
        pallet = kwargs.get('pallet')
        commission = kwargs.get('commission')
        cup = kwargs.get('cup')
        valid = kwargs.get('valid')

        pallet_object:Pallet = workbench.k1 if loc.name[1] == '1' else workbench.k2
        if pallet and pallet_object is not None:
            self.eventlogService.write_event("CommissionController",f"Commission {commission.id} is invalid: target location {loc.name} is not empty.")
            valid = False
        elif cup and pallet_object is None:
            self.eventlogService.write_event("CommissionController",f"Commission {commission.id} is invalid: target location {loc.name} has no pallet.")
            valid = False
        elif cup and pallet_object is not None:
            slot = pallet_object.slotA if loc.name[-1] == 'A' else pallet_object.slotB
            if slot is not None:
                self.eventlogService.write_event("CommissionController",f"Commission {commission.id} is invalid: target location {loc.name} is not empty.")
                valid = False
        return valid

    def _verifyStorageElementTarget(self, **kwargs) -> bool:
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
        target: Locations = kwargs.get('target')
        inventory = kwargs.get('inventory')
        pallet = kwargs.get('pallet')
        commission = kwargs.get('commission')
        valid = kwargs.get('valid')
        cup = kwargs.get('cup')

        locName = target.name
        number = int(locName[1:-1])
        row = int(locName[1:-1])//6
        col = int(locName[1:-1]) % 6 -1
        sE = inventory.pallets[row][col].pallet
        if pallet and sE is not None:
            self.eventlogService.write_event("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {target.name} is not empty.")
            valid = False
            return valid
        elif cup and sE is None:
            self.eventlogService.write_event("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {target.name} has no pallet.")
            valid = False
            return valid
        slot = sE.slotA if target.name[-1] == 'A' else sE.slotB
        if cup and slot.id != 0:
            self.eventlogService.write_event("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {target.name} is not empty.")
            valid = False
            return valid
        return valid

    def _setupWorkbenchCopy(self) -> Workbench:
        """
        Creates and returns a copy of invController's workbench object.
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
    

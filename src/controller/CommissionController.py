from typing import Union
from src.viewmodel.commissionViewModel import CommissionViewModel, CommissionFilterProxyModel
from PySide6.QtCore import QSortFilterProxyModel, Slot, Qt
from PySide6 import QtCore
from PySide6.QtCore import QModelIndex, QObject, Signal, Slot
from src.model.CommissionModel import CommissionData, CommissionState, Locations, Velocity
from src.constants.Constants import Constants
from src.controller.invController import invController
from yaml import safe_load, safe_dump
from src.model.DataModel import Cup, Pallet, Product, StorageElement, Inventory, Workbench, MobileRobot
from src.service.EventlogService import EventlogService

class CommissionController(QObject):
    """
    This class is used to provide a viewModel for all commission data source is a database file where all commissions are saved.
    While operating commissions will be passed to CommisioonController by ModbusService or
    OPCUAService.
    """
    new_commission = Signal(CommissionData)
    transmitCommission = Signal(int, str, str, str, int) #id, item, source, target, state
    prepared_commission = Signal(bool)
    def __init__(self, inventoryController: invController, eventlogService : EventlogService):
        super().__init__(None)
        self.constants = Constants()
        self.inventoryController: invController = inventoryController
        self.eventlogService: EventlogService = eventlogService
        self.commissionViewModel = CommissionViewModel(self.loadCommissionData())
        self.commissionFilterProxyModel = CommissionFilterProxyModel()
        self.inventory_copy: Inventory = None
        self.workbench_copy: Workbench = None
        self.mobile_robot_copy: MobileRobot = None
        self.dumpCommissionData()
        self.commissionFilterProxyModel.setSourceModel(self.commissionViewModel)
        print([commission.id for commission in self.commissionViewModel.commissionData])
        self.sortComissionData()
        print([commission.id for commission in self.commissionViewModel.commissionData])
        self.validateCommissionData()

    @Slot()
    def clearDone(self):
        leftidx = None
        for i in range(self.commissionViewModel.rowCount()):
            commission = self.commissionViewModel.commissionData[i]
            if commission.state == CommissionState.DONE:
                leftidx = i
                break
        rightidx = self.commissionViewModel.rowCount()
        self.commissionViewModel.beginRemoveRows(QModelIndex(), leftidx, rightidx)
        ret = self.commissionViewModel.removeRows(leftidx, rightidx-leftidx)
        self.commissionViewModel.endRemoveRows()
        print(f"result of removing rows: {ret}, leftidx: {leftidx}, rightidx {rightidx}")
        self.dumpCommissionData()

    @Slot(str)
    def loadCommission(self, id: str):
        id = int(id)
        for commission in self.commissionViewModel.commissionData:
            if commission.id == id:
                self.transmitCommission.emit(commission.id, 
                                             "Cup" if commission.cup else "Pallet", 
                                             commission.source.name, 
                                             commission.target.name, 
                                             commission.state.name)
                break

    @Slot(str, str, str, str, str)
    def overwriteCommission(self, id:str, item:str, source:str, target:str, state:str ):
        """
        QML List Model has the following entries
        ListElement{ index: "OPEN"; text: "open"}
        ListElement{ index: "PENDING"; text: "pending"}
        ListElement{ index: "PROGRESS"; text: "in progress"}
        ListElement{ index: "DONE"; text: "done"}

        :param id: primary key of a commission
        :type id: str which represents an integer
        :param item: 'Cup' or 'Pallet'
        :type item: str
        :param source: source string which represents Locations.name value
        :type source: str
        :param target: target string which represents Locations.name value
        :type target: str
        :param state: state string which represents CommissionState.name value
        :type state: str
        """
        print(id, item, source, target, state)
        states = [CommissionState.OPEN, CommissionState.PENDING, CommissionState.PROGRESS,CommissionState.DONE]
        source = Locations[source]
        target = Locations[target]
        state = states[int(state)]
        index = self.commissionViewModel.indexOf(int(id))
        if None in [index, state, target, source]:
            print(f"Failed to decode: index:{index}, state: {state}, target: {target}, source: {source}")
            return
        else: 
            srcindex = self.commissionViewModel.createIndex(index, 1)
            self.commissionViewModel.setData(srcindex, source)
            trgindex = self.commissionViewModel.createIndex(index, 2)
            self.commissionViewModel.setData(trgindex, target)
            stateindex = self.commissionViewModel.createIndex(index, 6)
            self.commissionViewModel.setData(stateindex, state)
        self.sortComissionData()
        self.dumpCommissionData()

    @Slot(CommissionData, CommissionState)
    def change_commission_state(self, commission: CommissionData, state: CommissionState):
        """
        Changes the state of a commission.
        :param commission: commission to change
        :type commission: CommissionData
        :param state: new state
        :type state: CommissionState
        """
        print(f"CommissionController: Commission {commission.id} changed state to {state}")
        for com in self.commissionViewModel.commissionData:
            if com.id == commission.id:
                row = self.commissionViewModel.indexOf(com)
                index = self.commissionViewModel.createIndex(row, 6)
                res = self.commissionViewModel.setData(index, state)
                if state == CommissionState.PROGRESS:
                    self.set_to_gripper(commission)
                elif state == CommissionState.DONE:
                    self.perform_commission(commission)
                if res : 
                    self.dumpCommissionData()
                    self.eventlogService.write_event("CommissionController", f"Commission {commission.id} changed to {state.value}")
                else:
                    self.eventlogService.write_event("CommissionController", f"Commission {commission.id} could not be changed to {state.value}")
                break

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
        elif cup and source.name == 'ROBOT':
            valid[0] = True
        elif pallet and source.name[-1] not in ['A', 'B']:
            valid[0] = True 
        if cup and target.name[-1] in ['A', 'B']:
            valid[1] = True
        elif cup and target.name == 'ROBOT':
            valid[1] = True
        elif pallet and target.name[-1] not in ['A', 'B']:
            valid[1] = True
        elif pallet and target.name == 'ROBOT':
            valid[1] = False
        if pallet and source.name[0] == 'K' and target.name[0] == 'K':    
            self.eventlogService.write_event("CommissionController", f"Note! Workbench -> Workbench is only valiid for cups.")
        result = all(valid)
        return result

    @Slot(bool, bool, bool, bool, bool, bool, int, int )
    def handle_opcua_commission(self, prepare:bool, execute: bool, to_storage: bool, to_robot: bool, cup: bool, product: bool, cup_id: int, product_id: int):
        """
        Converts commission data from opcua service into modeldata that can be used to create the 
        create_new_commission() method. 

        If execute is True, this methods checks wether before a similar commission was created to be prepared. 

        If to_storage is True, inventoryControllers method create_mobile_robot_cup() is called to create the corresponding data in mobile robot.
        Afterwards it determines where to store the cup by using inventoryControllers find_place_for_cup() method. 

        If to_robot is True, inventoryControllers method find_cup() is called to determine the storage location. 
        """
        self.eventlogService.write_event("CommissionController:", f"Received a commission from OPCUAService with prepare: {prepare}, execute: {execute}, to_storage: {to_storage}, to_robot: {to_robot}, cup: {cup}, product: {product}, cup_id: {cup_id}, product_id: {product_id}")
        if to_storage: 
            ret = self.inventoryController.create_mobile_robot_cup(cup_id= cup_id, product_id= product_id)
            if not ret: self.eventlogService.write_event("CommissionController:", "Cup at mobile robot could not be created: robot not empty.")
            source = "ROBOT" 
            target = self.inventoryController.find_place_for_cup()
            row, col, slot = target['row'], target['col'], target['slot']
            target = f"L{row*6+col+1}{slot}"
            self.eventlogService.write_event("CommissionController", f"About to create a new commission from robot: source: {source}, target: {target}, prepare: {prepare}, execute: {execute}")
            self.create_new_commission(source=source, target = target, cup_or_pallet = "Cup", prepare = prepare, execute = execute)
        if to_robot:
            cup: Cup = self.inventoryController.find_cup(cup_id=cup_id, product_id=product_id)
            if cup is None:
                self.eventlogService.write_event("CommissionController", "Could not find any cup to create commission.") 
                return False
            pallet:Pallet = cup.location
            if pallet.location == self.inventoryController.workbench:
                col = 1 if pallet == self.inventoryController.workbench.k1 else 2 if pallet == self.inventoryController.workbench.k2 else None
                slot = 'A' if pallet.slotA == cup else 'B' if pallet.slotB == cup else None
                if col is None or slot is None: 
                    self.eventlogService.write_event("CommissionController", "Could not decode storage and thus could not create a commission.")
                    return False
                source = f"K{col}{slot}"
            elif isinstance(pallet.location, StorageElement):
                row = pallet.location.row
                col = pallet.location.col
                slot = 'A' if pallet.slotA == cup else 'B' if pallet.slotB == cup else None
                if slot is None: 
                    self.eventlogService.write_event("CommissionController", "Could not decode pallet slot and thus could not create a commission")
                    return False
                source = f"L{row*6+col+1}{slot}" 
            target = "ROBOT"
            self.eventlogService.write_event("CommissionController", f"About to create a new commission to robot: source: {source}, target: {target}, prepare: {prepare}, execute: {execute}")
            self.create_new_commission(source = source, target = target, cup_or_pallet ="Cup", prepare=prepare, execute = execute)
            if prepare:
                self.prepared_commission.emit(True)

    @Slot(str, str, str)
    def create_new_commission(self, source: str, target: str, cup_or_pallet: str, prepare:bool = False, execute = True):
        """
        Creates a new commission and adds it to the commissionViewModel.
        Cases: 
        1.) robot -> workbench (cup only) : 1 commission
        2.) workbench -> robot (cup only) : 1 commission 
        3.) workbench -> workbench (cup only, 2 pallets at workbench, target empty) : 1 commissions
        4.) workbench -> storage (vice versa, pallet only, with empty target) : 1 commissions
        5.) workbench -> storage (cup) : 3 commissions (1. storage -> workbench (pallet with empty slot), 2. workbench-> workbench(cup) 3. workbench -> storage (pallet together with cup))
        6.) storage -> workbench (cup | pallet, at least one slot for pallet in workbench empty) : 1 commission
        7.) storage -> storage (pallet only, with empty workbench) : 4 commissions (1. storage -> workbench, 2. storage -> workbench, 3. workbench -> storage, 4. workbench -> storage)
        8.) storage -> storage (cup only, empty workbench, target pallet slot is empty) : 5 commissions (1. storage -> workbench (pallet), 2. storage -> workbench (pallet), 3. workbench -> workbench (cup), 4. workbench -> storage (pallet), 5. workbench -> storage (pallet))
        9.) storage -> robot (cup only, at least one slot empty in workbench): 3 commissions (1. storage-> workbench(pallet), 2. workbench -> robot (cup), 3. workbench -> storage (pallet))
        10.) robot -> storagte (cup only, at least one cup slot empty in workbench)
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
        commissions: list[CommissionData] = []
        # case 1 Cup from Robot to workbench
        if src == Locations.ROBOT and trg.name[0] == 'K' and cup:
            if target_object is None:
                commissions.append(self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {trg.value} created")
        # case 2 Cup from workbench to robot
        elif trg == Locations.ROBOT and src.name[0] == 'K' and cup:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object.cup is None:
                commissions.append(self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(target_object, 'id', 0),
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {src.value} created")
        # case 3 cup between workbench
        elif src.name[0] == 'K' and trg.name[0] == 'K' and cup:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object is None:
                commissions.append(self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {src.value} created")
        # case 4 pallet from workbench to storage
        elif src.name[0] == 'K' and trg.name[0] == 'L' and pallet:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object is None:
                commissions.append(self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New commission from {src.value} to {src.value} created")
        # case 5 Cup from workbench to storage
        elif src.name[0] == 'K' and trg.name[0] == 'L' and cup:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            other_workbench = 'K' + (1 if target.name[1] == '2' else 1)
            other_workbenchslot = other_workbench + ('A' if target.name[-1] == 'A' else 'B')
            # create first commission storage -> workbench
            if target_object.location is not None and other_workbenchslot is not None:
                commissions.append(self._create_new_commission(
                    source= Locations[target[0:-1]], # pull pallet from storage
                    target= Locations[other_workbench],
                    cup= False,
                    pallet= True,
                    object= 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {source} to {target} created")
            # create second commission workbench -> workbench
            commissions.append(self._create_new_commission(
                source = Locations[source],
                target = Locations[other_workbenchslot],
                cup = True,
                pallet = False,
                object = getattr(self._get_object_from_location(source).id,0),
            ))
            self.eventlogService.write_event("CommissionController", f"New sub-commission from {source} to {target} created")
            # create third commission workbench -> storage
            commissions.append(self._create_new_commission(
                source = Locations[other_workbenchslot[0:-1]],
                target = Locations[target[0:-1]],
                cup = False,
                pallet = True,
                object = 0,
                prepare = prepare and not execute
            ))
            self.eventlogService.write_event("CommissionController", f"Final sub-commission from {source} to {target} created")
        # case 6 Pallet from storage to workbench
        elif src.name[0] == 'L' and trg.name[0] == 'K' and pallet:
            source_object = self._get_object_from_location(src)
            target_object = self._get_object_from_location(trg)
            if target_object is None:
                commissions.append(self._create_new_commission(
                    source= src,
                    target= trg,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New commission from {source} to {target} created")
        # case 7 Pallet from storage to storage
        elif src.name[0] == 'L' and trg.name[0] == 'L' and pallet:
            if self._get_object_from_location(Locations['K1']) is None and self._get_object_from_location(Locations['K2']) is None:
                commissions.append(self._create_new_commission(
                    source= src,
                    target= Locations.K1,
                    cup= cup,
                    pallet= pallet,
                    object= getattr(source_object, 'id', 0),
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K1'].value} created")
                if target_object is not None:
                    commissions.append(self._create_new_commission(
                        source = trg,
                        target = Locations.K2,
                        cup = cup,
                        pallet = pallet,
                        object = getattr(source_object, 'id', 0),
                        prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                    ))
                    self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K2'].value} created")
                    commissions.append(self._create_new_commission(
                        source = Locations.K2,
                        target = src,
                        cup = cup,
                        pallet = pallet,
                        object = getattr(source_object, 'id', 0),
                        prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                    ))
                    self.eventlogService.write_event("CommissionController", f"New sub-commission from {Locations['K2']} to {src} created")
                commissions.append(self._create_new_commission(
                    source = Locations.K1,
                    target = trg,
                    cup = cup,
                    pallet = pallet,
                    object = getattr(source_object, 'id', 0),
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"Final sub-commission from {Locations['K1'].value} to {src.value} created")
        # case 8 Cup from storage to storage
        elif src.name[0] == 'L' and trg.name[0] == 'L' and cup:
            if self._get_object_from_location(trg) is None and self._get_object_from_location(Locations['K1'].name) is None and self._get_object_from_location(Locations['K2'].name) is None:
                commissions.append(self._create_new_commission(
                    source= src,
                    target= Locations['K1'].name,
                    cup= False,
                    pallet= True,
                    object= 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K1'].value} created")
                commissions.append(self._create_new_commission(
                    source = trg,
                    target = Locations['K2'].name,
                    cup = False,
                    pallet = True,
                    object = 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K2'].value} created")
                commissions.append(self._create_new_commission(
                    source = Locations['K1'+source[-1]].name,
                    target = Locations['K2'+target[-1]].name,
                    cup = True,
                    pallet = False,
                    object = getattr(source_object, 'id', 0),
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {Locations['K1'+ source[-1]].value} to {Locations['K2'+ target[-1]].value} created")
                commissions.append(self._create_new_commission(
                    source = Locations['K2'].name,
                    target = Locations[trg[0:-1]],
                    cup = False,
                    pallet = True,
                    object = 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {Locations['K2'].value} to {Locations[trg[0:-1]].value} created")
                commissions.append(self._create_new_commission(
                    source = Locations['K1'].name,
                    target = Locations[src[0:-1]].name,
                    cup = False,
                    pallet = True,
                    object = 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"Final sub-commission from {Locations['K1'].name} to {Locations[src[0:-1]].value} created")
        # case 9 Cup from storage to robot
        elif src.name[0] == 'L' and trg == Locations.ROBOT and cup:
            if self._get_object_from_location(Locations['K1'].name) is None:
                commissions.append(self._create_new_commission(
                    source= Locations[src.name[0:-1]],
                    target= Locations.K1,
                    cup= False,
                    pallet= True,
                    object= 0,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"New sub-commission from {src.value} to {Locations['K1'].value} created")
                commissions.append(self._create_new_commission(
                    source= Locations.K1,
                    target= trg,
                    cup= True,
                    pallet= False,
                    object= 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW,
                ))
                self.eventlogService.write_event("CommissionController", f"Final commission from {src.value} to {Locations['K1'].value} created")
        # case 10 Cup from robot to storage
        elif src == Locations.ROBOT and trg.name[0] == 'L' and cup:
            # if there is no cup free and at least one pallet slot empty, get a suitable pallet from storage. 
            
            # check k1
            k1 = self._get_object_from_location(Locations.K1)
            if k1 is not None: k1_a, k1b = k1.slotA, k1.slotB
            else: k1_a, k1_b = None, None

            # check k2
            k2 = self._get_object_from_location(Locations.K2)
            if k2 is not None: k2_a, k2_b = k2.slotA, k2.slotB
            else: k2_a, k2_b = None, None

            # no pallet at workbench? --> get one with an empty slot from storage
            # one pallet there but full, other empty? --> get one with an empty slot from storage
            if (k1, k2 == None, None) or (k1 == None and k2_a is not None and k2_b is not None) or (k2 == None and k1_a is not None and k1_b is not None):
                # get a suitable pallet from storage
                location = None
                for i in range(18):
                    pallet = self._get_object_from_location(location=Locations[f'L{i}'].name)
                    if pallet is not None: 
                        if pallet.slotA is None or pallet.slotB is None: 
                            location = 'L1'
                            break
                comtrg = Locations.K1 if k1 == None else Locations.K2,
                storage = Locations[location].name,
                slot = 'A' if pallet.slotA is None else pallet.slotB
                # get pallet to workbench
                self.create_new_commission(
                    source = storage,
                    target = comtrg,
                    cup = False, 
                    pallet = True,
                    object = 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW
                )
                # get cup from robot to pallet
                self.create_new_commission(
                    source = Locations.ROBOT,
                    target = Locations[comtrg+slot],
                    cup = True, 
                    pallet = False,
                    object = 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW
                )
                # put Pallet back to storage
                self.create_new_commission(
                    source = Locations[comtrg],
                    target = Locations[storage],
                    cup = False, 
                    pallet = True,
                    object = 0,
                    prepare = prepare and not execute,
                    velocity = Velocity.SLOW
                )
            elif all(x is None for x in [k1, k2, k1_a, k1_b, k2_a, k2_b]):
                # DESPERATION!!!!!!!!!
                return

        #check =self.validateCommissionData()
        check = True
        if check:
            self.dumpCommissionData()
            self.eventlogService.write_event("CommissionController", f"All commissions valid.")
        else:
            self.eventlogService.write_event("CommissionController", f"Error! Commission invalid.")

    def set_to_gripper(self, commission: CommissionData):
        """
        Sets object to gripper.
        Doesn't perform any check.
        :param commission: commission to perform
        :type commission: CommissionData
        """
        object: Union[Cup, Pallet] = self._get_object_from_location(commission.source) #object is fine here (K->L)
        if isinstance(object, MobileRobot):
            self.inventoryController.move_to_gripper(object.cup)
        else:
            self.inventoryController.move_to_gripper(object)

    def perform_commission(self, commission: CommissionData):
        """
        Performs commissions submitted in actual DataModel.
        Note that an object that is performing is set to gripper once state changed to PROGRESS.

        In case of a cup to be transported: 
        Since cups are not allowed to be stored without pallet, it is enough to use _get_object_from_location to get the target pallet object.

        In case of a pallet to be transported:
        1.) If target is storage, the storageElement object is needed
        2.) If target is workbench, the pallet must be set to workbench.k1 or workbench.k2

        :param commission: commission to perform
        :type commissions: CommissionData
        """
        object: Union[Cup, Pallet] = self.inventoryController.gripper.object #object is fine here (L->K), (K->L)
        if isinstance(object, Cup):
            target_location = Locations[commission.target.name[0:-1]] if commission.target is not Locations.ROBOT else Locations.ROBOT # get Pallet Location
            target = self._get_object_from_location(target_location)
            if isinstance(target, MobileRobot):
                self.inventoryController.move_to_robot(object)
            elif isinstance(target.location, Workbench):
                self.inventoryController.move_to_workbench(object, commission.target)
            elif isinstance(target.location, StorageElement):
                self.inventoryController.move_to_storage(object)
            object.setLocation(target)
        elif isinstance(object, Pallet):
            if commission.target.name[0] == 'L':
             self.inventoryController.move_to_storage(object, target=commission.target)
            elif commission.target.name[0] == 'K':
                self.inventoryController.move_to_workbench(object, target=commission.target)     

    def _get_object_from_location(self, location: Locations) -> Union[Cup, Pallet]:
        """
        Returns the object at the specified location.
        If location is mobile robot, returns mobile robot object instead of None. 
        Parameters
        :param location: location to get object from
        :type location: Locations
        """
        default = None
        match location:
            case Locations.ROBOT:
                return self.inventoryController.mobileRobot
            case Locations.K1:
                return getattr(self.inventoryController.workbench, 'k1', default)
            case Locations.K1A:
                return getattr(self.inventoryController.workbench.k1, 'slotA', default)
            case Locations.K1B:
                return getattr(self.inventoryController.workbench.k1, 'slotB', default)
            case Locations.K2:
                return getattr(self.inventoryController.workbench, 'k2', default)
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

    def _create_new_commission(self, **kwargs) -> CommissionData:
        """
        Creates a new commission and adds it to the commissionViewModel.
        Parameters
        :param source: source location
        :type source: Locations
        :param target: target location
        :type target: Locations
        :param cup: True if Commission is a cup, False if not
        :type cup: bool
        :param pallet: True if Commission is a pallet, False if not
        :type pallet: bool
        :param object: object id
        :type object: int
        :return: created commission
        :rtype: CommissionData
        """
        commission = CommissionData(
            id=self.commissionViewModel.new_comission_id(),
            source= kwargs.get('source'),
            target= kwargs.get('target'),
            object=kwargs.get('object'),
            cup=kwargs.get('cup'),
            pallet=kwargs.get('pallet'),
            state= CommissionState.PREPARE if kwargs.get('prepare') else CommissionState.OPEN,
            velocity = kwargs.get('velocity'))
        self.commissionViewModel.add(commission)
        self.new_commission.emit(commission)
        return commission

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
                velocity = Velocity[line['CommissionData']['velocity']]
                commissionData.append(CommissionData(
                    id = int(line['CommissionData']['id']),
                    source= source,
                    target=target,
                    object=int(line['CommissionData']['object']),
                    cup=cup,
                    pallet=pallet,
                    velocity=velocity,
                    state=state
                ))
                #print(commissionData[-1].source.value)
        return commissionData

    def sortComissionData(self):
        self.commissionViewModel.commissionData.sort(key = lambda x: (x.state == CommissionState.DONE, x.id))
        # [print(x.state) for i, x in enumerate(self.commissionViewModel.commissionData)]

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
                    'velocity' : commission.velocity.name,
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
        if self.inventory_copy is None:
            self.inventory_copy = self._setupInventoryCopy()
        if self.workbench_copy is None:
            self.workbench_copy = self._setupWorkbenchCopy()
        if self.mobile_robot_copy is None:
            self.mobile_robot_copy = self._setupMobileRobotCopy()
        valid = True
        for commission in self.commissionViewModel.commissionData:
            if commission.state != CommissionState.DONE:
                source, target, cup, pallet, object = commission.source, commission.target, commission.cup, commission.pallet, commission.object
                data = {
                    'commission': commission,
                    'cup': cup,
                    'inventory': self.inventory_copy,
                    'object': object,
                    'pallet': pallet,
                    'source': source,
                    'valid': valid,
                    'target': target,
                    'workbench': self.workbench_copy,
                    'robot': self.mobile_robot_copy,
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
        valid: bool = kwargs.get('valid')
        source: Locations = kwargs.get('source')
        target: Locations = kwargs.get('target')
        pallet: bool = kwargs.get('pallet')
        inventory: Inventory = kwargs.get('inventory')
        workbench: Workbench = kwargs.get('workbench')
        cup: bool = kwargs.get('cup')
        robot: MobileRobot = kwargs.get('robot')
        # commission = kwargs.get('commission')
        # object = kwargs.get('object')

        if valid:
            if pallet:
                # get object from source
                sEPallet = None
                if source.name[0] == 'L':
                    source_row = int(source.name[1]) // 6 - 1
                    source_col = int(source.name[1]) % 6
                    sEPallet = inventory.pallets[source_row][source_col].pallet
                elif source.name[0] == 'K':
                    sEPallet = workbench.k1 if source.name[1] == '1' else workbench.k2
                # set object to target
                if target.name[0] == 'L':
                    target_row = int(target.name[-1]) // 6 if len(target.name) ==2 else int(target.name[1:-1]) // 6 - 1
                    target_col = int(target.name[-1]) % 6 -1 if len(target.name) ==2 else int(target.name[1:-1]) % 6
                    print( f"target_row: {target_row}, target_col: {target_col}")
                    inventory.setStoragePallet(target_row, target_col, sEPallet)
                elif target.name[0] == 'K':
                    if target.name[1] == '1':
                        #workbench.k1 = sEPallet
                        sEPallet.setLocation(workbench.k1)
                    else:
                        #workbench.k2 = sEPallet
                        sEPallet.setLocation(workbench.k2)
            elif cup:
                # get object from source
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
                elif source == Locations.ROBOT:
                    sECup = self.mobile_robot_copy.cup
                # set object to target
                if target.name[0] == 'L':
                    target_row = int(target.name[1]) // 6 - 1
                    target_col = int(target.name[1]) % 6
                    if target.name[-1] == 'A':
                        #inventory.pallets[target_row][target_col].pallet.slotA = sECup
                        sECup.setLocation(inventory.pallets[target_row][target_col].pallet)
                    else:
                        #inventory.pallets[target_row][target_col].pallet.slotB = sECup
                        sECup.setLocation(inventory.pallets[target_row][target_col].pallet)
                elif target.name[0] == 'K':
                    if target.name[1] == '1':
                        if target.name[-1] == 'A':
                            #workbench.k1.slotA = sECup
                            sECup.setLocation(workbench.k1.slotA)
                        if target.name[-1] == 'B':
                            #workbench.k1.slotB = sECup
                            sECup.setLocation(workbench.k1.slotB)
                    else:
                        if target.name[-1] == 'A':
                            #workbench.k2.slotA = sECup
                            sECup.setLocation(workbench.k2.slotA)
                        else:
                            #workbench.k2.slotB = sECup
                            sECup.setLocation(workbench.k2.slotB)
                elif target == Locations.ROBOT and sECup is not None:
                    self.mobile_robot_copy.cup = sECup
                    sECup.setLocation(robot)

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
            'workbench': workbench,
            'robot': self.mobile_robot_copy,
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
            'workbench': workbench,
            'robot': self.mobile_robot_copy,
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
        robot = kwargs.get('robot')

        

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
        robot = kwargs.get('robot')

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
        robot = kwargs.get('robot')

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
        robot = kwargs.get('robot')

        locName = target.name
        row = int(locName[-1]) //6 if len(locName) == 2 else int(locName[1:-1])//6
        col = int(locName[-1]) %6 -1 if len(locName) == 2 else int(locName[1:-1]) % 6 -1
        sE = inventory.pallets[row][col].pallet
        if pallet and sE is not None:
            self.eventlogService.write_event("CommissionController",
                                            f"Commission {commission.id} is invalid: target location {target.name} is not empty.")
            valid = False
            return valid
        elif pallet and sE is None:
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

    def _setupMobileRobotCopy(self) -> MobileRobot:
        """
        Creates and returns a copy of invController's mobileRobot object.
        """
        mobileRobot = MobileRobot()
        if self.inventoryController.mobileRobot.cup is not None:
            mobileRobot.cup = Cup(
                id=self.inventoryController.mobileRobot.cup.id,
                product=Product(
                    id=self.inventoryController.mobileRobot.cup.product.id,
                    name=""
                )
            )
        return mobileRobot
    
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
                prodA = 0
                prodB = 0
                cupA = 0
                cupB = 0
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
    

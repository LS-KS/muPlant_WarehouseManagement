import pytest
from src.model.DataModel import *
from src.controller.invController import invController
from src.viewmodel.productlistViewModel import ProductListViewModel
from src.viewmodel.storageViewModel import StorageViewModel
from src.viewmodel.productSummaryViewModel import ProductSummaryViewModel
from src.service.EventlogService import EventlogService
from PySide6.QtCore import Qt
from PySide6 import QtCore

"""
This module contains tests for the functions of InventoryController class. 
Test should pass but throw some warnings and coverage will not give any results. 
last run:
date: 21.06.2023
lines covered: na due to pyside6 code
"""


def testInit():
    iC = invController()
    iC.eventlogService =  EventlogService()
    assert isinstance(iC.inventory, Inventory)
    assert isinstance(iC.gripper, Gripper)
    assert isinstance(iC.workbench, Workbench)
    assert isinstance(iC.mobileRobot, MobileRobot)
    assert len(iC.inventory.pallets) == 3
    assert len(iC.inventory.pallets[1]) == 6
    assert isinstance(iC.inventory.pallets[1][1], StorageElement)
    assert isinstance(iC.eventlogService, EventlogService)


def testViewModelInit():
    """
    Note: ViewModel cannot be tested with pytest since it's C++ code!
    Only initialization can be testet. If initialization is done correctly, their values in invController will be other than None
    :return:
    """
    iC = invController()
    iC.eventlogService =  EventlogService()
    assert isinstance(iC.productListViewModel, ProductListViewModel)
    assert isinstance(iC.storageViewModel, StorageViewModel)
    assert isinstance(iC.productSummaryViewModel, ProductSummaryViewModel)


def testDumpToFile():
    iC = invController()
    iC.eventlogService =  EventlogService()
    iC._dumpStorage()
    assert True


def testMoveToWorkbench():
    ic = invController()
    ic.eventlogService =  EventlogService()
    pallet1 = Pallet()
    pallet2 = Pallet()
    product = Product(1, "Banane")
    cup1 = Cup(1, product)
    cup2 = Cup(2, product)
    cup3 = Cup(3, product)
    cup4 = Cup(4, product)
    pallet1.setSlotA(cup1)
    pallet1.setSlotB(cup2)
    pallet2.setSlotA(cup3)
    ic.movePalletToK1(pallet1)
    ic.movePalletToK2(pallet2)
    assert pallet1 == ic.workbench.k1
    assert pallet1.location == ic.workbench
    assert pallet2 == ic.workbench.k2
    assert pallet2.location == ic.workbench
    assert ic.gripper.object is None
    ic.moveCupToK2(cup4)
    assert pallet2.slotB == cup4
    assert cup4.location == pallet2
    with pytest.raises(ValueError) as info:
        ic.moveCupToK1(cup4)


def testMoveToMobileRobot():
    ic = invController()
    ic.eventlogService =  EventlogService()
    product = Product(1, "Banane")
    cup = Cup(1, product)
    cup2 = Cup(2, product)
    ic.moveCupToMobileRobot(cup)
    assert ic.mobileRobot.cup == cup
    assert cup.location == ic.mobileRobot
    assert ic.gripper.object is None
    with pytest.raises(ValueError) as info:
        ic.moveCupToMobileRobot(cup2)


def testMoveToStorage():
    ic = invController()
    ic.eventlogService =  EventlogService()
    pallet1 = Pallet()
    pallet2 = Pallet()
    ic.movePalletToK1(ic.inventory.getStoragePallet(0, 0))
    assert ic.inventory.getStoragePallet(0, 0) is None
    ic.movePalletToStorage(pallet1, 0, 0)
    assert pallet1 == ic.inventory.getStoragePallet(0, 0)
    assert pallet1.location is not None
    ic.movePalletToK2(ic.inventory.getStoragePallet(0, 1))
    assert ic.inventory.getStoragePallet(0, 1) is None
    ic.movePalletToStorage(pallet1, 0, 1)
    assert pallet1 == ic.inventory.getStoragePallet(0, 1)
    assert ic.inventory.getStoragePallet(0, 0) is None
    with pytest.raises(ValueError) as info:
        ic.movePalletToStorage(pallet2, 0, 1)


def testMoveAround():
    ic = invController()
    ic.eventlogService =  EventlogService()
    pallet = ic.inventory.getStoragePallet(1, 1)
    ic.movePalletToK1(pallet)
    assert ic.workbench.k1 == pallet
    assert ic.inventory.getStoragePallet(1, 1) is None
    assert ic.gripper.object is None
    cup = pallet.slotA
    ic.moveCupToMobileRobot(pallet.slotA)
    assert cup == ic.mobileRobot.cup
    assert ic.workbench.k1.slotA is None
    assert ic.gripper.object is None
    with pytest.raises(AttributeError) as info:  # raises AttributeError because k2 has no pallet
        ic.moveCupToK2(ic.mobileRobot.cup)
    ic.moveCupToK1(ic.mobileRobot.cup)
    assert ic.workbench.k1.slotA == cup
    ic.movePalletToK2(pallet)
    assert ic.workbench.k1 is None
    assert ic.workbench.k2 == pallet
    ic.movePalletToStorage(pallet, 1, 1)
    assert ic.workbench.k2 is None
    assert ic.inventory.getStoragePallet(1, 1) == pallet



def testChangeStorage():
    ic = invController()
    ic.eventlogService =  EventlogService()
    pallet_origin = ic.inventory.getStoragePallet(0,5)
    a_cup_origin = pallet_origin.slotA
    a_product = a_cup_origin.product
    assert a_cup_origin.id == 0
    assert a_product.id == 0
    ic.changeStorage("L6", 'a', 15, 5, "Yes")
    pallet_new = ic.inventory.getStoragePallet(0, 5)
    assert pallet_origin == pallet_new
    a_cup_new = pallet_origin.slotA
    assert a_cup_origin == a_cup_new
    a_product = a_cup_new.product
    assert a_cup_new.id == 15
    assert a_product.id == 5

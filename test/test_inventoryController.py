import pytest
from src.model.DataModel import *
from src.controller.invController import invController
from src.viewmodel.productlistViewModel import ProductListViewModel
from src.viewmodel.storageViewModel import StorageViewModel
from src.viewmodel.productSummaryViewModel import ProductSummaryViewModel
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
    assert isinstance(iC.inventory, Inventory)
    assert isinstance(iC.gripper, Gripper)
    assert isinstance(iC.workbench, Workbench)
    assert isinstance(iC.mobileRobot, MobileRobot)
    assert len(iC.inventory.pallets) == 3
    assert len(iC.inventory.pallets[1]) == 6
    assert isinstance(iC.inventory.pallets[1][1], StorageElement)

def testViewModelInit():
    """
    Note: ViewModel cannot be tested with pytest since it's C++ code!
    Only initialization can be testet. If initialization is done correctly, their values in invController will be other than None
    :return:
    """
    iC = invController()
    assert isinstance(iC.productlistViewModel, ProductListViewModel)
    assert isinstance(iC.storageViewModel, StorageViewModel)
    assert isinstance(iC.productSummaryViewModel, ProductSummaryViewModel)

def testDumpToFile():
    iC = invController()
    iC.dumpStorage()
    assert True

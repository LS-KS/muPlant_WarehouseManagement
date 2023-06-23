import pytest
from src.model.DataModel import *
from src.controller.invController import invController

"""
This module contains tests for the functions of InventoryController class. 

last run:
date: 21.06.2023
lines covered: 100% (perfect)
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

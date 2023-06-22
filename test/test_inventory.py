import pytest
from src.model.DataModel import Cup, Product, Pallet,StorageElement, Gripper, Workbench, MobileRobot, Inventory
"""
This module contains tests for the consistency of Datamodel classes. 
The tests check if the methods of these classes work as expected and if the interactions between these classes are 
likely consistent.

date: 21.06.2023
lines coverage: 82% (fine)
"""

def testProductWithCup():
    """
    Testcase for consistency of Product and Cup classes.
    First initializes product and cup object while cup gets product with initialization.
    calls products withoutCup method and asserts all necessary changes.

    Afterwards a product change with two cups and two products is tested
    :return:
    """
    prod1 = Product(1, "Banana")
    cup1 = Cup(3, prod1)
    assert 3 == cup1.id
    assert prod1 == cup1.getProduct()
    assert prod1.cups == [cup1]

    #delete cup from products cups list
    prod1.withoutCup(cup1)
    assert prod1.cups == []
    assert cup1.getProduct() == None

    #test product change
    prod2 = Product(2, "Apple")
    cup2 = Cup(2)
    prod2.withCup(cup2)
    assert cup2.product == prod2
    assert cup2 in prod2.cups
    prod2.withCup(cup1)
    assert cup1.product == prod2
    assert cup2.product == prod2

def testProductCupPallet():
    """
    Testcase for consistency of Product and Cup together with Pallet classes.

    :return:
    """

    prod1 = Product(1, "Banana")
    cup1 = Cup(1, prod1)

    prod2 = Product(2, "Apple")
    cup2 = Cup(2, prod2)

    pallet = Pallet()
    pallet.setSlotA(cup1)
    pallet.setSlotB(cup2)
    assert pallet.slotA == cup1
    assert pallet.slotB == cup2
    assert cup1.location == pallet
    assert cup2.location == pallet

    pallet.setSlotA(cup2)
    assert pallet.slotA == cup2
    assert pallet.slotB is None
    assert cup1.location is None
    assert cup2.location == pallet
    pallet.setSlotB(cup2)
    assert pallet.slotA is None
    assert pallet.slotB == cup2
    assert cup1.location == None
    assert cup1.location is None

def testStorageElement():
    """
    Testcase for Pallet StorageElement combination
    :return:
    """
    element = StorageElement(1,1)
    pallet1 = Pallet()
    pallet2 = Pallet()
    assert element.row == 1
    assert element.col == 1

    element.setPallet(pallet1)
    assert element.pallet == pallet1
    assert pallet1.location == element
    element.setPallet(None)
    element.setPallet(pallet2)
    assert element.pallet == pallet2
    assert pallet1.location == None
    assert pallet2.location == element

def testCupProductPalletStorageElement():
    """
    Testcase for all classes: Cup, Product, Pallet and StorageElement
    :return:
    """

    product1 = Product(1, "Bananensaft")
    product2 = Product(2, "Kirschsaft")
    cup1 = Cup(1,product1)
    cup2 = Cup(2,product2)
    pallet1 = Pallet()
    pallet1.setSlotA(cup1)
    pallet2 = Pallet()
    pallet2.setSlotB(cup2)
    element1 = StorageElement(1,1)
    element1.setPallet(pallet1)
    element2 = StorageElement(1,2)
    element2.setPallet(pallet2)
    assert cup1.location == pallet1
    assert pallet1.location == element1
    assert cup2.location == pallet2
    assert pallet2.location == element2
    element2.setPallet(None)
    assert element2.pallet is None
    assert pallet2.location is None
    element2.setPallet(pallet1)
    assert pallet1.location == element2
    assert element2.pallet == pallet1
    assert element1.pallet is None
    assert pallet2.location is None

def testGripper():
    """
    Gripper class testcase
    :return:
    """
    prod = Product(1, "Kiwi")
    cup = Cup(1, prod)
    pallet = Pallet()
    pallet.setSlotA(cup)
    sE = StorageElement(1,1)
    sE.setPallet(pallet)
    gripper = Gripper()
    gripper.setObject(pallet)
    assert gripper.object == pallet
    assert pallet.location == gripper
    assert sE.pallet == None
    assert pallet.slotA == cup
    assert cup.product == prod

def testWorkbench():
    """
    Testcase for Workbench methods.
    creates two products and one workbench objects.
    Then shifts Pallets around.
    :return:
    """
    pallet1 = Pallet()
    pallet2 = Pallet()
    workbench = Workbench()
    workbench.setK1(pallet1)
    workbench.setK2(pallet2)
    assert workbench.k1 == pallet1
    assert workbench.k2 == pallet2
    with pytest.raises(ValueError) as info:
        workbench.setK1(pallet2)
    assert workbench.k1 == pallet1
    workbench.setK1(None)
    workbench.setK1(pallet2)
    assert workbench.k1 == pallet2
    assert workbench.k2 == None
    workbench.setK2(pallet2)
    assert workbench.k1 == None
    assert workbench.k2 == pallet2

def testMobileRobotGripper():
    """
    Testcase for Mobile Robot together with a Cup object and Gripper objects.
    passes the cup around and asserts changes.
    :return:
    """
    mobi = MobileRobot()
    grip = Gripper()
    cup = Cup(1, Product(1, "Banana"))
    mobi.setCup(cup)
    assert mobi.cup == cup
    assert cup.location == mobi
    grip.setObject(cup)
    assert cup.location == grip
    assert grip.object == cup
    assert mobi.cup == None
    mobi.setCup(cup)
    assert cup.location == mobi
    assert grip.object == None
    assert mobi.cup == cup

def testInventoryGripper():
    grip = Gripper()
    inv = Inventory(None)
    pallet = Pallet()
    grip.setObject(pallet)
    assert grip.object == pallet
    assert pallet.location == grip
    assert len(inv.pallets) == 3
    assert len(inv.pallets[0]) == 6
    inv.setStoragePallet(1,1,pallet)
    assert inv.pallets[1][1].pallet == pallet
    assert grip.object == None
    assert pallet.location == inv.pallets[1][1]
    grip.setObject(pallet)
    assert grip.object == pallet
    assert inv.pallets[1][1].pallet == None
    inv.setStoragePallet(0,0,pallet)
    assert inv.pallets[0][0].pallet == pallet
    assert grip.object == None
    assert pallet.location == inv.pallets[0][0]
    inv.setStoragePallet(1,1,pallet)
    assert inv.pallets[1][1].pallet == pallet
    assert pallet.location == inv.pallets[1][1]
    assert inv.pallets[0][0].pallet == None


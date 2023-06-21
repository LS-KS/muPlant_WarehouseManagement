import pytest
from src.model.DataModel import Cup, Product, Pallet,StorageElement


def testProductWithCup():
    prod1 = Product(1, "Banana")
    cup1 = Cup(3, prod1)
    assert 3 == cup1.id
    assert prod1 == cup1.getProduct()
    assert prod1.cups == [cup1]
    prod1.withoutCup(cup1)
    assert prod1.cups == []
    assert cup1.getProduct() == None
    prod2 = Product(2, "Apple")
    cup2 = Cup(2)
    prod2.withCup(cup2)
    assert cup2.product == prod2
    assert cup2 in prod2.cups
    prod2.withCup(cup1)
    assert cup1.product == prod2
    assert cup2.product == prod2


def testProductCupPallet():
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


def testStorageELement():
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

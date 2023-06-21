import pytest
from src.model.DataModel import Cup, Product, Pallet


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
    assert cup1.storage == pallet
    assert cup2.storage == pallet

    pallet.setSlotA(cup2)
    assert pallet.slotA == cup2
    assert pallet.slotB is None
    assert cup1.storage is None
    assert cup2.storage == pallet
    pallet.setSlotB(cup2)
    assert pallet.slotA is None
    assert pallet.slotB == cup2
    assert cup1.storage == None
    assert cup1.storage is None
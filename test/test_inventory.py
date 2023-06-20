
from src.model.DataModel import Cup, Product

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
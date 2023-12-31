from PySide6.QtCore import QObject, Signal
from typing import List


class Inventory:
    """
    Implements the storage rack in µPlant.
    holds an 2D List which represents row col in the factory.
    Each array slot holds a StorageElement which can hold a pallet.
    This way pallets don't have to bear their location.

    :param pallets: 2D List

    :type pallets: StorageElement

    :param invController : InventoryController

    """

    def __init__(self, controller):
        """
        Initialize inventory object and fills pallets array with StorageElements
        :param controller:

        """
        self.pallets: List[List[StorageElement]] = []
        self.invController = controller
        for row in range(3):
            self.pallets.append([])
            for col in range(6):
                self.pallets[row].append(StorageElement(row=row, col=col, inventory=self))
                self.pallets[row][col].locations = self.calcLocations(row, col)

    def getStoragePallet(self, row, col):
        """
        Returns pallet object at given index.
        :param row:
        :type row: int
        :param col:
        :type col: int
        :return: Returns Pallet object at given position
        :rtype: Pallet or None if no pallet is stored
        """
        return self.pallets[row][col].pallet

    def setStoragePallet(self, row: int, col: int, pallet):
        """
        Sets a pallet into the storage at given position.
        Throws ValueError if storage Position is not empty.
        Calls SetLocation method of pallet.
        :param row:
        :param col:
        :param pallet:
        :return:
        """
        if self.pallets[row][col].pallet == pallet:
            return self
        if self.pallets[row][col].pallet is not None:
            raise ValueError(f"In this spot {row}/{col} is actually already a pallet object {self.pallets[row][col]}!")
        self.pallets[row][col].pallet = pallet # (K->L) everything fine here
        if pallet is not None:
            if pallet.location is not self.pallets[row][col]:
                pallet.setLocation(self.pallets[row][col])

    def calcLocations(self, row, col):
        from src.model.CommissionModel import Locations
        for i, loc in enumerate(Locations):
            if loc.name[0] == 'L' and loc.name[-1] in ['A', 'B']:
                if (int(loc.name[1]) - 1) // 6 == row and (int(loc.name[1]) - 1) % 6 == col:
                    return [loc, Locations[(str(loc.name[0:-1]) + 'B')]]
        return None


class MobileRobot:
    """
    Implements Mobile Robot class from µPlant.
    can store up to one cup in two different sizes.
    last revision: 21.06.20223
    :param cup: stores cup on mobile Robot
    :type cup: Cup
    """

    def __init__(self):
        """
        Initializes cup field with None value
        """
        self.cup = None

    def setCup(self, cup):
        """
        sets Cup on mobile Robot.

        :param cup:
        :return:
        """
        if self.cup == cup:
            return self
        oldValue = self.cup
        if self.cup is not None:
            self.cup = None
            oldValue.setLocation(None)
        self.cup = cup
        if cup is not None:
            if cup.location is not self:
                cup.setLocation(self)


class Workbench:
    """
    Implements Workbench class from µPlant.
    Workbench stores up to two palette items.
    last revision: 20.06.20223
    :param k1: stores pallet on K1 slot
    :type k1: Pallet
    :param k2: stores pallet on K2 slot
    :type k2: Pallet
    """

    def __init__(self):
        """
        Initialize all paarameters with None value
        """

        self.k1: Pallet = None
        self.k2: Pallet = None

    def setK1(self, pallet):
        """
        Sets or removes a Pallet object in location spot k1.
        Raises an ValueError if K1 is already occupied

        If the new pallet is not None and is not already associated with this slot,
        adds this storage element object location object of the new pallet.

        If the new pallet is None and this storage element object is associated with an existing pallet,
        it throws a ValueError.

        :param pallet: The new pallet object to store in
        :type pallet: Pallet
        """
        if self.k1 == pallet:
            return self
        if self.k1 is not None and pallet is not None:
            raise ValueError("In this spot is actually already a pallet object!")
        oldValue = self.k1
        self.k1 = None
        if oldValue is not None:
            oldValue.setLocation(None)
        self.k1 = pallet
        if pallet is not None:
            if pallet.location is not self:
                pallet.setLocation(self)
            if self.k1 == self.k2:
                self.k2 = None

    def setK2(self, pallet):
        """
        Sets or removes a Pallet object in location spot k2.
        Raises an ValueError if K2 is already occupied

        If the new pallet is not None and is not already associated with this slot,
        adds this storage element object location object of the new pallet.

        If the new pallet is None and this storage element object is associated with an existing pallet,
        it throws a ValueError.

        :param pallet: The new pallet object to store in
        :type pallet: Pallet
        """
        if self.k2 == pallet:
            return self
        if self.k2 is not None and pallet is not None:
            raise ValueError("In this spot is actually already a pallet object!")
        oldValue = self.k2
        self.k2 = None
        if oldValue is not None:
            oldValue.setLocation(None)
        self.k2 = pallet
        if pallet is not None:
            if pallet.location is not self:
                pallet.setLocation(self)
            if self.k1 == self.k2:
                self.k1 = None


class Gripper(QObject):
    """
    Implements Gripper data class from µPlant industrial robotic arm.
    Gripper stores a cup or a pallet object while transport operation is in progress.
    Idea is to prevent data loss if program interruption occurs whilst progress.
    last revision: 21.06.20223

    :param object: Stores either cup object or pallet object (or None)
    :type id: Cup or Pallet (or None)
    """

    def __init__(self):
        """
        initialize data object with None value
        """
        self.object = None
        self.objectChanged = Signal(bool, bool, int, int, str, int, int,
                                    str)  # isPallet, isCup, cup, prod, productname, cup, row, productname

    def setObject(self, object):
        """
        takes a Cup or Pallet data object.
        raises an ValueError if gripper already has an object.
        calls objects setLocation function to set gripper as objects location
        :param object:
        :type object: Cup, Pallet or None
        :return:
        """
        if self.object == object:
            return self
        if self.object is not None and object is not None:
            raise ValueError("This spot is actually already occupied!")
        oldValue = self.object
        self.object = None
        if oldValue is not None:
            oldValue.setLocation(None)
        self.object = object
        if object is not None:
            if object.location is not self:
                object.setLocation(self)

    def emitObject(self):
        """
        emits a signal with the current object data
        """
        if self.object is None:
            self.objectChanged.emit(False, False, 0, 0, "", 0, 0, "")
        elif isinstance(self.object, Pallet):
            if object.slotA is not None:
                cupA = object.slotA.id
                prodA = object.slotA.product.id
                prodNameA = object.slotA.product.name
            else:
                cupA = 0
                prodA = 0
                prodNameA = ""
            if object.slotB is not None:
                cupB = object.slotB.id
                prodB = object.slotB.product.id
                prodNameB = object.slotB.product.name
            else:
                cupB = 0
                prodB = 0
                prodNameB = ""
            self.objectChanged.emit(True, False, cupA, prodA, prodNameA, cupB, prodB, prodNameB)
        elif isinstance(self.object, Cup):
            self.objectChanged.emit(False, True, self.object.id, self.object.product.id, self.object.product.name,
                                    self.object.row, self.object.col, self.object.location.name)
        else:
            raise ValueError("Object is not a Cup or Pallet object!")


class Product:
    """
    Implements Product class from µPlant.
    Cup stores an id and name beside a list of Cups filled with the product.
    last revision: 20.06.20223

    :param id: The id of the product
    :type id: int
    :param name: The name of the product
    :type name: str
    """

    def __init__(self, id, name):
        """
        Initializes a new instance of the Product class.

        :param id: The id of the product
        :type id: int
        :param name: The name of the product
        :type name: str
        """
        self.id: int = id
        self.name: str = name
        self.cups: List[Cup] = []

    def withCup(self, cup):
        """
        Adds a Cup object to the cups list if it is not already in the list.

        :param cup: The Cup object to add to the cups list
        :type cup: Cup
        :return: The instance of the Product class on which the method was called
        :rtype: Product
        :raises TypeError: If cup is not an instance of the Cup class
        """
        if isinstance(cup, Cup):
            if not cup in self.cups:
                self.cups.append(cup)
                cup.setProduct(self)
            else:
                return self
        else:
            raise TypeError("cup is not Cup object")

    def withoutCup(self, cup):
        """
        Removes a Cup object from the cups list if it is not already removed from the list.

        :param cup: The Cup object to add to the cups list
        :type cup: Cup
        :return: The instance of the Product class on which the method was called
        :rtype: Product
        :raises TypeError: If cup is not an instance of the Cup class
        """
        if isinstance(cup, Cup) and cup in self.cups:
            self.cups.remove(cup)
        if cup.product == self:
            cup.setProduct(None)


class Cup:
    """
    Implements Cup class from µPlant which exists in two sizes.
    Only small size matters for warehouse management so size will be ignored.
    Cup stores an id and product.
    last revision: 20.06.20223

    :param id: The id of the cup
    :type id: int
    :param product: The product stored in the cup
    :type product: Product
    """

    def __init__(self, id: int, product=None):
        """
        Initializes a new instance of the Cup class.

        :param id: The id of the cup
        :type id: int
        :param product: The product stored in the cup
        :type product: Product
        :param location: the location object where the cup is stored (Pallet, MobileRobot, Gripper)
        """
        self.id: int = id
        self.product: Product = product
        self.location: Pallet | MobileRobot | Gripper = None
        if product != None:
            product.withCup(self)

    def getID(self):
        """
        Returns the id of the cup.

        :return: The id of the cup
        :rtype: int
        """
        return self.id

    def getProduct(self):
        """
        Returns the product stored in the cup.

        :return: The product stored in the cup
        :rtype: Product
        """
        return self.product

    def setID(self, id):
        """
        Sets the id of the cup.

        :param id: The new id of the cup
        :type id: int
        """
        self.id = id

    def setProduct(self, product):
        """
        Sets the product stored in the cup. If the cup already has a product,
        calls the withoutCup method on the existing product before setting the new product.

        If the new product is not None and is not already associated with this Cup object,
        adds this Cup object to the cups list of the new product.

        If the new product is None and this Cup object is associated with an existing product,
        calls the withoutCup method on the existing product before setting the new product to None.

        :param product: The new product to store in the cup
        :type product: Product
        """
        oldValue = self.product
        if self.product is None and product is not None:
            self.product = product
            if not self in product.cups:
                product.cups.append(self)
        elif product is None:
            if self.product is not None and self in self.product.cups:
                self.product.withoutCup(self)
            self.product = product
        else:
            self.product = None
            if oldValue.cups.__contains__(self):
                oldValue.withoutCup(self)
            self.product = product
            if not self in product.cups:
                product.cups.append(self)

    def setLocation(self, location):
        """
        Sets the storage stored the cup is stored in.
        Note, that the Cup cannot now the exact spot of the storage item.
        Therefor if storage is instance of Pallet, use Pallets setSlotA(Cup) / setSlotb(Cup) methods
        storage can be Mobile Robot, Pallet or Gripper

        :param location:
        :return: Cup
        """
        if self.location == location:
            return self
        oldValue = self.location
        if self.location is not None:
            self.storage = None
            if isinstance(oldValue, Pallet):
                pass
            if isinstance(oldValue, Gripper):
                oldValue.setObject(None)
            if isinstance(oldValue, MobileRobot):
                oldValue.setCup(None)
        self.location = location
        if location is not None:
            if isinstance(location, Pallet):
                pass
            if isinstance(location, Gripper):
                location.setObject(self)
            if isinstance(location, MobileRobot):
                location.setCup(self)
        if isinstance(oldValue, Pallet):
            if oldValue.slotA == self:
                oldValue.slotA = None
            if oldValue.slotB == self:
                oldValue.slotB = None
        return self


class Pallet:
    """
    Implements Pallet class from µPlant which stores up tp two cups.
    Cup objects are stored in slotA and slotB and shall be set by corresponding methods.
    last revision: 21.06.20223

    :param location: The location object in which the pallet is stored (Workbench, Gripper, Inventory)
    :param slotA: slot for a Cup object which represents the slot in the front of storage bar.
    :param slotB: slot for a Cup object which represents the slot in the rear of storage bar.    """

    def __init__(self):
        """
        Initializes a new instance of the Pallet class with all attributes as None.

        :param location: The location object in which the pallet is stored (Workbench, Gripper, Inventory)
        :param slotA: slot for a Cup object which represents the slot in the front of storage bar.
        :param slotB: slot for a Cup object which represents the slot in the rear of storage bar.
        """
        self.location = None
        self.slotA: Cup = None
        self.slotB: Cup = None

    def setSlotA(self, cup):
        """
        Sets or removes a Cup obeject in the front slot of this pallet object.
        If the slot already has a cup,
        calls the setLocation method on the existing cup with None as param before setting the new cup.

        If the new cup is not None and is not already associated with this Pallet object,
        adds this Pallet object location object of the new cup.

        If the new cup is None and this Pallet object is associated with an existing cup,
        calls the setLocation method on the existing cup before setting the new cup to None.

        :param cup: The new cup to store in the cup
        :type cup: Cup
        """
        if self.slotA == cup:
            return self
        oldValue = self.slotA
        if self.slotA is not None:
            self.slotA = None
            oldValue.setLocation(None)
        self.slotA = cup
        if cup is not None:
            if cup.location is not self:
                cup.setLocation(self)
        if self.slotA == self.slotB:
            self.slotB = None

    def setSlotB(self, cup):
        """
        Sets or removes a Cup obeject in the rear slot of this pallet object.
        If the slot already has a cup,
        calls the setLocation method on the existing cup with None as param before setting the new cup.

        If the new cup is not None and is not already associated with this Pallet object,
        adds this Pallet object location object of the new cup.

        If the new cup is None and this Pallet object is associated with an existing cup,
        calls the setLocation method on the existing cup before setting the new cup to None.

        :param cup: The new cup to store in the cup
        :type cup: Cup
        """
        if self.slotB == cup:
            return self
        oldValue = self.slotB
        if self.slotB is not None:
            self.slotB = None
            oldValue.setLocation(None)
        self.slotB = cup
        if cup is not None:
            if cup.location is not self:
                cup.setLocation(self)
        if self.slotB == self.slotA:
            self.slotA = None

    def setLocation(self, storageElement):
        if self.location == storageElement:
            return self
        oldValue = self.location
        if oldValue is not None:
            if isinstance(oldValue, StorageElement):
                oldValue.setPallet(None)
            if isinstance(oldValue, Gripper):
                oldValue.setObject(None)
            if isinstance(oldValue, Workbench):
                if oldValue.k1 == self:
                    oldValue.setK1(None)
                if oldValue.k2 == self:
                    oldValue.setK2(None)
        self.location = storageElement
        if storageElement is not None:
            if isinstance(storageElement, StorageElement):
                if storageElement.pallet is not self:
                    storageElement.setPallet(self)
            elif isinstance(storageElement, Gripper):
                if storageElement.object is not self:
                    storageElement.setObject(self)


class StorageElement:
    """
    StorageElement represents a slot in µPlant storage bar, so there are 18 static objects.
    Each usually holds one or none pallet object which should be also the same.
    :param row: represents the storage bar row
    :type row: int
    :param col: represents the storage bar column
    :type col: int
    :param pallet: stores the pallet or nothing
    :type pallet: Pallet
    :param inventory: parent class of StorageElement
    :type inventory: Inventory
    """

    def __init__(self, row, col, inventory=None):
        """
        initialize the storage element object.
        :param row: represents the storage bar row
        :type row: int
        :param col: represents the storage bar column
        :type col: int
        :param pallet: stores the pallet or nothing
        :type pallet: Pallet
        :param inventory: parent class of StorageElement
        :type inventory: Inventory
        """
        self.row: int = row
        self.col: int = col
        self.pallet: Pallet = None
        self.inventory: Inventory = inventory
        self.locations: List[Locations] = []

    def setPallet(self, pallet):
        """
        Sets or removes a Pallet object in location spot of the storage bar.
        If the storage element already has a pallet object,
        calls the setLocation method on the existing pallet with None as param before setting the new pallet.

        If the new pallet is not None and is not already associated with this storage element object,
        adds this storage element object location object of the new pallet.

        If the new pallet is None and this storage element object is associated with an existing pallet,
        it throws a ValueError.

        :param pallet: The new pallet object to store in
        :type pallet: Pallet
        """
        if self.pallet == pallet:
            return self
        if self.pallet is not None and pallet is not None:
            raise ValueError("In this spot is actually already a pallet object!")
        oldValue = self.pallet
        self.pallet = None
        if oldValue is not None:
            oldValue.setLocation(None)
        self.pallet = pallet
        if pallet is not None:
            if pallet.location is not self:
                pallet.setLocation(self)

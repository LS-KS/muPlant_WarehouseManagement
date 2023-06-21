
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
        self.id = id
        self.name = name
        self.cups = []

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

    def __init__(self, id: int, product = None):
        """
        Initializes a new instance of the Cup class.

        :param id: The id of the cup
        :type id: int
        :param product: The product stored in the cup
        :type product: Product
        """
        self.id = id
        self.product = product
        self.storage = None
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
        if self.product is None and product is not None:
            self.product = product
            if not self in product.cups:
                product.cups.append(self)
        elif product is None:
            if self.product is not None and self in self.product.cups:
                self.product.withoutCup(self)
            self.product = product

    def setStorage(self, storage):
        """
        Sets the storage stored the cup is stored in.
        Note, that the Cup cannot now the exact spot of the storage item.
        Therefor if storage is instance of Pallet, use Pallets setSlotA(Cup) / setSlotb(Cup) methods
        storage can be Mobile Robot, Pallet or Gripper

        :param storage:
        :return: Cup
        """
        if self.storage == storage:
            return self
        oldValue = self.storage
        if self.storage is not None:
            self.storage = None
            if not isinstance(oldValue, Pallet):
                oldValue.setCup(None)
        self.storage = storage
        if storage is not None and not isinstance(storage, Pallet):
            storage.setCup(self)

        return self


class Pallet:
    """
    Implements Pallet class from µPlant which stores up tp two cups.
    Cup objects are stored in slotA and slotB and shall be set by corresponding methods.
    last revision: 21.06.20223

    :param storage: The storage object in which the pallet is stored (Workbench, Gripper, Inventory)
    :param slotA: slot for a Cup object which represents the slot in the front of storage bar.
    :param slotB: slot for a Cup object which represents the slot in the rear of storage bar.    """
    def __init__(self):
        """
        Initializes a new instance of the Pallet class with all attributes as None.

        :param storage: The storage object in which the pallet is stored (Workbench, Gripper, Inventory)
        :param slotA: slot for a Cup object which represents the slot in the front of storage bar.
        :param slotB: slot for a Cup object which represents the slot in the rear of storage bar.
        """
        self.storage = None
        self.slotA = None
        self.slotB = None


    def setSlotA(self, cup):
        """
        Sets or removes a Cup obeject in the front slot of this pallet object.
        If the slot already has a cup,
        calls the setStorage method on the existing cup with None as param before setting the new cup.

        If the new cup is not None and is not already associated with this Pallet object,
        adds this Pallet object storage object of the new cup.

        If the new cup is None and this Pallet object is associated with an existing cup,
        calls the setStorage method on the existing cup before setting the new cup to None.

        :param cup: The new cup to store in the cup
        :type cup: Cup
        """
        if self.slotA == cup:
            return self
        oldValue = self.slotA
        if self.slotA is not None:
            self.slotA = None
            oldValue.setStorage(None)
        self.slotA = cup
        if cup.storage is not self:
            cup.setStorage(self)
        if self.slotA == self.slotB:
            self.slotB = None

    def setSlotB(self, cup):
        """
        Sets or removes a Cup obeject in the rear slot of this pallet object.
        If the slot already has a cup,
        calls the setStorage method on the existing cup with None as param before setting the new cup.

        If the new cup is not None and is not already associated with this Pallet object,
        adds this Pallet object storage object of the new cup.

        If the new cup is None and this Pallet object is associated with an existing cup,
        calls the setStorage method on the existing cup before setting the new cup to None.

        :param cup: The new cup to store in the cup
        :type cup: Cup
        """
        if self.slotB == cup:
            return self
        oldValue = self.slotB
        if self.slotB is not None:
            self.slotB = None
            oldValue.setStorage(None)
        self.slotB = cup
        if cup.storage is not self:
            cup.setStorage(self)
        if self.slotB == self.slotA:
            self.slotA = None

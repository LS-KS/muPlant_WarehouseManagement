from typing import Union

from src.model.CommissionModel import Locations
from src.model.DataModel import *
from src.constants.Constants import Constants
from src.viewmodel.storageViewModel import StorageViewModel, StorageData
from src.viewmodel.productlistViewModel import ProductListViewModel,ProductData
from src.viewmodel.productSummaryViewModel import ProductSummaryViewModel
from src.service.EventlogService import EventlogService
from PySide6.QtCore import Signal, Slot, QObject
from PySide6.QtCore import Qt
import yaml

class invController(QObject):


    # Signal can be captured in qml file with Connections - syntax and handling on signal called 'onRowClicked'
    transmitStorageData = Signal(str, int, int, bool)
    transmitWorkbenchData = Signal(int, int, bool)
    transmitWorkbenchPallet = Signal(str,int, int, str, bool, int, int, str)
    transmitMobileRobot = Signal(int, int, str)
    transmitGripper = Signal(bool, bool, int, int, str, int, int, str)
    productSelected = Signal(str)
    idSwapped = Signal(int, int)

    def __init__(self, parent=None):
        """
        Controller class which gives access to DataModel module to remain consistent Data.
        """
        super().__init__(parent)
        self.inventory: Inventory = Inventory(self)
        self.mobileRobot: MobileRobot = MobileRobot()
        self.gripper: Gripper = Gripper()
        self.workbench: Workbench = Workbench()
        self.constants: Constants = Constants()
        self.storageViewModel: StorageViewModel | None = None
        self.productListViewModel: ProductListViewModel | None = None
        self.productSummaryViewModel: ProductSummaryViewModel | None = None
        self.eventlogService: EventlogService | None = None
        self.productList: list[Product] = []
        self.__loadData()

    @Slot(str)
    def selectRow(self, message):
        """
        @Slot(str)
        Takes a product ID as argument and emits it as signal productSelected.
        :param message: product id
        :type message: str
        :return: None
        """
        print("selectRow called with message: " + message)
        self.productSelected.emit(message)
    @Slot(str, str)
    def loadStorage(self, storage: str, slot: str):
        """
        @Slot(str, str)
        This method takes data from EditDialog qml file when the user wants to
        override the storage entry.
        Decodes Storage ID 'L1' to L'18' in row / col and checks for ValueErrors.
        Uses invControllers transmitData signal to return product, slot, cup ID and productList index.

        :param storage:
        :type storage: str
        :param slot:
        :type slot: str
        :return: uses Qt Signal object to return product slot, cup ID and productListIndex.
        """

        if storage != "":
            number = int(storage[1:]) # extracts the integer from storage string
            row = (number - 1) // 6
            col = (number - 1) % 6
            if not 0 <= row <= 2:
                raise ValueError("Error could not decode storage(row)")
            if not 0 <= col <= 5:
                raise ValueError("Error could not decode storage(col)")
            palletRole = Qt.DisplayRole + 1
            if slot == "a":
                cupRole = Qt.DisplayRole + 2
                prodRole = Qt.DisplayRole + 3
            elif slot == "b":
                cupRole = Qt.DisplayRole + 5
                prodRole = Qt.DisplayRole + 6
            else:
                raise ValueError("Slot Value error. Slot must be 'a' or 'b'")
            index = self.storageViewModel.createIndex(row, col)
            isPallet = True if self.storageViewModel.data(index, palletRole) == 1 else False
            product = self.storageViewModel.data(index, prodRole)
            print(f"index: {index}, product: {product}")
            productlistIndex = self.productListViewModel.indexOf(product)
            cup = self.storageViewModel.data(index, cupRole)
            self.transmitStorageData.emit(slot, cup, product, isPallet)
    @Slot(str, str)
    def loadWorkbench(self, storage: str, slot: str):
        """
        @Slot(str, int, int, bool)
        This method takes data from WorkbenchDialog.qml file when the user wants to manually
        override the workbench entry.
        Uses invControllers transmitWorkbenchData signal to return product, slot, cup ID and productList index.
        :return:
        """
        if storage == "K1":
            if self.workbench.k1 is not None:
                isPallet = True
                if slot == "a":
                    cupID = self.workbench.k1.slotA
                    productID = self.workbench.k1.slotA.product.id
                elif slot == "b":
                    cupID = self.workbench.k1.slotB
                    productID = self.workbench.k1.slotB.product.id
                else:
                    raise ValueError("Slot Value error. Slot must be 'a' or 'b'")
            else:
                cupID = 0
                productID = 0
                isPallet = False
        elif storage == "K2":
            if self.workbench.k2 is not None:
                isPallet = True
                if slot == "a":
                    cupID = self.workbench.k2.slotA
                    productID = self.workbench.k2.slotA.product.getID()
                elif slot == "b":
                    cupID = self.workbench.k2.slotB
                    productID = self.workbench.k2.slotB.product.getID()
                else:
                    raise ValueError("Slot Value error. Slot must be 'a' or 'b'")
            else:
                cupID = 0
                productID = 0
                isPallet = False
        else:
            raise ValueError("Storage Value error. Storage must be 'K1' or 'K2'")
        self.transmitWorkbenchData.emit(cupID, productID, isPallet)
    @Slot(bool, bool, int, int, int, int)
    def changeGripper(self, isPallet: bool, isCup:bool, cupAID :int, productAID: int, cupBID: int, productBID: int):
        """
        @Slot(bool, bool, int, int, int, int)
        This method takes data from manual gripper override in EditDialog.qml.
        When grippers object is changed, it emits its signal objectChanged to update ProcessView.
        Sets grippers object to None if isPallet and isCup are False.
        :param isPallet: True if the changed data refers to a pallet, else False
        :type isPallet: bool
        :param isCup: True if the changed data refers to a cup, else False
        :type isCup: bool
        :param cupAID: either ID from Cup A if transmitted object shall be an Pallet object or cupID.
        :type cupAID: int
        :param productAID: either ID from Product A if transmitted object shall be an Pallet object or productID.
        :param cupBID: Cup-ID from Cup B if transmitted object shall be an Pallet object, else 0.
        :type cupBID: int
        :param productBID: Product-ID from Product B if transmitted object shall be an Pallet object, else 0.
        :return: None
        """
        if isPallet:
            pallet = Pallet()
            pallet.setSlotA(Cup(cupAID, self.__productFromID(productAID)))
            pallet.setSlotB(Cup(cupBID, self.__productFromID(productBID)))
            if self.gripper.object is not None:
                self.gripper.setObject(None)
            self.gripper.setObject(pallet)
        elif isCup:
            cup = Cup(cupAID, self.__productFromID(productAID))
            self.gripper.setObject(cup)
        else:
            self.gripper.setObject(None)
        productAName = self.__productFromID(productAID).name
        productBName = self.__productFromID(productBID).name
        self.transmitGripper.emit(isPallet, isCup, cupAID, productAID, productAName, cupBID, productBID, productBName)
        self.eventlogService.write_event("Gripper",
                                        f"\n*** ATTENTION ***\n\n!!! GRIPPER OVERRIDE !!!\n\nLocation: Gripper\n\n*** DANGER ***\n\nThe storage information provided might be incorrect. As a result, the robotic arm will move recklessly, posing a severe risk to human life. There is a high possibility of crashes and flying parts that can cause serious injuries or fatalities.\n\n*** THIS IS A LIFE-THREATENING SITUATION ***\n\n>>>>> CHANGES ARE PERMANENT <<<<<\n\n_____\n")
    @Slot()
    def loadGripper(self):
        """
        @Slot()
        emits transmitGripper signal to update ProcessView although no data is changed.
        :return: None
        """
        if self.gripper.object is not None:
            isPallet = isinstance(self.gripper.object, Pallet)
            isCup = isinstance(self.gripper.object, Cup)
            cupAID = self.gripper.object.slotA.id if isPallet else self.gripper.object.id
            productAID = self.gripper.object.slotA.product.id if isPallet else self.gripper.object.product.id
            productAName = self.gripper.object.slotA.product.name if isPallet else self.gripper.object.product.name
            cupBID = self.gripper.object.slotB.id if isPallet else 0
            productBID = self.gripper.object.slotB.product.id if isPallet else 0
            productBName = self.gripper.object.slotB.product.name if isPallet else ""
            print(f"loadGripper: {isPallet}, {isCup}, {cupAID}, {productAID}, {productAName}, {cupBID}, {productBID}, {productBName}")
            self.transmitGripper.emit(isPallet, isCup, cupAID, productAID, productAName, cupBID, productBID, productBName)
        else:
            print(f"loadGripper: False, False, 0, 0, '', 0, 0, ''")
            self.transmitGripper.emit(False, False, 0, 0, "", 0, 0, "")

    @Slot(str, str, int, int, str)
    def changeStorage(self, storage, slot, cupID, productID, palletPresent: str):
        """
        @Slot(str, str, int, int)
        This method takes data from manual storage override in EditDialog.qml.
        Decodes Storage ID 'L1' to L'18' in row / col and checks for ValueErrors.
        checks if the inventory must be changed and performs the change.
        Erases data if isPallet is False.
        Changes StorageViewModel object of invController and calls _dumpStorage() to save
        changes to file.

        :param storage: String like "L17"
        :type storage: str
        :param slot: palette slot 'a' (front) or 'b' (rear)
        :type slot: str
        :param cupID: cup ID
        :type cupID: int
        :param productID: product ID
        :type productID: int
        :return: None
        """
        col, isPallet, row = self.__decodeStorage(palletPresent, storage)

        pallet = self.inventory.getStoragePallet(row, col)
        if isPallet: # if User wants to set a pallet
            self.__handleStorageChangePallet(col, cupID, isPallet, pallet, productID, row, slot)
        else:
            self.__handleStorageChange(col, pallet, row)
        self._dumpStorage()

    def __handleStorageChange(self, col, pallet, row):
        """
        This method handles a storage change if no pallet is present.
        basically it erases the data from the storage and the pallet object, so
        garbage collection can do its job.
        :param col: column index of storage view-model
        :type col: int
        :param pallet: pallet object at given storage location
        :type pallet: Pallet
        :param row: row index of storage view-model
        :return: None
        """
        if pallet is not None:
            pallet.setLocation(None)
            cupA = pallet.slotA
            cupA.product.withoutCup(cupA)
            pallet.setSlotA(None)
            del cupA
            cupB = pallet.slotB
            cupB.product.withoutCup(cupB)
            pallet.setSlotB(None)
            del cupB
            del pallet
        index = self.storageViewModel.createIndex(row, col)
        roleCupA = Qt.DisplayRole + 2
        roleProductA = Qt.DisplayRole + 3
        roleNameA = Qt.DisplayRole + 4
        rolePallet = Qt.DisplayRole + 1
        self.storageViewModel.setData(index, 0, role=roleCupA)
        self.storageViewModel.setData(index, 0, role=Qt.DisplayRole + 3)
        self.storageViewModel.setData(index, self.findProductName(0), role=Qt.DisplayRole + 4)
        self.storageViewModel.setData(index, False, role=rolePallet)
        self.storageViewModel.dataChanged.emit(index, index, [roleCupA, roleProductA, roleNameA, rolePallet])
        roleCupB = Qt.DisplayRole + 5
        roleProductB = Qt.DisplayRole + 6
        roleNameB = Qt.DisplayRole + 7
        self.storageViewModel.setData(index, 0, role=roleCupB)
        self.storageViewModel.setData(index, 0, role=Qt.DisplayRole + 6)
        self.storageViewModel.setData(index, self.findProductName(0), role=Qt.DisplayRole + 7)
        self.storageViewModel.dataChanged.emit(index, index, [roleCupB, roleProductB, roleNameB, rolePallet])

    def __handleStorageChangePallet(self, col, cupID, isPallet, pallet, productID, row, slot):
        """
        This method handles a change in storage in case a pallet is set.
        Performs all necessary checks and creates a new pallet if none exists in given location.
        calls view-models setData() method to update the view-model.
        :param col: column index of storage view-model
        :type col: int
        :param cupID: ID of corresponding cup object in data-model
        :type cupID: int
        :param isPallet: True if User wants to set a pallet
        :type isPallet: bool
        :param pallet: Pallet object if one exists in given location else None
        :type pallet: Pallet
        :param productID: ID of corresponding product object in data-model
        :type productID: int
        :param row: row index of storage view-model
        :type row: int
        :param slot: "a" for front slot or "b" for rear slot of pallet object.
        :type slot: str
        :return: None
        """
        if pallet is None:  # create a new pallet if there is none
            pallet = Pallet()
            pallet.setSlotA(Cup(0, self.__productFromID(0)))
            pallet.setSlotB(Cup(0, self.__productFromID(0)))
            self.inventory.setStoragePallet(row, col, pallet)
        if slot == "a":
            oldproductID = pallet.slotA.product.id
            print(f"to set storage: row: {row}, col: {col}, cup: {cupID}, slot: {slot}, product: {productID}")
            roleCup = Qt.DisplayRole + 2
            roleProduct = Qt.DisplayRole + 3
            roleName = Qt.DisplayRole + 4
            cup_obj = pallet.slotA
        elif slot == "b":
            oldproductID = pallet.slotB.product.id
            print(f"to set storage: row: {row}, col: {col}, cup: {cupID}, slot: {slot}, product: {productID}")
            roleCup = Qt.DisplayRole + 5
            roleProduct = Qt.DisplayRole + 6
            roleName = Qt.DisplayRole + 7
            cup_obj = pallet.slotB
        else:
            raise ValueError("Slot Value error. Slot must be 'a' or 'b'")
        prod_obj = self.__productFromID(productID) # get existing product object from data-model by id
        cup_obj.setProduct(prod_obj)  # set product object to cup object --> calls the withoutCup() of old product
        index = self.storageViewModel.createIndex(row, col)
        cup = self.storageViewModel.setData(index, cupID, role=roleCup)
        product = self.storageViewModel.setData(index, productID, role=roleProduct)
        name = self.storageViewModel.setData(index, self.findProductName(productID), role=roleName)
        rolePallet = Qt.DisplayRole + 1
        pallet = self.storageViewModel.setData(index, isPallet, role=rolePallet)
        self.storageViewModel.dataChanged.emit(index, index, [roleCup, roleProduct, roleName, rolePallet])
        self.idSwapped.emit(product, productID)
        self.eventlogService.write_event("USER", "Inventory Override!")
        oldIndex = self.productListViewModel.indexOf(oldproductID)
        self.productListViewModel.setData(oldIndex, -1, role=Qt.DisplayRole + 3)  # reduces quantity of old product by 1
        newIndex = self.productListViewModel.indexOf(productID)
        self.productListViewModel.setData(newIndex, 1, role=Qt.DisplayRole + 3)  # increases quantity of new product by 1

    def __decodeStorage(self, palletPresent, storage):
        """
        This method decodes the storage ID to row and col.
        :raises ValueError: if row, col or palletPresent could not be decoded
        :param palletPresent: "Yes" or "No" depending if a Pallet is present or not
        :type palletPresent: str
        :param storage: String which describes the storage like "L17"
        :type storage: str
        :return: row, col, isPallet
        :rtype: int, int, bool
        """
        number = int(storage[1:])
        row = (number - 1) // 6
        if not 0 <= row <= 2:
            raise ValueError("Error could not decode storage(row)")
        col = (number - 1) % 6
        if not 0 <= col <= 5:
            raise ValueError("Error could not decode storage(col)")
        if palletPresent == "Yes":
            isPallet = True
        elif palletPresent == "No":
            isPallet = False
        else:
            raise ValueError("Error could not decode palletPresent")
        return col, isPallet, row

    @Slot(str, str, int, int, bool)
    def changeWorkbench(self, storage: str, slot: str, cup_id: int, product_id: int, pallet_present: bool):
        """
        This method changes workbench entry depending on submitted storage.
        gets the pallet object stored in submitted storage and changes the cup object depending on submitted parameters
        slot, cupID, productID and isPallet. If isPallet is False, cup object is set to None and sets product of cup object to None.
        Writes message to eventlogService.
        Calls _dumpStorage() to save changes to file.
        :param storage: can be 'K1' or 'K2'
        :param slot: can be 'a' for front or 'b' for rear slot of pallet object
        :type slot: str
        :param cup_id: ID of cup object in data-model
        :type cup_id: int
        :param product_id: ID of product object in data-model
        :type product_id: int
        :param pallet_present: True if User wants to set a pallet
        :type pallet_present: bool
        :return: None
        """
        print(f"to set workbench: storage: {storage}, slot: {slot}, cup: {cup_id}, product: {product_id}, isPallet: {pallet_present}")
        if storage == "K1":
            pallet = self.workbench.k1
            if pallet is not None:
                cup_obj_a = pallet.slotA if pallet.slotA is not None else Cup(0, self.__productFromID(0))
                cup_obj_b = pallet.slotB if pallet.slotB is not None else Cup(0, self.__productFromID(0))
                if slot == "a":
                    pass
                elif slot == "b":
                    pass
                else:
                    raise ValueError("Slot Value error. Slot must be 'a' or 'b'")
            else:
                pallet = Pallet()
                cup_obj_a = Cup(0, self.__productFromID(0))
                cup_obj_b = Cup(0, self.__productFromID(0))
        elif storage == "K2":
            pallet = self.workbench.k2
            if pallet is not None:
                cup_obj_a = pallet.slotA if pallet.slotA is not None else Cup(0, self.__productFromID(0))
                cup_obj_b = pallet.slotB if pallet.slotB is not None else Cup(0, self.__productFromID(0))
                if slot == "a":
                    pass
                elif slot == "b":
                    pass
                else:
                    raise ValueError("Slot Value error. Slot must be 'a' or 'b'")
            else:
                pallet = Pallet()
                cup_obj_a = Cup(0, self.__productFromID(0))
                cup_obj_b = Cup(0, self.__productFromID(0))
        else:
            raise ValueError("Storage Value error. Storage must be 'K1' or 'K2'")
        if pallet_present:
            if slot == "a":
                cup_obj_a.setID(cup_id)
                cup_obj_a.setProduct(self.__productFromID(product_id))
            elif slot == "b":
                cup_obj_b.setID(cup_id)
                cup_obj_b.setProduct(self.__productFromID(product_id))
        else:
            cup_obj_a.setID(0)
            cup_obj_a.setProduct(self.__productFromID(0))
            cup_obj_b.setID(0)
            cup_obj_b.setProduct(self.__productFromID(0))
        pallet.setSlotA(cup_obj_a)
        pallet.setSlotB(cup_obj_b)
        if storage == "K1":
            self.workbench.setK1(pallet)
            cup_a_id = self.workbench.k1.slotA.id
            prod_a_id = self.workbench.k1.slotA.product.id
            prod_a_name = self.workbench.k1.slotA.product.name
            cup_b_id = self.workbench.k1.slotB.id
            prod_b_id = self.workbench.k1.slotB.product.id
            prod_b_name = self.workbench.k1.slotB.product.name
        elif storage == "K2":
            self.workbench.setK2(pallet)
            cup_a_id = self.workbench.k2.slotA.id
            prod_a_id = self.workbench.k2.slotA.product.id
            prod_a_name = self.workbench.k2.slotA.product.name
            cup_b_id = self.workbench.k2.slotB.id
            prod_b_id = self.workbench.k2.slotB.product.id
            prod_b_name = self.workbench.k2.slotB.product.name
        else:
            raise ValueError("Storage Value error. Storage must be 'K1' or 'K2'")
        self.transmitWorkbenchPallet.emit(storage, cup_a_id, prod_a_id, prod_a_name, pallet_present, cup_b_id, prod_b_id, prod_b_name)
        self._dumpStorage()
        print(f"transmitWorkbenchPallet emitted:{storage} {cup_a_id}, {prod_a_id},{prod_a_name}, {pallet_present}, {cup_b_id}, {prod_b_id}, {prod_b_name}")
        self.eventlogService.write_event("USER", "Workbench override!")
    @Slot(int, int)
    def changeMobileRobot(self, cupID: int, productID: int):
        """
        @Slot(int, int)
        This method takes data from TurtleDialog. It is used to change the mobile robot's cup and product.
        Checks the cupID and productID for ValueErrors.
        Writes changes to inventoryController's mobile Robot object.
        Emits transmitMobileRobot signal with data stored in self.mobileRobot cup and product data.
        Writes an event to the eventlogService.
        :param cupID:
        :type cupID: int
        :param productID:
        :type productID: int
        :return: None
        """
        oldCup = self.mobileRobot.cup
        if oldCup is not None:
            oldCup.setProduct(None)
            oldCup.setLocation(None)
        del oldCup
        newCup = Cup(cupID, self.__productFromID(productID))
        self.mobileRobot.setCup(newCup)
        cupID = self.mobileRobot.cup.id
        productID = self.mobileRobot.cup.product.id
        name = self.__productFromID(productID).name
        self.transmitMobileRobot.emit(cupID, productID, name)
        print(f"transmitMobileRobot emitted:{cupID}, {productID}, {name}")
    @Slot(str)
    def getWorkbenchSlot(self, slot: str):
        """
        @Slot(str)
        This method passes workbench data to the GUI.
        Decodes Slot ID 'K1' or 'K2' and checks for ValueErrors.
        Calls transmitWorkbenchPallet signal with data stored in self.workbench.
        :param slot: Slot 'K1' or 'K2'
        :type slot: str
        :return: None
        """
        print(f"getWorkbenchSlot: {slot}")
        if slot == "K1":
            pallet = self.workbench.k1 if self.workbench.k1 is not None else None
            if pallet is not None:
                cupIDA = pallet.slotA
                productIDA = pallet.slotA.product.getID()
                isPallet = True
                cupIDB = pallet.slotB
                productIDB = pallet.slotB.product.getID()
            else:
                cupIDA = 0
                productIDA = 0
                isPallet = False
                cupIDB = 0
                productIDB = 0
        elif slot == "K2":
            pallet = self.workbench.k2 if self.workbench.k2 is not None else None
            if pallet is not None:
                cupIDA = pallet.slotA
                productIDA = pallet.slotA.product.getID()
                isPallet = True
                cupIDB = pallet.slotB
                productIDB = pallet.slotB.product.getID()
            else:
                cupIDA = 0
                productIDA = 0
                isPallet = False
                cupIDB = 0
                productIDB = 0
        else:
            raise ValueError("Slot Value error. Slot must be 'K1' or 'K2'")
        productNameA = self.findProductName(productIDA)
        productNameB = self.findProductName(productIDB)
        print(f"getWorkbenchSlot: {slot}, {cupIDA}, {productIDA}, {productNameA}, {isPallet}, {cupIDB}, {productIDB}, {productNameB}")
        self.transmitWorkbenchPallet.emit(slot, cupIDA, productIDA, productNameA, isPallet, cupIDB, productIDB, productNameB)


    def findProductName(self, id: int):
        """
        Method to get product Name from productListModel.
        It is used to emit the changed name for StorageView.qml
        :param id:
        :type id: int
        :return: product name to corresponding index
        :rtype str
        """
        for index, product in enumerate(self.productList):
            if product.id == id:
                return product.name
        return None
    def __loadData(self):
        """
        Load a productList with product ID and name to have appropriate product data.
        Load Storage Data from another File to populate pallets array and viewmodel

        """
        # load product data from Produkte.db
        self.productList = self.__loadProductList()

        # load Inventory from StorageData.db
        storageData = self.__loadStorageData()

        self.__populateInventory(storageData)

        self.__populateViewModels( storageData)
    import yaml

    def _dumpStorage(self):
        """
        Saves the data from StorageViewModel to a YAML file.

        :return: None
        """
        if self.storageViewModel is None:
            raise ValueError("Model not set. Cannot dump data to file")
        else:
            try:
                data_to_dump = []
                rows = self.storageViewModel.rowCount()

                for row in range(rows):
                    row_data = []
                    for col in range(6):
                        storage = self.storageViewModel.storageData[row][col]
                        cell_data = {
                            'row': row,
                            'col': col,
                            'isPalletPresent': bool(storage[0]),
                            'cupID_a': storage[1],
                            'productID_a': storage[2],
                            'cupID_b': storage[4],
                            'productID_b': storage[5]
                        }
                        row_data.append(cell_data)
                    data_to_dump.append(row_data)

                with open(self.constants.STORAGEDATAWRITE, 'w', encoding='utf-8') as file:
                    yaml.dump(data_to_dump, file, default_flow_style=False)

            except FileNotFoundError:
                print("Storage file not found")
            except Exception as e:
                print("Error:", str(e))
            #self.eventcontroller.writeEvent("USER", f"\n Manual Storage Override saved to local File \n")
    def __populateInventory(self, storageData):
        """
        Takes storageData variable to create pallet objects with corresponding cups and products.

        :param storageData:
        :type storageData: List of StorageData objects
        :param productList: List of all possible products
        :type productList: List of Product objects
        :return:

        """
        for element in storageData:
            if element.isPallet:
                pallet = Pallet()
                cup_a = Cup(element.a_CupID, self.__productFromID(element.a_ProductID)) if element.a_ProductID != 0 else None
                pallet.setSlotA(cup_a)
                cup_b = Cup(element.b_CupID, self.__productFromID(element.b_ProductID)) if element.b_ProductID != 0 else None
                pallet.setSlotB(cup_b)
                self.inventory.setStoragePallet(element.row, element.col, pallet)
    import yaml

    def __loadStorageData(self) -> list[StorageData]:
        """
        :return: storageData
        :rtype storageData: List of StorageData objects.
        """
        FILE = self.constants.STORAGEDATA
        storageData = []
        try:
            with open(FILE, 'r', encoding='utf-8') as file:
                data = yaml.safe_load(file)
            for row_data in data:
                for cell_data in row_data:
                    row = cell_data['row']
                    col = cell_data['col']
                    isPallet = cell_data['isPalletPresent']
                    a_CupID = cell_data['cupID_a']
                    a_ProductID = cell_data['productID_a']
                    b_CupID = cell_data['cupID_b']
                    b_ProductID = cell_data['productID_b']
                    a_Name = self.findProductName(a_ProductID)
                    b_Name = self.findProductName(b_ProductID)
                    # Append data to storageData for QAbstractTableModel
                    storageData.append(
                        StorageData(row=row, col=col, isPallet=isPallet, a_CupID=a_CupID, a_ProductID=a_ProductID,
                                    b_CupID=b_CupID, b_ProductID=b_ProductID, a_Name=a_Name, b_Name=b_Name))
        except FileNotFoundError:
            print("Storage data file not found")
        except Exception as e:
            print("Error:", str(e))
        finally:
            if 'file' in locals() and not file.closed:
                file.close()
        return storageData

    def __loadProductList(self):
        """
        Opens YAML file with path from constants.
        Transforms data to object-oriented data.
        :return: productList
        """

        FILE = self.constants.PRODUCTLIST  # Assuming this points to the YAML file path
        productList = []

        try:
            with open(FILE, 'r', encoding='utf-8') as file:
                data = yaml.safe_load(file)

            for product_id, product_name in data.items():
                productList.append(Product(id=int(product_id), name=str(product_name)))

        except FileNotFoundError:
            print("Error: couldn't find product list YAML file")
        except Exception as e:
            print("Error:", str(e))
        finally:
            if 'file' in locals() and not file.closed:
                file.close()

        return productList

    def __populateViewModels(self, storageData):
        """

        Now since data from StorageData.db and Produkte.db is loaded and transformed, it
        can be used to populate viewModels storageViewModel.
        However, for QAbstractTableModel storageData has to be transformed into table struct.

        :param productList:  list of products from loadData method without product quantity
        :type productList: list of ProductData objects.

        :param storageData: product, cup and pallet data stored in storage rack.
        :type storageData: list of StorageData objects

        :return None

        """

        # storageData is now a abject oriented data.
        # to use a TableModel the data must be set in row/col - values
        cols = 6
        rows = 3
        tableData = [[None for col in range(cols)] for row in range(rows)]
        for col in range(cols):
            for row in range(rows):
                for element in storageData:
                    if col == element.col and row == element.row:
                        tableData[row][col] = [element.isPallet, element.a_CupID, element.a_ProductID, element.a_Name,
                                               element.b_CupID, element.b_ProductID, element.b_Name, element.row,
                                               element.col]
        self.storageViewModel = StorageViewModel(storageData=tableData)
        self.__populateProductlistViewModel(storageData)
        '''
        create sortable and filterable viewModel 
        '''
        self.productSummaryViewModel = ProductSummaryViewModel(self.productListViewModel)
    def __populateProductlistViewModel(self, storageData):
        """

        Loop over storageData to calculate existing product quantities.
        For this the ProductData class from ProductListViewModel is used due to
        Product doesn't store quantity information.
        Then set data to controller's ProductListViewModel

        :param productList:  list of products from loadData method
        :type productList: list of Product objects.
        :param storageData: product, cup and pallet data stored in storage rack.
        :type storageData: list of StorageData objects
        :return: None

        """
        productDataList = [] # different to productList due to Product doesn't contain quantity information (senseless)
        for product in self.productList:
            productDataList.append(ProductData(product.id, product.name, 0))
        for stock in storageData:
            for product in productDataList:
                if stock.a_ProductID == product.id:
                    product.quantity += 1
                if stock.b_ProductID == product.id:
                    product.quantity += 1
        '''
            
        productList is used to populate productListViewModel
            
        '''
        self.productListViewModel = ProductListViewModel(productDataList)
    def __productFromID(self, id)->Product:
        """

        Finds Product object from given id and returns the object.
        raises ValueError if no product is found

        :param id: id of Product object that is searched
        :type id: int
        :return: Product object

        """
        for product in self.productList:
            if product.id == id:
                return product
        raise ValueError(f"Id {id} not found!")

    def move_to_gripper(self, object: Union[Pallet, Cup]):
        """
        Moves object to gripper. And updates viewodel and view.

        Gripper is rendered as a pallet. If only a cup shall be rendered,
        isCup must be true and isPallet false. cupAID and productAID as well as productAName must be set.
        all other parameters will be ignored.

        if a cup is transported - this can only be between commissiontable and mobile robot. storage can be ignored in that case. 
        if a pallet is transported - this can only be between storage and  workbench. mobile robot can be ignored.

        :param object: Pallet or Cup object
        :type object: Union[Pallet, Cup]
        :return: None
        """
        source = object.location
        isPallet = isinstance(object, Pallet)
        isCup = isinstance(object, Cup)
        cupAID =object.id if isCup else getattr(object.slotA, "id", 0)
        productAID = object.product.id if isCup else (0 if object.slotA is None else (object.slotA.product, "id", 0))
        productAName = object.product.name if isCup else ( 0 if object.slotA is None else getattr(object.slotA.product, "name", "Kein Becher"))
        cupBID = 0 if isCup else getattr(object.slotB, "id", 0)
        productBID = 0 if isCup else (0 if object.slotA is None else getattr(object.slotB.product, "id", 0))
        productBName = "" if isCup else (0 if object.slotA is None else getattr(object.slotB.product, "name", "Kein Becher"))
        self.gripper.setObject(object)
        self.transmitGripper.emit(isPallet, isCup, cupAID, productAID, productAName, cupBID, productBID, productBName)
        if isPallet:
            if isinstance(source, StorageElement):
                row = source.row
                col = source.col
                self.__handleStorageChange(col, None, row)
            if isinstance(source, Workbench):
                if self.workbench.k1 is None:
                    self.transmitWorkbenchPallet.emit("K1", 0, 0, "", False, 0, 0, "")
                else:
                    if self.workbench.k1.slotA is None:
                        cup_a_id, pro_a_id, pro_a_name = 0, 0, "Kein Becher"
                    else:
                        cup_a_id = self.workbench.k1.slotA.id
                        pro_a_id = self.workbench.k1.slotA.product.id
                        pro_a_name = self.workbench.k1.slotA.product.name
                    if self.workbench.k1.slotB is None:
                        cup_b_id, pro_b_id, pro_b_name = 0, 0, "Kein Becher"
                    else:
                        cup_b_id = self.workbench.k1.slotB.id
                        pro_b_id = self.workbench.k1.slotB.product.id
                        pro_b_name = self.workbench.k1.slotB.product.name
                    self.transmitWorkbenchPallet.emit("K1", cup_a_id, pro_a_id, pro_a_name, True, cup_b_id, pro_b_id, pro_b_name)
                if self.workbench.k2 is None:
                    self.transmitWorkbenchPallet.emit("K2", 0, 0, "", False, 0, 0, "")
                else:
                    if self.workbench.k2.slotA is None:
                        cup_a_id, pro_a_id, pro_a_name = 0, 0, "Kein Becher"
                    else:
                        cup_a_id = self.workbench.k2.slotA.id
                        pro_a_id = self.workbench.k2.slotA.product.id
                        pro_a_name = self.workbench.k2.slotA.product.name
                    if self.workbench.k2.slotB is None:
                        cup_b_id, pro_b_id, pro_b_name = 0, 0, "Kein Becher"
                    else:
                        cup_b_id = self.workbench.k2.slotB.id
                        pro_b_id = self.workbench.k2.slotB.product.id
                        pro_b_name = self.workbench.k2.slotB.product.name
                    self.transmitWorkbenchPallet.emit("K2", cup_a_id, pro_a_id, pro_a_name, True, cup_b_id, pro_b_id, pro_b_name)
        if isCup:
            if source == self.mobileRobot: # Mobile Robot
                self.transmitMobileRobot.emit(0 , 0, "Kein Becher")
            elif source.location == self.workbench: # Workbench
                # notify workbench k1 view
                if self.workbench.k1 is None:
                    cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
                    cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
                    pallet = False
                else:
                    pallet = True
                    if self.workbench.k1.slotA is None:
                        cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
                    else:
                        cupA_id = self.workbench.k1.slotA.id
                        prodA_id = self.workbench.k1.slotA.product.id
                        prodA_name = self.workbench.k1.slotA.product.name
                    if self.workbench.k1.slotB is None:
                        cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
                    else:
                        cupB_id = self.workbench.k1.slotB.id
                        prodB_id = self.workbench.k1.slotB.product.id
                        prodB_name = self.workbench.k1.slotB.product.name
                self.transmitWorkbenchPallet.emit( "K1", cupA_id, prodA_id, prodA_name, pallet, cupB_id, prodB_id, prodB_name)
                # notify workbench k2 view
                if self.workbench.k2 is None:
                    cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
                    cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
                    pallet = False
                else:
                    pallet = True
                    if self.workbench.k2.slotA is None:
                        cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
                    else:
                        cupA_id = self.workbench.k2.slotA.id
                        prodA_id = self.workbench.k2.slotA.product.id
                        prodA_name = self.workbench.k2.slotA.product.name
                    if self.workbench.k2.slotB is None:
                        cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
                    else:
                        cupB_id = self.workbench.k2.slotB.id
                        prodB_id = self.workbench.k2.slotB.product.id
                        prodB_name = self.workbench.k2.slotB.product.name
                self.transmitWorkbenchPallet.emit( "K2", cupA_id, prodA_id, prodA_name, pallet, cupB_id, prodB_id, prodB_name)


    def move_to_robot(self, object):
        """
        Moves a Cup to mobile robot and updates view.
        Note that source is always gripper.
        :param object: Cup object
        :type object: Cup
        """
        object.setLocation(self.mobileRobot)
        self.gripper.setObject(None)
        self.transmitMobileRobot.emit(0, 0, 0)
        self.transmitMobileRobot.emit(object.id, object.product.id, object.product.name)
        self.transmitGripper.emit(False, False, 0, 0, "", 0, 0, "")

    def move_to_workbench(self, object: Union[Cup, Pallet], target: Locations):
        """
        Moves a Cup or a Pallet to workbench and updates view.
        Note, that source is always gripper.

        :param object: Cup or Pallet object
        :type object: Union[Cup, Pallet]
        :param target: Locations.K1 or Locations.K2
        :type target: Locations
        """
        if target == Locations.K1A:
            self.workbench.k1.setSlotA(object)
            string = "K1"
        elif target == Locations.K1B:
            self.workbench.k1.setSlotB(object)
            string = "K1"
        elif target == Locations.K2A:
            self.workbench.k2.setSlotA(object)
            string = "K2"
        elif target == Locations.K2B:
            self.workbench.k2.setSlotB(object)
            string = "K2"
        elif target == Locations.K1:
            self.workbench.setK1(object)
            string = "K1"
        elif target == Locations.K2:
            self.workbench.setK2(object)
            string = "K2"
        else:
            return
        # notify gripper view
        self.transmitGripper.emit(False, False, 0, 0, "", 0, 0, "")

        # notify workbench k1 view
        if self.workbench.k1 is None:
            cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
            cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
            pallet = False
        else:
            pallet = True
            if self.workbench.k1.slotA is None:
                cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
            else:
                cupA_id = self.workbench.k1.slotA.id
                prodA_id = self.workbench.k1.slotA.product.id
                prodA_name = self.workbench.k1.slotA.product.name
            if self.workbench.k1.slotB is None:
                cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
            else:
                cupB_id = self.workbench.k1.slotB.id
                prodB_id = self.workbench.k1.slotB.product.id
                prodB_name = self.workbench.k1.slotB.product.name
        self.transmitWorkbenchPallet.emit( "K1", cupA_id, prodA_id, prodA_name, pallet, cupB_id, prodB_id, prodB_name)
        # notify workbench k2 view
        if self.workbench.k2 is None:
            cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
            cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
            pallet = False
        else:
            pallet = True
            if self.workbench.k2.slotA is None:
                cupA_id, prodA_id, prodA_name = 0, 0, "Kein Becher"
            else:
                cupA_id = self.workbench.k2.slotA.id
                prodA_id = self.workbench.k2.slotA.product.id
                prodA_name = self.workbench.k2.slotA.product.name
            if self.workbench.k2.slotB is None:
                cupB_id, prodB_id, prodB_name = 0, 0, "Kein Becher"
            else:
                cupB_id = self.workbench.k2.slotB.id
                prodB_id = self.workbench.k2.slotB.product.id
                prodB_name = self.workbench.k2.slotB.product.name
        self.transmitWorkbenchPallet.emit( "K2", cupA_id, prodA_id, prodA_name, pallet, cupB_id, prodB_id, prodB_name)
    def move_to_storage(self, object, target: Locations):
        """
        Moves Pallet or Cup to storage.
        view must be updated by updating view model.

        :param object: Pallet or Cup object to be transported
        :type object: Union[Pallet, Cup]
        :param target: Locations.L1 - Locations.L18 if object is Pallet instance. Locations.L1A - Locations.L18B if object is Cup instance.
        :type target: Locations
        """
        if target.name[-1] in ["A", "B"]:
            row = ((int)(target.name[1:-1])-1) // 6
            col = ((int)(target.name[1:-1])-1) % 6
        else: 
            row = ((int)(target.name[1:])-1) // 6 
            col = ((int)(target.name[1:])-1) % 6
        if isinstance(object, Pallet):
            self.inventory.setStoragePallet(row, col, object) #object is fine here
            index = self.storageViewModel.createIndex(row, col) # (K->L) everything fine here	
            base = Qt.DisplayRole
            pallet_role, cup_a_id_role, product_a_id_role, product_a_name_role, cup_b_id_role, product_b_id_role, product_b_name_role = base + 1, base + 2, base + 3, base + 4, base + 5, base + 6, base + 7
            self.storageViewModel.setData(index, True, role=pallet_role)
            cupA_id = getattr(self.inventory.getStoragePallet(row, col).slotA, "id", 0)
            self.storageViewModel.setData(index, cupA_id, role=cup_a_id_role)
            prodA_id = 0 if object.slotA is None else getattr(object.slotA.product, "id", 0)
            self.storageViewModel.setData(index, prodA_id, role=product_a_id_role)
            prodA_name = 0 if object.slotA is None else getattr(object.slotA.product, "name", "")
            self.storageViewModel.setData(index, prodA_name, role=product_a_name_role)
            cupB_id = getattr(self.inventory.getStoragePallet(row, col).slotB, "id", 0)
            self.storageViewModel.setData(index, cupB_id, role=cup_b_id_role)
            prodB_id =  0 if object.slotB is None else getattr(object.slotB.product,"id",0)
            self.storageViewModel.setData(index,prodB_id, role=product_b_id_role)
            prodB_name = 0 if object.slotB is None else getattr(object.slotB.product,"name","")
            self.storageViewModel.setData(index, prodB_name , role=product_b_name_role)
            self.storageViewModel.dataChanged.emit(index, index, [pallet_role, cup_a_id_role, product_a_id_role, product_a_name_role, cup_b_id_role, product_b_id_role, product_b_name_role])
        elif isinstance(object, Cup):
            if target.name[-1] == "A":
                self.inventory.getStoragePallet(row, col).setSlotA(object)
            elif target.name[-1] == "B":
                self.inventory.getStoragePallet(row, col).setSlotB(object)
            else:
                return
            self.storageViewModel.setData(self.storageViewModel.createIndex(row, col), True, role=Qt.DisplayRole + 1)
            self.storageViewModel.setData(self.storageViewModel.createIndex(row, col), getattr(self.inventory.getStoragePallet(row, col).slotA, "id", 0), role=Qt.DisplayRole + 2)
            self.storageViewModel.setData(self.storageViewModel.createIndex(row, col), 0 if self.inventory.getStoragePallet(row, col).slotA is None else getattr(self.inventory.getStoragePallet(row, col).slotA.product, "id", 0), role=Qt.DisplayRole + 3)
            self.storageViewModel.setData(self.storageViewModel.createIndex(row, col), 0 if self.inventory.getStoragePallet(row, col).slotA is None else getattr(self.inventory.getStoragePallet(row, col).slotA.product, "name", ""), role=Qt.DisplayRole + 4)
            self.storageViewModel.setData(self.storageViewModel.createIndex(row, col), getattr(self.inventory.getStoragePallet(row, col).slotB, "id", 0), role=Qt.DisplayRole + 5)
            self.storageViewModel.setData(self.storageViewModel.createIndex(row, col), 0 if self.inventory.getStoragePallet(row, col).slotB is None else getattr(self.inventory.getStoragePallet(row, col).slotB.product,"id",0), role=Qt.DisplayRole + 6)
            self.storageViewModel.setData(self.storageViewModel.createIndex(row, col), 0 if self.inventory.getStoragePallet(row, col).slotB is None else getattr(self.inventory.getStoragePallet(row, col).slotB.product,"name",""), role=Qt.DisplayRole + 7)
        self.transmitGripper.emit(False, False, 0, 0, "", 0, 0, "")
        
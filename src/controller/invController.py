from src.model.DataModel import *
from src.constants.Constants import Constants
from src.viewmodel.storageViewModel import StorageViewModel, StorageData
from src.viewmodel.productlistViewModel import ProductListViewModel,ProductData
from src.viewmodel.productSummaryViewModel import ProductSummaryViewModel
from PySide6.QtCore import Signal, Slot, QObject
from PySide6.QtCore import Qt

class invController(QObject):
    """
    Controller class which gives access to DataModel module to remain consistent Data.

    :param inventory: holds 2D array of StorageElements which can hold a pallet.
    :type inventory: DataModel.Inventory

    :param mobileRobot: represents a mobileRobot in docking station.
    :type mobileRobot: DataModel.MobileRobot

    :param gripper: represents gripper on IRB140, can hold either one cup or pallet
    :type gripper: DataModel.Gripper

    :param workbench: represents physical workbench with two slots for a pallet.
    :type workbench: DataModel.Workbench
    """

    # Signal can be captured in qml file with Connections - syntax and handling on signal called 'onRowClicked'
    transmitData = Signal(str, int, int)
    productSelected = Signal(str)
    idSwapped = Signal(int, int)

    def __init__(self, parent=None):
        """

        create objects of every DataModel entity which is a physical unit.

        """
        super().__init__(parent)
        self.inventory = Inventory(self)
        self.mobileRobot = MobileRobot()
        self.gripper = Gripper()
        self.workbench = Workbench()
        self.constants = Constants()
        self.storageViewModel = None
        self.productlistViewModel = None
        self.productSummaryViewModel = None
        self.eventlogService = None
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
        self.productSelected.emit(message)
    @Slot(str, str)
    def loadStorage(self, storage: str, slot: str):
        """
        @Slot(str, str)
        This method takes data from EditDialog qml file when the user wants to
        override the storage entry.
        Decodes Storage ID 'L1' to L'18' in row / col and checks for ValueErrors.
        Uses invControllers transmitData signal to return productslot, cup ID and productListindex.
        :param storage:
        :type storage: str
        :param slot:
        :type slot: str
        :return: uses Qt Signal object to return productslot, cup ID and productListIndex.
        """

        if storage != "":
            number = int(storage[1:]) # extracts the integer from storage string
            row = (number - 1) // 6
            col = (number - 1) % 6
            if not 0 <= row <= 2:
                raise ValueError("Error could not decode storage(row)")
            if not 0 <= col <= 5:
                raise ValueError("Error could not decode storage(col)")
            if slot == "a":
                cupRole = Qt.UserRole + 2
                prodRole = Qt.UserRole + 3
            elif slot == "b":
                cupRole = Qt.UserRole + 5
                prodRole = Qt.UserRole + 6
            else:
                raise ValueError("Slot Value error. Slot must be 'a' or 'b'")
            index = self.storageViewModel.createIndex(row, col)
            product = self.storageViewModel.data(index, prodRole)
            print(f"index: {index}, product: {product}")
            productlistIndex = self.productlistViewModel.indexOf(product)
            cup = self.storageViewModel.data(index, cupRole)
            self.transmitData.emit(slot, cup, product)
    @Slot(str, str, int, int)
    def changeStorage(self, storage, slot, cupID, productID):
        """
        @Slot(str, str, int, int)
        This method takes data from manual storage override in EditDialog.qml.
        Decodes Storage ID 'L1' to L'18' in row / col and checks for ValueErrors.
        Changes StorageViewModel object of invController and calls _dumpStorage() to save
        changes to file.

        :param storage: String like "L17"
        :type storage: str
        :param slot: palette slot 'a' (front) or 'b' (rear)
        :type slot: int
        :param cupID: cup ID
        :type cupID: int
        :param productID: product ID
        :type productID: int
        :return: None
        """

        number = int(storage[1:])
        row = (number - 1) // 6
        col = (number - 1) % 6
        if not 0 <= row <= 2:
            raise ValueError("Error could not decode storage(row)")
        if not 0 <= col <= 5:
            raise ValueError("Error could not decode storage(col)")
        if slot == "a":
            print(f"to set storage: row: {row}, col: {col}, cup: {cupID}, slot: {slot}, product: {productID}")
            roleCup = Qt.UserRole + 2
            roleProduct = Qt.UserRole + 3
            roleName = Qt.UserRole + 4
        elif slot == "b":
            print(f"to set storage: row: {row}, col: {col}, cup: {cupID}, slot: {slot}, product: {productID}")
            roleCup = Qt.UserRole + 5
            roleProduct = Qt.UserRole + 6
            roleName = Qt.UserRole + 7
        else:
            raise ValueError("Slot Value error. Slot must be 'a' or 'b'")

        index = self.storageViewModel.createIndex(row, col)
        cup = self.storageViewModel.setData(index, cupID, role=roleCup)
        product = self.storageViewModel.setData(index, productID, role=roleProduct)
        name = self.storageViewModel.setData(index, self.findProductName(productID), role=roleName)
        self.storageViewModel.dataChanged.emit(index, index, [roleCup, roleProduct, roleName])
        self.idSwapped.emit(product, productID)
        self.eventlogService.writeEvent("USER",
                                        f"\n*** ATTENTION ***\n\n!!! INVENTORY OVERRIDE !!!\n\nLocation: {storage} - {slot}\nCup: {cup} --> {cupID}\nProduct: {product} --> {productID}\n\n*** DANGER ***\n\nThe storage information provided might be incorrect. As a result, the robotic arm will move recklessly, posing a severe risk to human life. There is a high possibility of crashes and flying parts that can cause serious injuries or fatalities.\n\n*** THIS IS A LIFE-THREATENING SITUATION ***\n\n>>>>> CHANGES ARE PERMANENT <<<<<\n\n_____\n")
        self._dumpStorage()
    def movePalletToK1(self, pallet: Pallet) -> bool:
        """

        Moves a pallet to Workbench's K1 slot.

        :param pallet: The pallet which shall be transported
        :type: Pallet object
        :raises ValueError: if destination is not None
        :return: True if successful, False if not

        """
        if not isinstance(pallet, Pallet):
            return False
        if pallet == self.workbench.k1:
            return True
        if self.workbench.k1 is not None:
            raise ValueError("Pallet can not be transprted to K1 because destination is not empty!")
        pallet.setLocation(self.gripper)
        # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
        self.workbench.setK1(pallet)
        return True
    def moveCupToK1(self, cup: Cup) -> bool:
        """
        Moves a cup to Workbench's K1 slot.

        :param cup: The cup which shall be transported
        :type: Cup object
        :raises ValueError: if the destination has no pallet or existing pallet has no empty cup place
        :return: True if successful
        """
        if not isinstance(cup, Cup):
            return False
        if cup == self.workbench.k1.slotA or cup == self.workbench.k1.slotB:
            return True
        if self.workbench.k1.slotA is not None:
            if self.workbench.k1.slotB is not None:
                raise ValueError("Pallet can not be transprted to K1 because destination is not empty!")
            else:
                self.gripper.setObject(cup)
                # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
                self.workbench.k1.setSlotB(cup)
                return True
        else:
            self.gripper.setObject(cup)
            # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
            self.workbench.k1.setSlotA(cup)
            return True
    def movePalletToK2(self, pallet: Pallet) -> bool:
        """
        Moves a pallet to Workbench's K2 slot.

        :param pallet: The pallet which shall be transported
        :type: Pallet object
        :return: True if successful, False if not

        """
        if not isinstance(pallet, Pallet):
            return False
        if pallet == self.workbench.k2:
            return True
        if self.workbench.k2 is not None:
            raise ValueError("Pallet can not be transprted to K2 because destination is not empty!")
        pallet.setLocation(self.gripper)
        # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
        self.workbench.setK2(pallet)
        return True
    def moveCupToK2(self, cup: Cup) -> bool:
        """
        Moves a cup to Workbench's K2 slot.

        :param cup: The cup which shall be transported
        :type: Cup object
        :raises ValueError: if the destination has no pallet or existing pallet has no empty cup place
        :return: True if successful
        """
        if not isinstance(cup, Cup):
            return False

        if self.workbench.k2.slotA is not None:
            if cup == self.workbench.k2.slotA:
                return True
            if self.workbench.k2.slotB is not None:
                if cup == self.workbench.k2.slotB:
                    return True
                raise ValueError("Pallet can not be transprted to K1 because destination is not empty!")
            else:
                self.gripper.setObject(cup)
                # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
                self.workbench.k2.setSlotB(cup)
                return True
        else:
            self.gripper.setObject(cup)
            # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
            self.workbench.k2.setSlotA(cup)
            return True
    def moveCupToMobileRobot(self, cup:Cup) -> bool:
        """
        Moves a Cup object to the mobile Robot
        not implemented: Creates all necessary commands
        :param cup:
        :return: True if transport was successful
        :raises ValueError: if Mobile Robot is not empty
        """
        if self.mobileRobot.cup == cup:
            return True
        if self.mobileRobot.cup is not None:
            raise ValueError("Mobile Robot is not empty!")
        self.gripper.setObject(cup)
        # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
        self.mobileRobot.setCup(cup)
        return True
    def movePalletToStorage(self, pallet: Pallet, row: int, col: int) -> bool:
        """
        places a Pallet object in inventory at given position.
        not implemented: Creates all necessary commands to ABB controller

        :param pallet: pallet which shall be transported
        :type pallet: Pallet
        :param row:
        :type row: int
        :param col:
        :type col: int
        :return: True if successful

        """
        if self.inventory.getStoragePallet(row, col) is not None:
            raise ValueError( "Target destination is not empty!")
        else:
            self.gripper.setObject(pallet)
            # ToDo: Hier Kommando an ABB Roboter einfügen und warten bis Meldung kommt, dass Kommando ausgeführt wurde.
            self.inventory.setStoragePallet(row, col, pallet)
            return True
    def findProductName(self, id: int):
        """
        Method to get product Name from productListModel.
        It is used to emit the changed name for StorageView.qml
        :param id:
        :type id: int
        :return: product name to corresponding index
        :rtype str
        """
        for index, product in enumerate(self.productlistViewModel.products):
            if product.id == id:
                return product.name
        return None
    def __loadData(self):
        """
        Load a productList with product ID and name to have appropriate product data.
        Load Storage Data from another File to populate pallets array and viemodel

        """
        # load product data from Produkte.db
        productList = self.__loadProductList()

        # load Inventory from StorageData.db
        storageData = self.__loadStorageData(productList)

        self.__populateInventory(storageData, productList)

        self.__populateViewModels(productList, storageData)
    def _dumpStorage(self):
        """

        Saves the data from StorageViewModel to file.

        :return: None

        """
        if self.storageViewModel == None:
            raise ValueError(" Model not set. cannot dump data to file")
        else:
            FILE = None
            try:
                with open(self.constants.STORAGEDATAWRITE, 'w', encoding='utf-8-sig') as FILE:
                    FILE.write("# Row,Col:IsPalletPresent:CupID_a,ProductID_a|CupID_b,ProductID_b\n\n")
                    rows = self.storageViewModel.rowCount()
                    for row in range(rows):
                        r = row
                        for col in range (6):
                            storage = self.storageViewModel.storageData[row][col]
                            c = col
                            p = storage[0]
                            cA = storage[1]
                            pA = storage[2]
                            cB = storage[4]
                            pB = storage[5]
                            FILE.write(f"{r},{c}:{int(p)}:{cA},{pA}|{cB},{pB}\n")
                        FILE.write("\n")
            except FileNotFoundError("Storagefile not found"):
                return None
            finally:
                if FILE != None:
                    FILE.close()
            #self.eventcontroller.writeEvent("USER", f"\n Manual Storage Override saved to local File \n")
    def __populateInventory(self, storageData, productList):
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
                pallet.setSlotA(Cup(element.a_CupID, self.__productFromID(element.a_ProductID, productList)))
                pallet.setSlotB(Cup(element.b_CupID, self.__productFromID(element.b_ProductID, productList)))
                self.inventory.setStoragePallet(element.row, element.col, pallet)
    def __loadStorageData(self, productList) -> list[StorageData]:
        """

        :param productList: List of product data without quantities
        :type productList: List of ProductData objects
        :return: storageData
        :rtype storageData: List of StorageData objects.

        """
        FILE = self.constants.STORAGEDATA
        storageData = []
        try:
            # Open StorageData file and read in lines to list
            # Avoid u\efeff prefix in data by set encodeing to utf8-8-sig (source: stackoverflow)
            with open(FILE, 'r', encoding='utf-8-sig') as file:
                list = file.readlines()

            list = [line for line in list if line != '\n']  # remove empty lines
            list = list[1:]  # remove first line

            for line in list:
                splitData = line.strip().split(',')  # strip and split to get raw data
                splitData[1] = splitData[1].strip().split(':')
                splitData[2] = splitData[2].strip().split('|')
                # map the split data to Inevntory Data
                row = int(splitData[0])
                col = int(splitData[1][0])
                isPallet = True if splitData[1][1] == '1' else False
                a_CupID = int(splitData[1][2])
                a_ProductID = int(splitData[2][0])
                a_Name = ""
                b_CupID = int(splitData[2][1])
                b_ProductID = int(splitData[3])
                b_Name = ""
                # find matching product strings from actual product list
                for product in productList:
                    if product.id == a_ProductID:
                        a_Name = product.name
                    if product.id == b_ProductID:
                        b_Name = product.name
                    if a_Name != "" and b_Name != "":
                        break
                # append data to storageData for QAbstractTableModel
                storageData.append(
                    StorageData(row=row, col=col, isPallet=isPallet, a_CupID=a_CupID, a_ProductID=a_ProductID,
                                b_CupID=b_CupID, b_ProductID=b_ProductID, a_Name=a_Name, b_Name=b_Name))
                # print(f"Row: {row}\t Col: {col}\t isPallet: {isPallet}\t Cup_A: {a_CupID}\t ProductA: {a_ProductID}, {a_Name}\t Cup_B: {b_CupID}\t ProductB: {b_ProductID}, {b_Name} ")
        except FileNotFoundError:
            print("Error: could't find product list file 'StorageData.db'")
        except FileExistsError:
            print("Error: file 'StorageData.db' doesn't exist")
        finally:
            file.close()
        return storageData
    def __loadProductList(self) -> list[Product]:
        """
        Opens file with path from constants.
        transforms data to object-oriented data
        :return: productList
        :rtype: list of Product

        """
        FILE = self.constants.PRODUCTLIST
        productList = []
        try:
            # Open product file and read lines to list.
            # Avoid u\ufeff prefix in data by set encoding to utf8-8-sig (source: stackoverflow)
            with open(FILE, 'r', encoding='utf-8-sig') as file:
                list = file.readlines()

            for line in list:
                # Split the line by ';' to get the id and name
                product_data = line.strip().split(';')
                product_id = int(product_data[0])
                product_name = str(product_data[1])
                productList.append(Product(id=product_id, name=product_name))
        except FileNotFoundError:
            print("Error: could't find product list file 'Produkte.db'")
        except FileExistsError:
            print("Error: file 'Produkte.db' doesn't exist")
        finally:
            file.close()
        return productList
    def __populateViewModels(self, productList, storageData):
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
        self.__populateProductlistViewModel(productList, storageData)
        '''
        create sortable and filterable viewModel 
        '''
        self.productSummaryViewModel = ProductSummaryViewModel(self.productlistViewModel)
    def __populateProductlistViewModel(self, productList, storageData):
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
        for product in productList:
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
        self.productlistViewModel = ProductListViewModel(productDataList)
    def __productFromID(self, id, productList):
        """

        Finds Product object from given id and returns the object.
        raises ValueError if no product is found

        :param id: id of Product object that is searched
        :type id: int
        :param productList:
        :type productList: List of Product objects
        :return: Product object

        """
        for product in productList:
            if product.id == id:
                return product
        raise ValueError(f"Id {id} not found!")

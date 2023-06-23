from src.model.DataModel import *
from src.constants.Constants import Constants
from src.viewmodel.storageViewModel import StorageViewModel, StorageData
from src.viewmodel.productlistViewModel import ProductListViewModel,ProductData
from src.viewmodel.productSummaryViewModel import ProductSummaryViewModel

class invController:
    """
    Controller class which gives access to DataModel module to remain consistent Data.
    :param inventory: holds 2D array of StorageElements which can hold a pallet.
    :type inventory; DataModel.Inventory
    :param mobileRobot: represents a mobileRobot in docking station.
    :type mobileRobot: DataModel.MobileRobot
    :param gripper: represents gripper on IRB140, can hold either one cup or pallet
    :type gripper: DataModel.Gripper
    :param workbench: represents physical workbench with two slots for a pallet.
    :type workbench: DataModel.Workbench
    """
    def __init__(self):
        """
        create objects of every DataModel entity which is a physical unit.
        """
        self.inventory = Inventory(self)
        self.mobileRobot = MobileRobot()
        self.gripper = Gripper()
        self.workbench = Workbench()
        self.constants = Constants()
        self.storageViewModel = None
        self.productlistViewModel = None
        self.productSummaryViewModel = None
        self.loadData()

    def loadData(self):
        """
        Load a productList with product ID and name to have appropriate product data.
        Load Storage Data from another File to populate pallets array and viemodel

        """
        # load product data from Produkte.db
        productList = self.loadProductListData()

        # load Inventory from StorageData.db
        storageData = self.loadStorageData(productList)

        self.populateViewModels(productList, storageData)

    def loadStorageData(self, productList):
        """

        :param productList: List of product data without quantities
        :type productList: List of ProductData objects
        :return: storageData
        :type storageData: List of StorageData objects.

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

    def loadProductListData(self):
        """

        Opens file with path from constants.
        transforms data to object-oriented data

        :return: productList

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
                productList.append(ProductData(id=product_id, name=product_name))
        except FileNotFoundError:
            print("Error: could't find product list file 'Produkte.db'")
        except FileExistsError:
            print("Error: file 'Produkte.db' doesn't exist")
        finally:
            file.close()
        return productList

    def populateViewModels(self, productList, storageData):
        """
        Now since data from StorageData.db and Produkte.db is loaded and transformed, it
        can be used to populate viewmodels storageViewModel.
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
        self.populateProductlistViewModel(productList, storageData)
        '''
                create sortable and filterable viewModel 
                '''
        self.productSummaryViewModel = ProductSummaryViewModel(self.productlistViewModel)

    def populateProductlistViewModel(self, productList, storageData):
        """

        Loop over storageData to calculate existing product quantities.
        Then set data to controller's ProductListViewModel
        :param productList:  list of products from loadData method without product quantity
        :type productList: list of ProductData objects.
        :param storageData: product, cup and pallet data stored in storage rack.
        :type storageData: list of StorageData objects

        :return: None
        """
        for stock in storageData:
            for product in productList:
                if stock.a_ProductID == product.id:
                    product.quantity += 1
                if stock.b_ProductID == product.id:
                    product.quantity += 1
        '''
            
            productList is used to populate productListViewModel
            
            '''
        self.productlistViewModel = ProductListViewModel(productList)

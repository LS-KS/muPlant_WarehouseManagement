from src.model.DataModel import *


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
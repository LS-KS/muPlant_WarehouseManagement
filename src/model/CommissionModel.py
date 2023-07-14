from enum import StrEnum

class CommissionData:
    """
    Data Class for CommissionData
    """
    def __init__(self, id, source, target, object, cup, pallet, state = None):
        self.id = id
        self.source = source
        self.target = target
        self.object = object
        self.cup = cup
        self.pallet = pallet
        self.state = CommissionState.OPEN if state is None else state
        #print(f"CommissionData: {self.id}, {self.source}, {self.target}, {self.object}")

class CommissionState(StrEnum):
    """
    Enum for CommissionData State
    """
    OPEN = 'open'
    PENDING ='pending'
    PROGRESS = 'in progress'
    DONE = 'done'

class Locations(StrEnum):
    """
    Enum for CommissionDta locations source and target
    """
    ROBOT = 'Mobile Robot'
    K1A = 'Comm. table K1, slot A'
    K1B = 'Comm. table K1, slot B'
    K2A = 'Comm. table K2, slot A'
    K2B = 'Comm. table K2, slot B'
    GRIPPER = 'Gripper'
    STORAGE = 'Storage'
    # Storage locations
    L1A = 'Storage L1 (top), front'
    L1B = 'Storage L1 (top), rear'
    L2A = 'Storage L2 (top), front'
    L2B = 'Storage L2 (top), rear'
    L3A = 'Storage L3 (top), front'
    L3B = 'Storage L3 (top), rear'
    L4A = 'Storage L4 (top), front'
    L4B = 'Storage L4 (top), rear'
    L5A = 'Storage L5 (top), front'
    L5B = 'Storage L5 (top), rear'
    L6A = 'Storage L6 (top), front'
    L6B = 'Storage L6 (mid), rear'
    L7A = 'Storage L7 (mid), front'
    L7B = 'Storage L7 (mid), rear'
    L8A = 'Storage L8 (mid), front'
    L8B = 'Storage L8 (mid), rear'
    L9A = 'Storage L9 (mid), front'
    L9B = 'Storage L9 (mid), rear'
    L10A = 'Storage L10 (mid), front'
    L10B = 'Storage L10 (mid), rear'
    L11A = 'Storage L11 (mid), front'
    L11B = 'Storage L11 (mid), rear'
    L12A = 'Storage L12 (mid), front'
    L12B = 'Storage L12 (mid), rear'
    L13A = 'Storage L13 (bot), front'
    L13B = 'Storage L13 (bot), rear'
    L14A = 'Storage L14 (bot), front'
    L14B = 'Storage L14 (bot), rear'
    L15A = 'Storage L15 (bot), front'
    L15B = 'Storage L15 (bot), rear'
    L16A = 'Storage L16 (bot), front'
    L16B = 'Storage L16 (bot), rear'
    L17A = 'Storage L17 (bot), front'
    L17B = 'Storage L17 (bot), rear'
    L18A = 'Storage L18 (bot), front'
    L18B = 'Storage L18 (bot), rear'



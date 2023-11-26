from enum import StrEnum

class CommissionData:
    """
    Data Class for CommissionData
    properties:
    id: int - Commission ID (primary key)
    source: Locations - source location
    target: Locations - target location
    object: int - identifier for object (cup-id or pallet-id)
    cup: bool - True if cup is part of commission
    pallet: bool - True if pallet is part of commission
    state: CommissionState(StrEnum) - state of commission
    """
    def __init__(self, id, source, target, object, cup, pallet, state = None):
        self.id: int = id
        self.source: Locations = source
        self.target: Locations = target
        self.object: int = object
        self.cup: bool = cup
        self.pallet: bool = pallet
        self.state: CommissionState = CommissionState.OPEN if state is None else state
        #print(f"CommissionData: {self.id}, {self.source}, {self.target}, {self.object}")

class CommissionState(StrEnum):
    """
    Enum for CommissionData State
    """
    OPEN = 'open'
    PENDING ='pending'
    PROGRESS = 'in progress'
    DONE = 'done'
    ERROR = 'error while executing'

class Locations(StrEnum):
    """
    Enum for CommissionData locations source and target
    """
    ROBOT = 'Mobile Robot'
    K1 = 'Comm. table K1'
    K1A = 'Comm. table K1, slot A'
    K1B = 'Comm. table K1, slot B'
    K2 = 'Comm. table K2'
    K2A = 'Comm. table K2, slot A'
    K2B = 'Comm. table K2, slot B'
    GRIPPER = 'Gripper'
    STORAGE = 'Storage'
    # Storage locations
    L1 = 'Storage L1 (top)'
    L1A = 'Storage L1 (top), front'
    L1B = 'Storage L1 (top), rear'
    L2 = 'Storage L2 (top)'
    L2A = 'Storage L2 (top), front'
    L2B = 'Storage L2 (top), rear'
    L3 = 'Storage L3 (top)'
    L3A = 'Storage L3 (top), front'
    L3B = 'Storage L3 (top), rear'
    L4 = 'Storage L4 (top)'
    L4A = 'Storage L4 (top), front'
    L4B = 'Storage L4 (top), rear'
    L5 = 'Storage L5 (top)'
    L5A = 'Storage L5 (top), front'
    L5B = 'Storage L5 (top), rear'
    L6 = 'Storage L6 (mid)'
    L6A = 'Storage L6 (top), front'
    L6B = 'Storage L6 (mid), rear'
    L7 = 'Storage L7 (mid)'
    L7A = 'Storage L7 (mid), front'
    L7B = 'Storage L7 (mid), rear'
    L8 = 'Storage L8 (mid)'
    L8A = 'Storage L8 (mid), front'
    L8B = 'Storage L8 (mid), rear'
    L9 = 'Storage L9 (mid)'
    L9A = 'Storage L9 (mid), front'
    L9B = 'Storage L9 (mid), rear'
    L10 = 'Storage L10 (mid)'
    L10A = 'Storage L10 (mid), front'
    L10B = 'Storage L10 (mid), rear'
    L11 = 'Storage L11 (mid)'
    L11A = 'Storage L11 (mid), front'
    L11B = 'Storage L11 (mid), rear'
    L12 = 'Storage L12 (mid)'
    L12A = 'Storage L12 (mid), front'
    L12B = 'Storage L12 (mid), rear'
    L13 = 'Storage L13 (bot)'
    L13A = 'Storage L13 (bot), front'
    L13B = 'Storage L13 (bot), rear'
    L14 = 'Storage L14 (bot)'
    L14A = 'Storage L14 (bot), front'
    L14B = 'Storage L14 (bot), rear'
    L15 = 'Storage L15 (bot)'
    L15A = 'Storage L15 (bot), front'
    L15B = 'Storage L15 (bot), rear'
    L16 = 'Storage L16 (bot)'
    L16A = 'Storage L16 (bot), front'
    L16B = 'Storage L16 (bot), rear'
    L17 = 'Storage L17 (bot)'
    L17A = 'Storage L17 (bot), front'
    L17B = 'Storage L17 (bot), rear'
    L18 = 'Storage L18 (bot)'
    L18A = 'Storage L18 (bot), front'
    L18B = 'Storage L18 (bot), rear'



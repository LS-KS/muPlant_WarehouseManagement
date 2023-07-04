from enum import Enum

class CommissionData:
    """
    Data Class for CommissionData
    """
    def __init__(self, id, source, target, object,cup, pallet):
        self.id = id
        self.source = source
        self.target = target
        self.object = object
        self.cup = cup
        self.pallet = pallet
        self.state = CommissionState.OPEN
        print(f"CommissionData: {self.id}, {self.source}, {self.target}, {self.object}")

class CommissionState(Enum):
    """
    Enum for CommissionData State
    """
    OPEN = 1
    PENDING =2
    PROGRESS = 3
    DONE = 4

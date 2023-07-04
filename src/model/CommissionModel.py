from enum import Enum

class CommissionData:
    """
    Data Class for CommissionData
    """
    def __init__(self, id, source, target, object,):
        self.id = id
        self.source = source
        self.target = target
        self.object = object
        self.state = CommissionState.OPEN

class CommissionState(Enum):
    """
    Enum for CommissionData State
    """
    OPEN = 1
    PENDING =2
    PROGRESS = 3
    DONE = 4

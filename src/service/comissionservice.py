from src.controller.CommissionController import CommissionController
from src.model.CommissionModel import CommissionData, CommissionState, Locations
from src.controller.ABBController import ABBController
from PySide6.QtCore import Qt, QThread, QObject, Signal, Slot, QMutex


class CommissionService(QThread):

    def __init__(self, **kwargs):
        self.commission_worker:CommissionWorker = None
        parent = None
        super().__init__(parent)
        self.abb_controller: ABBController = kwargs.get("abb_controller")
        self.commission_controller: CommissionController = kwargs.get("commission_controller")

    def start(self, priority: int = QThread.InheritPriority):
        self.commission_worker = CommissionWorker(self)
        self.commission_worker.moveToThread(self)


class CommissionWorker(QObject):

    def __init__(self, parent):
        super().__init__(parent)
        self.is_running = False

    def main(self):
        self.commission_controller.main()

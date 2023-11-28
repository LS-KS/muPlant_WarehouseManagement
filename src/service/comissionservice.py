import asyncio
from typing import Tuple
from src.controller.CommissionController import CommissionController
from src.model.CommissionModel import CommissionData, CommissionState, Locations
from src.controller.ABBController import ABBController
from PySide6.QtCore import Qt, QThread, QObject, Signal, Slot, QMutex
import time

class CommissionService(QObject):

    handle_commission = Signal(CommissionData)
    update_commission_state = Signal(CommissionData, CommissionState)
    def __init__(self, **kwargs):
        self.commission_worker:CommissionWorker = None
        parent = None
        super().__init__(parent)
        self.abb_controller: ABBController = kwargs.get("abb_controller")
        self.commission_controller: CommissionController = kwargs.get("commission_controller")

    @Slot()
    def start_worker(self):
        print("CommissionService: Starting worker")
        print("CommissionService: Creating CommissionWorker")
        self.commission_worker = CommissionWorker(self)
        self.handle_commission.connect(self.commission_worker.process_new_commission)
        self.commission_worker.commissionstate_changed.connect(self.handel_commission_state_change)
        print("CommissionService: Set CommissionWorker to running")
        self.commission_worker.is_running = True
        print("CommissionService: Handle existing commissions")
        self.handle_existing_commissions()

        
    
    def handle_new_commission(self, commission: CommissionData):
        self.handle_commission.emit(commission)

    def handle_existing_commissions(self):
        for commission in self.commission_controller.commissionViewModel.commissionData:
            if commission.state != CommissionState.DONE:
                self.handle_commission.emit(commission)

    def handel_commission_state_change(self, commission: CommissionData, state: CommissionState):
        print(f"CommissionService: Commission {commission.id} changed state to {state}")
        self.update_commission_state.emit(commission, state)

    def stop_worker(self):
        print("CommissionService: Stopping worker")
        self.commission_worker.is_running = False
        self.commission_worker.quit()
        self.commission_worker.wait()
        print("CommissionService: Worker stopped")

class CommissionWorker(QThread):

    commission_updated = Signal(int, Locations)
    commissionstate_changed = Signal(CommissionData, CommissionState)
    def __init__(self, service: CommissionService, parent=None):
        super().__init__(parent)
        self.commission_service = service
        self.is_running = False
        self.mock = True # Set true to simulate abb movements

    def start(self, priority: int = QThread.InheritPriority) -> None:
        return super().start(priority)

    @Slot()
    def process_new_commission(self, commission: CommissionData):
        """
        If a new commission is created, a signal from CommissionController is emitted called 'new_commission'.
        """
        print(f"CommissionWorker: handle commission {commission.id}, run state: {self.is_running}")
        if self.is_running:
            done = False
            while not done:
                if self.commission_service.abb_controller.check_ready(self.mock):
                    print("CommissionWorker: Commission ready; update to pending")
                    self.commissionstate_changed.emit(commission, CommissionState.PENDING)
                    source_string, target_string = self._create_abb_strings(commission)
                    time.sleep(0.5)
                    print("CommissionWorker: Calculated command strings, slepts well ; update to progress")
                    self.commissionstate_changed.emit(commission, CommissionState.PROGRESS)
                    if not self.mock:
                        print("CommissionWorker: Moving item using abb controller")
                        self.commission_service.abb_controller.move_item(source_string, target_string)
                    else:
                        print("CommissionWorker: Simulating abb movement, set abb controller to busy")
                        self.commission_service.abb_controller.busy = True
                    time.sleep(1.5)
                    print("CommissionWorker: Slept well, update to done")
                    self.commissionstate_changed.emit(commission, CommissionState.DONE)
                    done = True
                    if self.mock:
                        print("CommissionWorker: Simulating abb movement, set abb controller to not busy")
                        self.commission_service.abb_controller.busy = False
            print("CommissionWorker: Commission done")
        else:
            print("CommissionWorker: CommissionWorker not running")
                

    def _create_abb_strings(self, commission: CommissionData) -> Tuple[str, str]:
        """
        Creates the strings which ABBControllerWrapper.dll can parse to RAPID programs called via execute.
        :param commission: CommissionData object
        :type commission: CommissionData
        :return: source_string, target_string
        :rtype: tuple
        """
        source_string = str(commission.source.name)
        target_string = str(commission.target.name)
        return source_string, target_string

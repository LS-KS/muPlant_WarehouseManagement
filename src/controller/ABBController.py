import asyncio

from PySide6.QtCore import QObject, Signal, Slot
from src.controller.PreferenceController import PreferenceController
from src.service.EventlogService import EventlogService
from src.constants.Constants import Constants
import clr


class ABBController(QObject):
    """
    ABB IRB 140 in muPant storage cell uses RobotWare version RW5.15_10.00.9100.
    This class uses the ABBControllerWrapper DLL to establish a connection to the controller unit.
    ABBControllerWrapper is a C# class library using the ABB.Robotics.Controllers library of an old PC SDK.
    DLLs were imported from old Software Application called 'Lagerverwaltung 3.0'.
    """
    notify_transport = Signal(str, str)
    notify_busy = Signal(bool)
    def __init__(self, preferenceController: None | PreferenceController, eventlogService: None | EventlogService,
                 parent=None):
        super().__init__(parent)
        self.preference_controller = preferenceController
        self.eventlog_service = eventlogService
        self.ip = "192.168.2.51"  # garbage value
        self.port = 0
        self.constants = Constants()
        self.abb_controller = None
        self.connected = False
        self.busy = False

    @Slot()
    def setup(self):
        """
        Uses clr module to expose .NET framework to Python.
        .NET version is 6.
        Sets up the ABB controller by adding a reference to the ABBControllerWrapper DLL,
        initializing the ABBLinker class, which establishes a connection to IRC5 controller unit of IRB140.
        Hint: Ignore, that references to C# namespaces, classes and methods are not recognized by IDE.

        :param: None
        :return self.connected:  True if the setup is successful and a connection is established, False otherwise.
        :rtype: bool
        """
        clr.AddReference("dll/ABBControllerWrapper")
        from ABBPythonLinker import ABBLinker
        try:
            self.abb_controller = ABBLinker(str(self.ip))
            self.connected = self.abb_controller.Setup()
        except Exception as e:
            print(f"ABBController: Error during setup: {e}")
            self.abb_controller = None
            self.connected = False
            self.eventlog_service.write_event("ABBController.setup", f"Error during setup: {e}")
        finally:
            return self.connected
        self.eventlog_service.write_event("ABBController.setup", "Setup complete")

    @Slot(str, str)
    def move_item(self, source: str, target: str):
        """
        If setup is successful, this method calls the CreateAndExecute method of the ABBLinker class.
        This creates a command task of the SDK and sends an execute command to the controller unit.
        the strings must be formatted accordingly.
        :param source: formatted string of the execute command
        :type source: str
        :param target: formatted string of the execute command
        :type target: str
        """
        if self.connected and not self.busy:
            self.busy = True
            self.notify_busy.emit(self.busy)
            result = asyncio.run(self.abb_controller.CreateAndExecute(source, target))
        if result:
            self.busy = False
            self.notify_busy.emit(self.busy)
            self.notify_transport.emit(source, target)
            self.eventlog_service.write_event("ABBControlller", f"Moved Item {source}-->{target}")
        else:
            self.busy = False
            self.notify_busy.emit(self.busy)
            self.eventlog_service.write_event("ABBControlller", f"Error moving Item {source}-->{target}, False returned")

    @Slot(result= bool)
    def check_ready(self, mock:bool):
        """
        Checks if the ABB controller is busy.
        :return: True if the controller is busy, False otherwise
        :rtype: bool
        """
        if not mock:
            if self.connected:
                self.notify_busy.emit(self.busy)
                return not self.busy
            else:
                return False
        else:
            return True

    def _loadPreferences(self):
        self.ip = self.preference_controller.preferences.abb.ip
        self.port = self.preference_controller.preferences.abb.port
        print(f"ABB Controller: Settings loaded: Ip: {self.ip}, Port: {self.port}")
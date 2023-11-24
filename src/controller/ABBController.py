import requests
from requests.auth import HTTPDigestAuth
from requests import Session
from PySide6.QtCore import QObject
from src.controller.PreferenceController import PreferenceController
from src.service.EventlogService import EventlogService
from src.constants.Constants import Constants
from typing import Any
import clr
class ABBController( QObject ):
    """
    ABB IRB 140 in muPant storage cell uses RobotWare version RW5.15_10.00.9100.
    This class uses the ABBControllerWrapper DLL to establish a connection to the controller unit.
    ABBControllerWrapper is a C# class library using the ABB.Robotics.Controllers library of an old PC SDK.
    DLLs were imported from old Software Application called 'Lagerverwaltung 3.0'.
    """
    def __init__(self, preferenceController: None | PreferenceController, eventlogService: None | EventlogService, parent= None):
        super().__init__(parent)
        self.preference_controller = preferenceController
        self.eventlog_service = eventlogService
        self.ip = "192.168.2.51" #garbage value
        self.port = 0
        self.constants = Constants()
        self.abb_controller = None
        self.connected = False
        self.busy = False

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
            self.eventlog_service.writeEvent("ABBController.setup", f"Error during setup: {e}")
        finally:
            return self.connected
        
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
            self.abb_controller.CreateAndExecute(source, target)
            self.busy = True
        #TODO: Execution must be in an async function.

    def _loadPreferences(self):
        self.ip = self.preference_controller.preferences.abb.ip
        self.port = self.preference_controller.preferences.abb.port
        print(f"ABB Controller: Settings loaded: Ip: {self.ip}, Port: {self.port}")
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
    class to communicate with ABB RobotWare via ABB's RESTful API.
    ABB IRB 140 in muPant storage cell uses RobotWare version RW5.15_10.00.9100.
    """
    def __init__(self, preferenceController: None | PreferenceController, eventlogService: None | EventlogService, parent= None):
        super().__init__(parent)
        self.preference_controller = preferenceController
        self.eventlog_service = eventlogService
        self.username = "Default User"
        self.password = "robotics"
        self.session = None
        self.ip = "192.168.2.51" #garbage value
        self.port = 0
        self.constants = Constants()
        self.abb_controller = None
    def __del__(self):
        print("ABBController: Destructor called")

    def setup(self):
        abb_path = "dll/ABBControllerWrapper"

        clr.AddReference(abb_path)
        from ABBControllerWrapper import ABBControllerWrapper
        self.abb_controller = ABBControllerWrapper()
        self.abb_controller.Setup(self.ip)
    def _loadPreferences(self):
        self.ip = self.preference_controller.preferences.abb.ip
        self.port = self.preference_controller.preferences.abb.port
        print(f"ABB Controller: Settings loaded: Ip: {self.ip}, Port: {self.port}")
    def _set_variable(self, variable_name, value):
        # url =  f"http://{self.ip}:{self.port}/rw/vars/{variable_name}"
        url = f"http://{self.ip}/rw/vars/{variable_name}"
        payload = {
            "value": value
        }
        return url, payload
    def _get_variable(self, variable_name):
        # url =  f"http://{self.ip}:{self.port}/rw/vars/{variable_name}"
        url = f"http://{self.ip}/rw/vars/{variable_name}"
        return url

    def start_session(self) -> bool:
        """
        Start a session with the ABB robot controller's RESTful API using HTTP digest authentication.
        :return: True if the session was successfully started, False otherwise.
        :rtype: bool
        """
        try:
            self._loadPreferences()
            self.session = Session()
            self.session.auth = HTTPDigestAuth(self.username, self.password)
            # response = self.session.get(f"http://{self.ip}:{self.port}/rw/rapid/symbol/data/RAPID_Variable")
            self.base_url = f"http://{self.ip}"
            # resp = self.session.post(self.base_url + '/rw/rapid/execution?action=resetpp')
            # if resp.status_code == 204:
                # print('Program pointer reset to main')
            # else:
                # print('Could not reset program pointer to main')
            payload = {'LogonUser -name': 'Default User', '-pwd': 'robotics', 'locale Remote App': 'Warehouse Manager.exe', 'loc': 'MRT-PC230', 'alias': 'muPlant'  }
            #payload = {'regain': 'continue', 'execmode': 'continue', 'cycle': 'once', 'condition': 'none',
            #           'stopatbp': 'disabled', 'alltaskbytsp': 'false'}
            response = self.session.post(self.base_url + "/rw/rapid/execution?action=start", data=payload)
            if response.status_code == 200:
                self.eventlog_service.writeEvent(
                    "ABBController.start_session",
                    f"Session initialized."
                )
                return True
            else:
                self.eventlog_service.writeEvent(
                    "ABBController.start_session",
                    f"Session initialization failed. Status code: {response.status_code}"
                )
                return False
        except requests.exceptions.RequestException as e:
            # Handle network-related errors.
            self.eventlog_service.writeEvent(
                "ABBController.start_session",
                f"Session initialization failed: {e}"
            )
            return False
        except Exception as ex:
            # Handle other exceptions.
            self.eventlog_service.writeEvent(
                "ABBController.start_session",
                f"An unexpected error occurred during session initialization: {ex}"
            )
            return False

    def request_mastership(self) -> True:
        """
        Request mastership of the ABB robot controller.
        This method sends a POST request to the ABB robot controller's RESTful API to request mastership.
        Mastership is necessary for controlling the robot and performing certain operations.

        :return: True if mastership request was successful, False otherwise.
        :rtype: bool
        """
        self._loadPreferences()
        try:
            response = self.session.post(f"http://{self.ip}:{self.port}/rw/mastership")
            if response.status_code == 200:
                self.eventlog_service.writeEvent("ABBController.request_mastership: Request successful")
                return True
            else:
                message = response.json().get("message")
                self.eventlog_service.writeEvent(f"ABBController.request_mastership: Request failed: {message}")
        except requests.exceptions.RequestException as e:
            self.eventlog_service.writeEvent("ABBController.request_mastership",f"Request failed: {e}")
            return False
        except Exception as ex:
            self.eventlog_service.writeEvent("ABBController.request_mastership",f"An unexpected error occurred: {ex}")
            return False
    def release_mastership(self):
        self._loadPreferences()
        try:
            response = self.session.post(f"http://{self.ip}:{self.port}/rw/mastership?action=release")
            if response.status_code == 200:
                self.eventlog_service.writeEvent("ABBController.release_mastership: Request successful")
            else:
                message = response.json().get("message")
                self.eventlog_service.writeEvent(f"ABBController.release_mastership: Request failed: {message}")
        except requests.exceptions.RequestException as e:
            self.eventlog_service.writeEvent("ABBController.release_mastership", f"Request failed: {e}")
            return False
        except Exception as ex:
            self.eventlog_service.writeEvent("ABBController.release_mastership", f"An unexpected error occurred: {ex}")
            return False

    def request_rmmp(self):
        try:
            base_url = f"http://{self.ip}:{self.port}"
            response = self.session.post(base_url + '/users/rmmp', data={'privilege': 'modify'})
            if response.status_code == 200:
                self.eventlog_service.writeEvent("ABBController.request_rmmp: Request successful")
            else:
                message = response.json().get("message")
                self.eventlog_service.writeEvent(f"ABBController.request_rmmp: Request failed: {message}")
        except requests.exceptions.RequestException as e:
            self.eventlog_service.writeEvent("ABBController.request_rmmp", f"Request failed: {e}")
            return False
        except Exception as ex:
            self.eventlog_service.writeEvent("ABBController.request_rmmp", f"An unexpected error occurred: {ex}")
            return False

    def cancel_rmmp(self):
        try:
            response = self.session.post(self.base_url + '/users/rmmp?action=cancel')
            if response.status_code == 200:
                self.eventlog_service.writeEvent("ABBController.cancel_rmmp: Request successful")
            else:
                message = response.json().get("message")
                self.eventlog_service.writeEvent(f"ABBController.cancel_rmmp: Request failed: {message}")
        except requests.exceptions.RequestException as e:
            self.eventlog_service.writeEvent("ABBController.cancel_rmmp", f"Request failed: {e}")
            return False
        except Exception as ex:
            self.eventlog_service.writeEvent("ABBController.cancel_rmmp", f"An unexpected error occurred: {ex}")
            return False
    def set_variable(self, variable_name: str, value: Any) -> bool:
        """
        Public Method. Loads actual Settings from PreferenceController (ABB IP and Port).
        After this it writes a PUT Request to ABB-Robot Web Service's RESTful API with submitted variable name and value.
        Result of PUT-Request is submitted to eventlogservice.
        In Case Request was successful, True is returned, else False.
        :param variable_name: Name of variable write to
        :type variable_name: str
        :param value: value that shall be written
        :type value: Any
        :rtype: bool
        """
        self._loadPreferences()
        url, payload = self._set_variable(variable_name, value)
        try:
            response = requests.put(url, json= payload)
            if response.status_code == 200:
                self.eventlog_service.writeEvent("ABBController.set_variable:", f"Request successful: {variable_name} = {value}")
                print(f"PUT- Request successful,{variable_name} = {value}.")
                return True
            else:
                message = response.json().get("message")
                self.eventlog_service.writeEvent("ABBController.set_variable:",
                                                 f"Request failed: {variable_name} = {value}, response = {message}")
                print(f"PUT Request failed!: {variable_name}={value}, response: {message}")
                return False
        except requests.exceptions.RequestException as e:
            print(f"ABBController.set_variable: Request failed: {e}")
            self.eventlog_service.writeEvent("ABBController.set_variable:",f"Request failed: {e}" )
            return False
        except requests.exceptions.ConnectionError as ec:
            print(f"ABBController.set_variable: Failed to connect: {ec}")
            self.eventlog_service.writeEvent("ABBController.set_variable:", f"Request failed: {ec}")
            return False
        except requests.exceptions.Timeout as et:
            print(f"ABBController.set_variable: Timeout: {et}")
            self.eventlog_service.writeEvent("ABBController.set_variable:", f"Timeout: {et}")
            return False
    def get_variable(self, variable_name) -> Any:
        """
        Public Method. Loads actual Settings from PreferenceController (ABB IP and Port).
        After this it writes a GET Request to ABB-Robot Web Service's RESTful API with submitted variable name.
        Result of GET-Request is submitted to eventlogservice.
        In Case Request was successful, value is returned, else False.
        :param variable_name: Name of variable write to
        :type variable_name: str
        :rtype: Any, False if Request failed.
        """
        self._loadPreferences()
        url = self._get_variable(variable_name)
        try:
            response = requests.get(url)
            if response.status_code == 200:
                value = response.json().get("value")
                return value
            else:
                message = response.json().get("message")
                self.eventlog_service.writeEvent("ABBController.get_variable:",
                                         f"Request failed: {variable_name}, response = {message}")
                print(f"GET Request failed!: {variable_name}, response: {message}")
                return False
        except requests.exceptions.RequestException as e:
            print(f"ABBController.get_variable: Request failed: {e}")
            self.eventlog_service.writeEvent("ABBController.get_variable:",f"Request failed: {e}" )
            return False
        except requests.exceptions.ConnectionError as ec:
            print(f"ABBController.get_variable: Failed to connect: {ec}")
            self.eventlog_service.writeEvent("ABBController.get_variable:", f"Request failed: {ec}")
            return False
        except requests.exceptions.Timeout as et:
            print(f"ABBController.get_variable: Timeout: {et}")
            self.eventlog_service.writeEvent("ABBController.get_variable:", f"Timeout: {et}")
            return False


if __name__ == '__main__':
    eventlogService = EventlogService()
    preferenceController = PreferenceController(eventlogService)
    controller = ABBController(preferenceController=preferenceController, eventlogService= eventlogService)
    controller.setup()
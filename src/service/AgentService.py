from src.controller.PreferenceController import PreferenceController
from src.service.EventlogService import EventlogService
from PySide6.QtCore import QObject, Signal, Slot
"""
This Service will provide any necessary functionalities for the muPlant Agent System in the future.

"""

class AgentService(QObject):
    """
    This Service listens to signals from opcuaServices agent variables.
    #TODO:
    """

    def __init__(self, eventlogService: EventlogService, preferenceController : PreferenceController) -> None:
        super().__init__()
        self.eventlogService: EventlogService = eventlogService
        self.running: bool = False
        self.preferenceController : PreferenceController = preferenceController


    @Slot()
    def setupAgentService(self):
        """
        sets up AgentService
        """
        # TODO: implement OPC Agent Server
        self.running = True
        self.eventlogService.write_event("AgentService", "AgentService setup complete (not implemented)")
    
    @Slot()
    def stopAgentService(self):
        """
        Stops running Agentserver
        """
        self.running = False
        self.agentServer = None



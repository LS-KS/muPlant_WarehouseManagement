from src.agentlib.agent import AgentServer
from src.controller.PreferenceController import PreferenceController
from src.service.EventlogService import EventlogService
from PySide6.QtCore import QObject, Signal, Slot
"""
This Service will provide any necessary functionalities for the muPlant Agent System in the future.

"""

class AgentService(QObject):

    def __init__(self, eventlogService: EventlogService, preferenceController : PreferenceController) -> None:
        super().__init__()
        self.eventlogService: EventlogService = eventlogService
        self.preferenceController : PreferenceController = preferenceController
        self.agentServer: AgentServer = None

    @Slot()
    def setupAgentService(self):
        """
        sets up AgentService
        """
        self.agentServer = AgentServer(
            ip = self.preferenceController.preferences.modBus.ip,
            port = self.preferenceController.preferences.modBus.port,
        )
        # TODO: implement OPC Agent Server
        self.eventlogService.writeEvent("AgentService", "AgentService setup complete")
    
    @Slot()
    def stopAgentService(self):
        """
        Stops running Agentserver
        """
        self.agentServer.running = False
        self.agentServer = None



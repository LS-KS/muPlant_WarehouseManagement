from src.agentlib.agent import AgentClient, AgentClientOPC, AgentServer
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
        self.agentClient : AgentClient = None
        self.agentClientOPC : AgentClientOPC = None
        self.agentServer : AgentServer = None

    @Slot()
    def setupAgentService(self):
        """
        sets up AgentService
        """
        self.agentClient = AgentClient(
            agent_id = 0, 
            ip = self.preferenceController.preferences.modBus.ip,
            port = self.preferenceController.preferences.modBus.port,
            slave_id=0, # TODO: find out what slave_id is
            offset=0, # TODO: find out what offset is
            offset_coil=0, # TODO: find out what offset_coil is
        )
        # TODO: implement OPC Agent Client
        self.eventlogService.writeEvent("AgentService", "AgentService setup complete")


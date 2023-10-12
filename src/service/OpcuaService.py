from typing import Optional
from PySide6.QtCore import QThread, QObject, Signal, Slot
import asyncio
import logging
from asyncua import Server, ua, Client
from asyncua.common.methods import uamethod
from src.controller.PreferenceController import PreferenceController
from src.service.EventlogService import EventlogService

class agentVars:
    def __init__(self):
        self.agentAgentLockID = None
        self.agentAgentLockRequest = None
        self.agentDone = None
        self.agentFunctionID = None
        self.agentFunctionID = None
        self.agentFunctionReady = None
        self.agentKeepAlive = None
        self.agentResponseID = None
        self.agentResponseReady = None
        self.agentStatus = None
        self.agentUnused = None
        self.agentWorking = None
        self.agentFuncParameter_1 = None
        self.agentFuncParameter_2 = None
        self.agentFuncParameter_3 = None
        self.agentFuncParameter_4 = None
        self.agentFuncParameter_5 = None
        self.agentFuncParameter_6 = None
        self.agentFuncParameter_7 = None
        self.agentFuncParameter_8 = None
        self.agentFuncParameter_9 = None
        self.agentFuncParameter_10 = None
        self.agentFuncParameter_11 = None
        self.agentFuncParameter_12 = None
        self.agentFuncParameter_13 = None
        self.agentFuncParameter_14 = None
        self.agentFuncParameter_15 = None
        self.agentFuncParameter_16 = None
        self.agentFuncParameter_17 = None
        self.agentFuncParameter_18 = None
        self.agentFuncParameter_19 = None
        self.agentFuncParameter_20 = None
        self.agentFuncParameter_21 = None
        self.agentFuncParameter_22 = None
        self.agentFuncParameter_23 = None
        self.agentFuncParameter_24 = None
        self.agentFuncParameter_25 = None
        self.agentFuncParameter_26 = None
        self.agentFuncParameter_27 = None
        self.agentFuncParameter_28 = None
        self.agentFuncParameter_29 = None
        self.agentFuncParameter_30 = None
        self.agentFuncParameter_31 = None
        self.agentFuncParameter_32 = None
        self.agentRespParameter_1 = None
        self.agentRespParameter_2 = None
        self.agentRespParameter_3 = None
        self.agentRespParameter_4 = None
        self.agentRespParameter_5 = None
        self.agentRespParameter_6 = None
        self.agentRespParameter_7 = None
        self.agentRespParameter_8 = None
        self.agentRespParameter_9 = None
        self.agentRespParameter_10 = None
        self.agentRespParameter_11 = None
        self.agentRespParameter_12 = None
        self.agentRespParameter_13 = None
        self.agentRespParameter_14 = None
        self.agentRespParameter_15 = None
        self.agentRespParameter_16 = None
        self.agentRespParameter_17 = None
        self.agentRespParameter_18 = None
        self.agentRespParameter_19 = None
        self.agentRespParameter_20 = None
        self.agentRespParameter_21 = None
        self.agentRespParameter_22 = None
        self.agentRespParameter_23 = None
        self.agentRespParameter_24 = None
        self.agentRespParameter_25 = None
        self.agentRespParameter_26 = None
        self.agentRespParameter_27 = None
        self.agentRespParameter_28 = None
        self.agentRespParameter_29 = None
        self.agentRespParameter_30 = None
        self.agentRespParameter_31 = None
        self.agentRespParameter_32 = None

class OpcuaServerHandle(QThread):

    def __init__(self, preferenceController: PreferenceController, parent = None, ) -> None:
        QThread.__init__(self, parent)
        self.preferenceController = preferenceController
        self.opcuaServer = None
        self.agent_vars = agentVars()

    
    def run(self):
        """
        Must be implemented for QThread. Wraps asyncio function in sync function.
        """
        asyncio.run(self.main())

    def quit(self):
        """
        Must be implemented for QThread. Stops QThread and deletes it.
        """
        print("OpcuaServerHandle stopping...")
        super().quit()
        super().wait()
        self.deleteLater()
        print("OpcuaServerHandle stopped and deleted")

    @uamethod
    def func(parent, value):
        """
        Example function for opcua server
        """
        return value * 2
    
    def start(self):
        """
        Must be implemented for QThread. Starts QThread 
        and creates an opcua server object.
        """
        print("OpcuaServerHandle started")
        super().start()
        self.server = Server()
        self.server.set_security_policy([ua.SecurityPolicyType.NoSecurity])
        print("OpcuaServerHandle running...")

    async def main(self) -> None:
        """
        Main function for opcua server

        """
        _logger = logging.getLogger(__name__)
        # setup our server
        
        await self.server.init()
        endpoint = self.preferenceController.preferences.opcua.endpoint
        self.server.set_endpoint(endpoint)

        # set up our own namespace, not really necessary but should as spec
        uri = self.preferenceController.preferences.opcua.namespace
        idx = await self.server.register_namespace(uri)

        # populating our address space
        # server.nodes, contains links to very common nodes like objects and root
        myobj = await self.server.nodes.objects.add_object(idx, "MyObject")
        myvar = await myobj.add_variable(idx, "MyVariable", 6.7)
        # Set MyVariable to be writable by clients
        await myvar.set_writable()
        await self.server.nodes.objects.add_method(
            ua.NodeId("ServerMethod", idx),
            ua.QualifiedName("ServerMethod", idx),
            self.func,
            [ua.VariantType.Int64],
            [ua.VariantType.Int64],
        )
        _logger.info("Starting server!")
        _logger.info("Creating Agent variables")
        for field in vars(self.agent_vars).items():
            field = await self.server.nodes.objects.add_object(idx, str(field.__str__()))


        async with self.server:
            while True:
                await asyncio.sleep(1)
                new_val = await myvar.get_value() + 0.1
                _logger.info("Set value of %s to %.1f", myvar, new_val)
                await myvar.write_value(new_val)

class OpcuaClientHandle(QThread):

    def __init__(self, preferenceController: PreferenceController, parent: QObject | None = None) -> None:
        QThread.__init__(self,parent)
        self.preferenceController = preferenceController
        self.opcuaClient = None
        
    def run(self):
        asyncio.run(self.main())
    
    async def main(self):
        url = self.preferenceController.preferences.opcua.clientUrl
        namespace = self.preferenceController.preferences.opcua.namespace
        print(f"Connecting to {url} ...")
        async with Client(url=url) as client:
            # Find the namespace index
            nsidx = await client.get_namespace_index(namespace)
            print(f"Namespace Index for '{namespace}': {nsidx}")
    
            # Get the variable node for read / write
            var = await client.nodes.root.get_child(
                ["0:Objects", f"{nsidx}:MyObject", f"{nsidx}:MyVariable"]
            )
            value = await var.read_value()
            print(f"Value of MyVariable ({var}): {value}")
    
            new_value = value - 50
            print(f"Setting value of MyVariable to {new_value} ...")
            await var.write_value(new_value)
    
            # Calling a method
            res = await client.nodes.objects.call_method(f"{nsidx}:ServerMethod", 5)
            print(f"Calling ServerMethod returned {res}")

    def start(self):
        print("OpcuaClientHandle started")
        super().start()
        print("OpcuaClientHandle running...")

    def quit(self):
        print("OpcuaClientHandle stopping...")
        super().quit()
        super().wait()
        self.deleteLater()
        print("OpcuaClientHandle stopped and deleted")

class OpcuaService(QObject):
    """
    Class for handling opcua server and client. 
    will hold two QThreads for opcua server and client which wraps async functions.
    """
    def __init__(self, eventlogService : EventlogService, preferenceController : PreferenceController, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.eventlogService = eventlogService
        self.preferenceController = preferenceController
        self.opcuaServerHandle = OpcuaServerHandle(self.preferenceController)
        self.opcuaClientHandle = OpcuaClientHandle(self.preferenceController)
        
    
    @Slot()
    def startOpcuaService(self, ):
        self.opcuaServerHandle.start()
        # self.opcuaClientHandle.start()
        self.eventlogService.writeEvent("OpcuaService", "OpcuaService started")
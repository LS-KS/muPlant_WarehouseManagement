from typing import Optional
from PySide6.QtCore import QThread, QObject, Signal, Slot
import asyncio
import logging
from asyncua import Server, ua, Client
from asyncua.common.methods import uamethod
from src.controller.PreferenceController import PreferenceController
from src.service.EventlogService import EventlogService



class OpcuaServerHandle(QThread):

    def __init__(self, preferenceController: PreferenceController, parent = None, ) -> None:
        QThread.__init__(self,parent)
        self.preferenceController = preferenceController
        self.opcuaServer = None
    
    def run(self):
        asyncio.run(self.main())

    def quit(self):
        print("OpcuaServerHandle stopping...")
        super().quit()
        super().wait()
        self.deleteLater()
        print("OpcuaServerHandle stopped and deleted")

    @uamethod
    def func(parent, value):
        return value * 2
    
    def start(self):
        print("OpcuaServerHandle started")
        super().start()
        self.server = Server()
        print("OpcuaServerHandle running...")

    async def main(self) -> None:
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
        pass

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

    def __init__(self, eventlogService : EventlogService, preferenceController : PreferenceController, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.eventlogService = eventlogService
        self.preferenceController = preferenceController
        self.opcuaServerHandle = OpcuaServerHandle(self.preferenceController)
        self.opcuaClientHandle = OpcuaClientHandle(self.preferenceController)
        
    
    @Slot()
    def startOpcuaService(self, ):
        self.opcuaServerHandle.start()
        self.opcuaClientHandle.start()
        self.eventlogService.writeEvent("OpcuaService", "OpcuaService started")
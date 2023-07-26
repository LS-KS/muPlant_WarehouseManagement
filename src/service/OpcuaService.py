from asyncua import Client, Server, Server
from src.service.EventlogService import EventlogService
from src.controller.PreferenceController import PreferenceController

class SubHandler(object):
    
        """
        Client to subscribe to OPC UA Server
        """
    
        def datachange_notification(self, node, val, data):
            print("Python: New data change event", node, val)
    
        def event_notification(self, event):
            print("Python: New event", event)


class OpcuaService():

    def __init__(self, eventlogService: EventlogService, preferenceController: PreferenceController) -> None:
        self.eventlogService = eventlogService
        self.preferenceController = preferenceController
        self.client = self.setupOpcuaClient()
        self.server = self.setupOpcuaServer()
        self.eventlogService.writeEvent("OpcuaService", "OPC UA Service setup complete")
        try: 
            self.server.start()
            self.eventlogService.writeEvent("OpcuaService", "OPC UA Server started")
        finally:
            self.server.stop()
            self.eventlogService.writeEvent("OpcuaService", "OPC UA Server stopped")
        

    def setupOpcuaServer(self) -> Server:
        server = Server()
        server.set_endpoint("opc.tcp://127.0.0.1:4840/freeopcua/server/")
        server.set_server_name("FreeOpcUa Example Server")
        uri = "http://examples.freeopcua.github.io"
        idx = server.register_namespace(uri)
        objects = server.get_objects_node()
        myobj = objects.add_object(idx, "MyObject")
        myvar = myobj.add_variable(idx, "MyVariable", 6.7)
        myvar.set_writable()
        return server

    def setupOpcuaClient(self) -> Client:
        client = Client("opc.tcp://localhost:4840/freeopcua/server/")
        return client
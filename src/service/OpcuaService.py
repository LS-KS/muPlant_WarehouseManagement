from PySide6.QtCore import QThread, QObject, Signal, Slot
import asyncio
from asyncua import Server, ua
from asyncua.common.methods import uamethod
from src.controller.PreferenceController import PreferenceController
from src.controller.invController import invController
from src.controller.CommissionController import CommissionController
from src.controller.RfidController import RfidController
from src.model.DataModel import  Cup
from src.model.CommissionModel import CommissionData
from src.service.EventlogService import EventlogService
from src.service.AgentService import AgentService

class agent_vars:
    """
    Wrapper class for agentlib variables.
    Used in OpcuaServerHandle to create variables in the opcua server.
    """
    def __init__(self):
        self.agentAgentLockID = None # Agent ID that HAS rights to write
        self.agentAgentLockRequest = None # Agent ID that WANTS rights to write
        self.agentDone = None # Agent has to set this to True if he's done.
        self.agentFunctionID = None # ID of the function that the agent wants to execute
        self.agentFunctionReady = False # Agent has to set this to True if function can be executed
        self.agentKeepAlive = None # Agent counts this to zero. The server has to set this to 10
        self.agentResponseID = None # sth like 1= success, 2= error, ...
        self.agentResponseReady = False # Server sets this to True if response can be read
        self.agentStatus = 0 # 0= unknown, 1= automatic, 2= manual, initialization, 3 = error
        self.agentUnused = None # unused
        self.agentWorking = 0 # 0= idle, 1= working
        self.agentFuncParameter_1 = None # individual parameters for each function
        self.agentFuncParameter_2 = None # individual parameters for each function
        self.agentFuncParameter_3 = None # individual parameters for each function
        self.agentFuncParameter_4 = None # individual parameters for each function
        self.agentFuncParameter_5 = None # individual parameters for each function
        self.agentFuncParameter_6 = None # individual parameters for each function
        self.agentFuncParameter_7 = None # individual parameters for each function
        self.agentFuncParameter_8 = None # individual parameters for each function
        self.agentFuncParameter_9 = None # individual parameters for each function
        self.agentFuncParameter_10 = None # individual parameters for each function
        self.agentFuncParameter_11 = None # individual parameters for each function
        self.agentFuncParameter_12 = None # individual parameters for each function
        self.agentFuncParameter_13 = None # individual parameters for each function
        self.agentFuncParameter_14 = None # individual parameters for each function
        self.agentFuncParameter_15 = None # individual parameters for each function
        self.agentFuncParameter_16 = None # individual parameters for each function
        self.agentFuncParameter_17 = None # individual parameters for each function
        self.agentFuncParameter_18 = None # individual parameters for each function
        self.agentFuncParameter_19 = None # individual parameters for each function
        self.agentFuncParameter_20 = None # individual parameters for each function
        self.agentFuncParameter_21 = None # individual parameters for each function
        self.agentFuncParameter_22 = None # individual parameters for each function
        self.agentFuncParameter_23 = None # individual parameters for each function
        self.agentFuncParameter_24 = None # individual parameters for each function
        self.agentFuncParameter_25 = None # individual parameters for each function
        self.agentFuncParameter_26 = None # individual parameters for each function
        self.agentFuncParameter_27 = None # individual parameters for each function
        self.agentFuncParameter_28 = None # individual parameters for each function
        self.agentFuncParameter_29 = None # individual parameters for each function
        self.agentFuncParameter_30 = None # individual parameters for each function
        self.agentFuncParameter_31 = None # individual parameters for each function
        self.agentFuncParameter_32 = None # individual parameters for each function
        self.agentRespParameter_1 = None # individual parameters for each response
        self.agentRespParameter_2 = None # individual parameters for each response
        self.agentRespParameter_3 = None # individual parameters for each response
        self.agentRespParameter_4 = None # individual parameters for each response
        self.agentRespParameter_5 = None # individual parameters for each response
        self.agentRespParameter_6 = None # individual parameters for each response
        self.agentRespParameter_7 = None # individual parameters for each response
        self.agentRespParameter_8 = None # individual parameters for each response
        self.agentRespParameter_9 = None # individual parameters for each response
        self.agentRespParameter_10 = None # individual parameters for each response
        self.agentRespParameter_11 = None # individual parameters for each response
        self.agentRespParameter_12 = None # individual parameters for each response
        self.agentRespParameter_13 = None # individual parameters for each response
        self.agentRespParameter_14 = None # individual parameters for each response
        self.agentRespParameter_15 = None # individual parameters for each response
        self.agentRespParameter_16 = None # individual parameters for each response
        self.agentRespParameter_17 = None # individual parameters for each response
        self.agentRespParameter_18 = None # individual parameters for each response
        self.agentRespParameter_19 = None # individual parameters for each response
        self.agentRespParameter_20 = None # individual parameters for each response
        self.agentRespParameter_21 = None # individual parameters for each response
        self.agentRespParameter_22 = None # individual parameters for each response
        self.agentRespParameter_23 = None # individual parameters for each response
        self.agentRespParameter_24 = None # individual parameters for each response
        self.agentRespParameter_25 = None # individual parameters for each response
        self.agentRespParameter_26 = None # individual parameters for each response
        self.agentRespParameter_27 = None # individual parameters for each response
        self.agentRespParameter_28 = None # individual parameters for each response
        self.agentRespParameter_29 = None # individual parameters for each response
        self.agentRespParameter_30 = None # individual parameters for each response
        self.agentRespParameter_31 = None # individual parameters for each response
        self.agentRespParameter_32 = None # individual parameters for each response
class inventory_vars:
    """
    wrapper class for inventory variables.
    """
    def __init__(self):
        self.L1a: Cup = None
        self.L1b: Cup = None
        self.L2a: Cup = None
        self.L2b: Cup = None
        self.L3a: Cup = None
        self.L3b: Cup = None
        self.L4a: Cup = None
        self.L4b: Cup = None
        self.L5a: Cup = None
        self.L5b: Cup = None
        self.L6a: Cup = None
        self.L6b: Cup = None
        self.L7a: Cup = None
        self.L7b: Cup = None
        self.L8a: Cup = None
        self.L8b: Cup = None
        self.L9a: Cup = None
        self.L9b: Cup = None
        self.L10a: Cup = None
        self.L10b: Cup = None
        self.L11a: Cup = None
        self.L11b: Cup = None
        self.L12a: Cup = None
        self.L12b: Cup = None
        self.L13a: Cup = None
        self.L13b: Cup = None
        self.L14a: Cup = None
        self.L14b: Cup = None
        self.L15a: Cup = None
        self.L15b: Cup = None
        self.L16a: Cup = None
        self.L16b: Cup = None
        self.L17a: Cup = None
        self.L17b: Cup = None
        self.L18a: Cup = None
        self.L18b: Cup = None
class rfid_vars:
    ip_id:str
    name_id:str
    ip:str
    name:str
    iid:str
    dsfid:str
    timestamp:str
    last_valid_iid:str
    last_valid_dsfid:str
    last_valid_timestamp:str

    def __init__(self, ip:str, name:str):
        self.ip_id:str = ip
        self.name_id:str = name

class OpcuaServerHandle(QThread):
    agentVarsChanged = Signal(dict)
    inventoryVarsChanged = Signal(dict)
    commissionVarsChanged = Signal(dict)
    def __init__(self, preferenceController: PreferenceController, inventory_controller: invController,
                 commission_controller: CommissionController, eventlog_service : EventlogService,
                 agentservice: AgentService, opc_service, rfidcontroller: RfidController, parent = None, ) -> None:
        QThread.__init__(self, parent)
        self.preferenceController = preferenceController
        self.inventory_controller = inventory_controller
        self.commission_controller = commission_controller
        self.eventlog_service = eventlog_service
        self.opcuaServer: None | Server = None
        self.agent_vars = agent_vars()
        self.agent_nodes: list[int] = []
        self.inventory_vars = inventory_vars()
        self.inventory_nodes: list[int] = []
        self.commission_vars: list[CommissionData] = []
        self.commission_nodes: list[int] = []
        self.rfidcontroller: RfidController = rfidcontroller
        self.rfidNode: int = 0
        self.rfid_nodes: list[rfid_vars] = []
        self.opc_service: OpcuaService = opc_service
        self.idx = None
    def __del__(self):
        """
        Deconstructor for OpcuaServerHandle. Stops opcua server.
        """
        if self.opcuaServer is not None:
            self.opcuaServer.stop()
        print("OpcuaServerHandle deleted")
    def _update_inventory_values(self):
        """
        Updates inventory_vars with current inventory by referencing the corresponding cup object.
        """
        try:
            for i in range(3):
                for j in range(6):
                    pallet = self.inventory_controller.inventory.getStoragePallet(row=i, col=j)
                    var = f"L{(j + 1) + i * 6}"
                    if pallet is not None:
                        self.inventory_vars.__setattr__(f"{var}a", pallet.slotA)
                        self.inventory_vars.__setattr__(f"{var}b", pallet.slotB)
                    else:
                        self.inventory_vars.__setattr__(f"{var}a", None)
                        self.inventory_vars.__setattr__(f"{var}b", None)
        except Exception as e:
            self.eventlog_service.writeEvent("OpcuaService", f"Error while updating inventory values: {e}")
    def _load_commission_values_from_model(self) -> list[CommissionData]:
        """
        Load CommissionData from ComissionController's Data.
        """
        return  self.commission_controller.get_commissionData()
    async def _update_inventory_vars(self):
        """
        Write new invetory var values to opc server variables in objects of node…
        """
        try:
            for slot, node in zip(vars(self.inventory_vars).items(), self.inventory_nodes):
                id = node[1]
                prod = node[2]
                node = self.opcuaServer.get_node(node[0])
                if slot[1] is None:
                    id_val = 0
                    prod_val = 0
                else:
                    id_val = slot[1].id
                    prod_val = slot[1].product.id
                await id.write_value(id_val)
                await prod.write_value(prod_val)
        except Exception as e:
            self.eventlog_service.writeEvent("OpcuaService", f"Error while updating inventory vars: {e}")
    async def _create_agent_nodes(self, idx):
        """
        Creates nodes for agent variables.
        basically creates a node for each variable in agent_vars.
        individually set writeable for clients depending on dict.
        TODO: function variables could be in one object
        TODO: response variables could be in one object
        :param idx: namespace index
        :type idx: int
        """
        writable = {
            'agentAgentLockID': False,
            'agentAgentLockRequest': True,
            'agentDone': True,
            'agentFunctionID': True,
            'agentFunctionReady': True,
            'agentKeepAlive': True,
            'agentResponseID': False,
            'agentResponseReady': False,
            'agentStatus': False,
            'agentUnused': False,
            'agentWorking': False,
            'agentFuncParameter_1': True,
            'agentFuncParameter_2': True,
            'agentFuncParameter_3': True,
            'agentFuncParameter_4': True,
            'agentFuncParameter_5': True,
            'agentFuncParameter_6': True,
            'agentFuncParameter_7': True,
            'agentFuncParameter_8': True,
            'agentFuncParameter_9': True,
            'agentFuncParameter_10': True,
            'agentFuncParameter_11': True,
            'agentFuncParameter_12': True,
            'agentFuncParameter_13': True,
            'agentFuncParameter_14': True,
            'agentFuncParameter_15': True,
            'agentFuncParameter_16': True,
            'agentFuncParameter_17': True,
            'agentFuncParameter_18': True,
            'agentFuncParameter_19': True,
            'agentFuncParameter_20': True,
            'agentFuncParameter_21': True,
            'agentFuncParameter_22': True,
            'agentFuncParameter_23': True,
            'agentFuncParameter_24': True,
            'agentFuncParameter_25': True,
            'agentFuncParameter_26': True,
            'agentFuncParameter_27': True,
            'agentFuncParameter_28': True,
            'agentFuncParameter_29': True,
            'agentFuncParameter_30': True,
            'agentFuncParameter_31': True,
            'agentFuncParameter_32': True,
            'agentRespParameter_1': False,
            'agentRespParameter_2': False,
            'agentRespParameter_3': False,
            'agentRespParameter_4': False,
            'agentRespParameter_5': False,
            'agentRespParameter_6': False,
            'agentRespParameter_7': False,
            'agentRespParameter_8': False,
            'agentRespParameter_9': False,
            'agentRespParameter_10': False,
            'agentRespParameter_11': False,
            'agentRespParameter_12': False,
            'agentRespParameter_13': False,
            'agentRespParameter_14': False,
            'agentRespParameter_15': False,
            'agentRespParameter_16': False,
            'agentRespParameter_17': False,
            'agentRespParameter_18': False,
            'agentRespParameter_19': False,
            'agentRespParameter_20': False,
            'agentRespParameter_21': False,
            'agentRespParameter_22': False,
            'agentRespParameter_23': False,
            'agentRespParameter_24': False,
            'agentRespParameter_25': False,
            'agentRespParameter_26': False,
            'agentRespParameter_27': False,
            'agentRespParameter_28': False,
            'agentRespParameter_29': False,
            'agentRespParameter_30': False,
            'agentRespParameter_31': False,
            'agentRespParameter_32': False,
        }
        self.eventlog_service.writeEvent("OpcuaService", "Load and create agent variables")
        try:
            for field, value in vars(self.agent_vars).items():
                node = await self.opcuaServer.nodes.objects.add_object(idx, str(field.__str__()))
                var = await node.add_variable(nodeid= idx, bname= (field.__str__()), val= int(0),)
                if writable[str(field)]:
                    await var.set_writable()
                self.agent_nodes.append([node, var])
        except Exception as e:
            self.eventlog_service.writeEvent("OpcuaService", f"Error while creating agent nodes: {e}")
    async def _create_inventory_nodes(self, idx):
        """
        Creates an ua object to hold all inventory objects.
        Then creates another object for each storageElement slot in inventory.
        Writes id and product id to variables for each slot.
        In principle these variables are read only despite it's
        disputable if the operator shall be able to correct wrong storage info via remote.
        :param idx: namespace index
        :type idx: int
        """
        self._update_inventory_values()
        node = await self.opcuaServer.nodes.objects.add_object(idx, 'Storage')
        for field, value in vars(self.inventory_vars).items():
            subnode = await node.add_object(idx, str(field.__str__()))
            id = await subnode.add_variable(idx, str(field) + "_id", 0 if value is None else value.id)
            prod = await subnode.add_variable(idx, str(field) + "_prod",
                                                 0 if value is None else value.product.id)
            self.inventory_nodes.append([subnode, id, prod])
    async def _create_commission_nodes(self, idx):
        """
        First create an ua object to hold all commission objects.
        Then create another object for each commission.
        Then create a variable for each commission variable.
        Node ids are appended to self.commission_nodes.
        Commission variables are appended to self.commission_vars.
        In Principle these variables are read only. New Commissions can be created via Manual Control plugin
        or via agent system.
        :param idx: namespace index
        :type idx: int
        """
        node = await self.opcuaServer.nodes.objects.add_object(idx, "Commissions")
        for commission in self.commission_vars:
            subnode = await node.add_object(idx, f"Commission {str(commission.id)}")
            source = await subnode.add_variable(idx, "source", commission.source.value)
            target = await subnode.add_variable(idx, "target", commission.target.value)
            object = await subnode.add_variable(idx, "object", commission.object)
            cup = await subnode.add_variable(idx, "cup", commission.cup)
            pallet = await subnode.add_variable(idx, "pallet", commission.pallet)
            state = await subnode.add_variable(idx, "state", commission.state.value)
            self.commission_nodes.append([subnode, source, target, object, cup, pallet, state])

    async def _create_rfid_nodes(self):
        node = await self.opcuaServer.nodes.objects.add_object(self.idx, "RFID Nodes")
        for rfidnode in self.rfidcontroller.rfid_viewmodel.rfidData:
            subnode = await node.add_object(self.idx, rfidnode.name)
            rfidvar = rfid_vars(rfidnode.ipAddr, rfidnode.name)
            rfidvar.ip = await subnode.add_variable(self.idx, "ip", str(rfidnode.ipAddr))
            rfidvar.iid = await subnode.add_variable(self.idx, "iid", str(rfidnode.iid))
            rfidvar.dsfid = await subnode.add_variable(self.idx, "dsfid", str(rfidnode.dsfid))
            rfidvar.timestamp = await subnode.add_variable(self.idx, "timestamp", str(rfidnode.timestamp))
            rfidvar.last_valid_iid = await subnode.add_variable(self.idx, "last_valid_iid", str(rfidnode.last_valid_iid))
            rfidvar.last_valid_dsfid = await subnode.add_variable(self.idx, "last_valid_dsfid", str(rfidnode.last_valid_dsfid))
            rfidvar.last_valid_timestamp = await subnode.add_variable(self.idx, "last_valid_timestamp", str(rfidnode.last_valid_timestamp))
            self.rfid_nodes.append(rfidvar)


    @Slot(str, str, str, str, str, str, str)
    async def _update_rfid_vars(self,ip: str, timestamp: str, iid: str, dsfid: str, last_valid_iid: str, last_valid_dsfid: str, last_valid_timestamp: str):
        for node in self.rfid_nodes:
            if node.ip_id == ip:
                self.opcuaServer.get_node(node.timestamp).write_value(str(timestamp))
                self.opcuaServer.get_node(node.iid).write_value(str(iid))
                self.opcuaServer.get_node(node.dsfid).write_value(str(dsfid))
                self.opcuaServer.get_node(node.last_valid_iid).write_value(str(last_valid_iid))
                self.opcuaServer.get_node(node.last_valid_dsfid).write_value(str(last_valid_dsfid))
                self.opcuaServer.get_node(node.last_valid_timestamp).write_value(str(last_valid_timestamp))
        self.eventlog_service("OpcuaService", "Updated RFID Variables")

    async def _update_agent_vars(self):
        """
        Sets agent variables to values in agent_vars back to default values.
        Sets KeepAlive to 10.
        TODO: Check consistency if functions are ordered.
        """
        try:
            for i, (key, value) in enumerate(vars(self.agent_vars).items()):
                node = self.agent_nodes[i][0]
                var = self.agent_nodes[i][1]
                node = self.opcuaServer.get_node(node)
                if i == 4:
                    self.agent_vars.agentKeepAlive = 10
                    await var.write_value(self.agent_vars.agentKeepAlive)
                else:
                    if value is None or value == False:
                        await var.write_value(0)
                    elif value == True:
                        await var.write_value(1)
                    else:
                        await var.write_value(value)
        except Exception as e:
            self.eventlog_service.writeEvent("OpcuaService", f"Error while updating agent vars: {e}")
    def run(self):
        """
        Must be implemented for QThread. Wraps asyncio function in sync function.
        """
        asyncio.run(self.main())
    async def quit(self):
        """
        Must be implemented for QThread. Stops QThread and deletes it.
        """
        print("OpcuaServerHandle stopping...")
        await self.opcuaServer.stop()
        self.opcuaServer = None
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
        self.opcuaServer = Server()
        self.opcuaServer.set_security_policy([ua.SecurityPolicyType.NoSecurity])
        self.opc_service.isRunning = True
        self.opc_service.check_online_status()
        print("OpcuaServerHandle running...")
    async def main(self) -> None:
        """
        Main function for opcua server
        """
        try:
            self.eventlog_service.writeEvent("OpcuaService", "OpcuaServerHandle started")
            self.idx = await self.setup_server()
            self.eventlog_service.writeEvent("OpcuaService", "Server started")
            myobj = await self.opcuaServer.nodes.objects.add_object(self.idx, "MyObject")
            myvar = await myobj.add_variable(self.idx, "MyVariable", 6.7)
            await myvar.set_writable()
            await self.opcuaServer.nodes.objects.add_method(
                ua.NodeId("ServerMethod", self.idx),
                ua.QualifiedName("ServerMethod", self.idx),
                self.func,
                [ua.VariantType.Int64],
                [ua.VariantType.Int64],
            )
            await self._create_rfid_nodes()
            self.eventlog_service.writeEvent("OpcuaService", "Load and create RFID variables")
            await self._create_agent_nodes(self.idx)
            self.eventlog_service.writeEvent("OpcuaService", "Load and create inventory variables")
            await self._create_inventory_nodes(self.idx)
            self.eventlog_service.writeEvent("OpcuaService", "Load and create commission variables")
            self.commission_vars= self._load_commission_values_from_model()
            await self._create_commission_nodes(self.idx)
            # loop
            async with self.opcuaServer:
                while True:
                    await asyncio.sleep(1)
                    # Perform inventory update
                    self._update_inventory_values()
                    await self._update_inventory_vars()
                    # Perform agent update
                    await self._update_agent_vars()
                    # example var
                    new_val = await myvar.get_value() + 0.1
                    await myvar.write_value(new_val)
        except Exception as e:
            self.eventlog_service.writeEvent("OpcuaService", f"Error in Mainloop: {e}")
            self.opc_service.isRunning = False   
    async def setup_server(self):
        """
        setup server object and namespace.
        returns namespace index.
        rtype: int
        """
        await self.opcuaServer.init()
        endpoint = self.preferenceController.preferences.opcua.endpoint
        self.opcuaServer.set_endpoint(endpoint)
        uri = self.preferenceController.preferences.opcua.namespace
        idx = await self.opcuaServer.register_namespace(uri)
        return idx
    def clear_agent(self):
        """
        Resets all agent variables to default values.
        """
        self.agent_vars = agent_vars()
        self.agent_vars.agentKeepAlive = 10
class OpcuaService(QObject):
    """
    Class for handling opcua server.
    will hold a QThreads for opcua server which wraps async functions.
    """
    online = Signal(bool)
    def __init__(self, eventlogService : EventlogService, preferenceController : PreferenceController,
                 inventory_controller: invController, commission_controller: CommissionController,
                 agentservice: AgentService, rfidcontroller: RfidController, parent: QObject | None = None) -> None:
        super().__init__(parent)
        self.eventlogService = eventlogService
        self.preferenceController = preferenceController
        self.inventory_controller = inventory_controller
        self.commission_controller = commission_controller
        self.agentservice = agentservice
        self.rfid_controller = rfidcontroller
        self.opcuaServerHandle = None
        self.isRunning: bool = False

    @Slot()
    def startOpcuaService(self):
        self.opcuaServerHandle = OpcuaServerHandle(
            preferenceController= self.preferenceController,
            inventory_controller= self.inventory_controller,
            commission_controller= self.commission_controller,
            eventlog_service= self.eventlogService,
            agentservice= self.agentservice,
            rfidcontroller = self.rfid_controller,
            opc_service= self
        )
        self.eventlogService.writeEvent("OpcuaService", "OpcuaService started")
        self.online.emit(True)
        self.opcuaServerHandle.start()
        
        
    @Slot()
    def stopOpcuaService(self):
        asyncio.run(self.opcuaServerHandle.quit())

    @Slot()
    def check_online_status(self):
        print("check_online emitted")
        self.online.emit(self.isRunning)

    def handle_rfid_update(self, ipAddr, timestamp, iid, dsfid, last_valid_timestamp, last_valid_iid, last_valid_dsfid):
        asyncio.run(self.opcuaServerHandle._update_rfid_vars(ipAddr, timestamp, iid, dsfid, last_valid_timestamp, last_valid_iid, last_valid_dsfid))
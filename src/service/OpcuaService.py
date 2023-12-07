from PySide6.QtCore import QThread, QObject, Signal, Slot, QEventLoop,QCoreApplication
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
import time

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
    event = Signal(str, str)

    agent_function_ready = Signal(int)
    agent_response_ready = Signal(int)
    agent_function_id = Signal(int)
    agent_stationlockrequest = Signal(int)
    agent_funcParam_1 = Signal(str)
    agent_funcParam_2 = Signal(str)
    agent_funcParam_3 = Signal(str)
    agent_funcParam_4 = Signal(str)
    agent_funcParam_5 = Signal(str)
    sig_commission = Signal(bool, bool, bool, bool, bool, bool, int, int )
    prepared_commission = Signal(bool)

    def __init__(self, preferenceController: PreferenceController, inventory_controller: invController,
                 commission_controller: CommissionController, 
                 agentservice: AgentService, opc_service, rfidcontroller: RfidController, parent = None, ) -> None:
        QThread.__init__(self, parent)
        self.preferenceController = preferenceController
        self.inventory_controller = inventory_controller
        self.commission_controller = commission_controller
        self.opcuaServer: None | Server = None
        self.agent_vars: agent_vars = agent_vars()
        self.agent_nodes: list[int] = []
        self.inventory_vars = inventory_vars()
        self.inventory_nodes: list[int] = []
        self.commission_vars: list[CommissionData] = []
        self.commission_nodes: list[int] = []
        self.rfidcontroller: RfidController = rfidcontroller
        self.rfidNode: int = 0
        self.rfid_nodes: list[rfid_vars] = []
        self.opc_service: OpcuaService = opc_service
        self.running = False
        self.idx = None
        self.agentworker = agentlib_worker()
        self.agent_function_id.connect(self.agentworker.handle_function_id)
        self.agent_function_ready.connect(self.agentworker.handle_function_ready)
        self.agent_response_ready.connect(self.agentworker.handle_response_ready)
        self.agent_stationlockrequest.connect(self.agentworker.handle_lock_request)
        self.agent_funcParam_1.connect(self.agentworker.handle_function_param_1)
        self.agent_funcParam_2.connect(self.agentworker.handle_function_param_2)
        self.agent_funcParam_3.connect(self.agentworker.handle_function_param_3)
        self.agent_funcParam_4.connect(self.agentworker.handle_function_param_4)
        self.agent_funcParam_5.connect(self.agentworker.handle_function_param_5)
        self.prepared_commission.connect(self.agentworker.handle_prepared_commission)
        self.agentworker.sig_cleanupfunctionids.connect(self.handle_agent_cleanupfunctionids)
        self.agentworker.sig_cleanupresponseids.connect(self.handle_agent_cleanupresponseids)
        self.agentworker.sig_commission.connect(self.handle_commission)
        self.agentworker.sig_done.connect(self.handle_agent_done)
        self.agentworker.sig_event.connect(self.event.emit)
        self.agentworker.sig_functionready.connect(self.handle_agent_functionready)
        self.agentworker.sig_keepalive.connect(self.handle_agent_keepalive)
        self.agentworker.sig_lockrequest.connect(self.handle_agent_lockrequest)
        self.agentworker.sig_responseid.connect(self.handle_agent_responseid)
        self.agentworker.sig_responseready.connect(self.handle_agent_responseready)
        self.agentworker.sig_response_1.connect(self.handle_sig_response_1)
        self.agentworker.sig_response_2.connect(self.handle_sig_response_2)
        self.agentworker.sig_started.connect(self.handle_agent_started)
        self.agentworker.sig_stationlockid.connect(self.handle_agent_stationlockid)
        self.agentworker.sig_stationlockrequest.connect(self.handle_agent_stationlockrequest)
        self.agentworker.sig_stopped.connect(self.handle_agent_stopped)
        self.agentworker.sig_status.connect(self.handle_agent_status)
        self.agentworker.sig_unused.connect(self.handle_agent_unused)
        self.agentworker.sig_working.connect(self.handle_agent_working)

    @Slot(bool)
    def handle_prepared_commission(self, result):
        self.prepared_commission.emit(result)

    @Slot(bool, bool, bool, bool, bool, bool, int, int )
    def handle_commission(self, prepare:bool, execute: bool, to_storage: bool, to_robot: bool, cup: bool, product: bool, cup_id: int, product_id: int):
        self.sig_commission.emit(prepare, execute, to_storage, to_robot, cup, product, cup_id, product_id)

    @Slot()
    def handle_agent_cleanupfunctionids(self):
        for i, (key, value) in enumerate(vars(self.agent_vars).items()):
            if "agentFuncParameter" in key:
                node = self.agent_nodes[i][0]
                node = self.opcuaServer.get_node(node)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(0))
                self.agent_vars.__setattr__(key, 0)
            elif "agentFunctionID" == key:
                node = self.agent_nodes[i][0]
                node = self.opcuaServer.get_node(node)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(0))
                self.agent_vars.__setattr__(key, 0)
   
    @Slot()
    def handle_agent_cleanupresponseids(self):
        for i, (key, value) in enumerate(vars(self.agent_vars).items()):
            if "agentRespParameter" in key:
                value = 0 if value is None else int(value)
                self.agent_vars.__setattr__(key, None)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(int(value)))

    @Slot(int)
    def handle_agent_done(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentDone" in key:
                self.event.emit("OPCHandle: ", f"done: {value}")
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))
    
    @Slot(str)
    def handle_sig_response_1(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentRespParameter_1" in key:
                self.event.emit("OPCHandle: ", f"done: {value}")
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))
    
    @Slot(str)
    def handle_sig_response_2(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentRespParameter_2" in key:
                self.event.emit("OPCHandle: ", f"done: {value}")
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(ua.LocalizedText(value)))

    @Slot(int)
    def handle_agent_functionready(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentFunctionReady" in key:
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(int)
    def handle_agent_keepalive(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentKeepAlive" in key:
                self.agent_vars.__setattr__(key, int)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(int)
    def handle_agent_lockrequest(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentAgentLockRequest" in key:
                self.agent_vars.agentAgentLockRequest = value
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(int)
    def handle_agent_responseid(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentResponseID" in key:
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(int)
    def handle_agent_responseready(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentResponseReady" in key:
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(bool)
    def handle_agent_started(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentWorking" in key:
                self.agent_vars.__setattr__(key, int(value))
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(int)
    def handle_agent_stationlockid(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentAgentLockID" in key:
                self.agent_vars.__setattr__(key, int(value))
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(int)
    def handle_agent_stationlockrequest(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentAgentLockRequest" in key:
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(bool)
    def handle_agent_stopped(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentWorking" in key:
                self.agent_vars.__setattr__(key, int(value))
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(int)
    def handle_agent_status(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentStatus" in key:
                self.agent_vars.__setattr__(key, value)
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(value))

    @Slot(bool)
    def handle_agent_unused(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentUnused" in key:
                self.agent_vars.__setattr__(key, int(value))
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(int(value)))

    @Slot(bool)
    def handle_agent_working(self, value):
        for i, (key, val) in enumerate(vars(self.agent_vars).items()):
            if "agentWorking" in key:
                self.agent_vars.__setattr__(key, int(value))
                var = self.agent_nodes[i][1]
                var = self.opcuaServer.get_node(var)
                asyncio.run(var.write_value(int(value)))

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
            self.event.emit("OpcuaService", f"Error while updating inventory values: {e}")

    def _load_commission_values_from_model(self) -> list[CommissionData]:
        """
        Load CommissionData from ComissionController's Data.
        """
        return  self.commission_controller.get_commissionData()
    
    async def _listen_agentvars(self):
        for i, (key, value) in enumerate(vars(self.agent_vars).items()):
            node = self.agent_nodes[i][0]
            var = self.agent_nodes[i][1]
            #self.event.emit("agentlistener","listen agent node: "f"{key}: {node}, {value}, {var}")
            if key == "agentAgentLockRequest":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_stationlockrequest.emit(opc_val)
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentAgentResponseID":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_response_ready.emit(opc_val)
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentFunctionReady":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_function_ready.emit(opc_val)
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentFunctionID":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_function_id.emit(opc_val)
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentFuncParameter_1":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_funcParam_1.emit(str(opc_val))
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentFuncParameter_2":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_funcParam_2.emit(str(opc_val))
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentFuncParameter_3":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_funcParam_3.emit(str(opc_val))
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentFuncParameter_4":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_funcParam_4.emit(str(opc_val))
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")
            elif key == "agentFuncParameter_5":
                opc_val = await self.opcuaServer.get_node(var).get_value()
                if value != opc_val:
                    setattr(self.agent_vars, key, opc_val)
                    self.agent_funcParam_5.emit(str(opc_val))
                    self.event.emit("agentlistener",f"{key} has changed from {value} to {getattr(self.agent_vars, key)}!!")

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
            self.event.emit("OpcuaService", f"Error while updating inventory vars: {e}")

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
        self.event.emit("OpcuaService", "Load and create agent variables")
        try:
            for field, value in vars(self.agent_vars).items():
                node = await self.opcuaServer.nodes.objects.add_object(idx, str(field.__str__()))
                var = await node.add_variable(nodeid= idx, bname= (field.__str__()), val= int(0),)
                if writable[str(field)]:
                    await var.set_writable()
                self.agent_nodes.append([node, var])
        except Exception as e:
            self.event.emit("OpcuaService", f"Error while creating agent nodes: {e}")

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
        self.event.emit("OpcuaService", "Updated RFID Variables")

    def run(self):
        """
        Must be implemented for QThread. Wraps asyncio function in sync function.
        """
        #asyncio.run(self.main())
        self.loop = asyncio.new_event_loop()
        asyncio.set_event_loop(self.loop)
        self.running = True
        try:
            self.loop.run_until_complete(self.main())
        except Exception as e:
            self.event.emit("OpcuaService", f"Error in Mainloop: {e}")
            self.opc_service.isRunning = False
        finally:
            self.loop.close()

    def quit(self):
        """
        Must be implemented for QThread. Stops QThread and deletes it.
        """
        print("OpcuaServerHandle stopping...")
        self.running = False
        asyncio.run(self.loop.stop())
        asyncio.run(self.loop.close())
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
        self.event.emit("OpcuaService", "OpcuaServerHandle starting...")
        super().start()
        self.opcuaServer = Server()
        self.opcuaServer.set_security_policy([ua.SecurityPolicyType.NoSecurity])
        self.opc_service.isRunning = True
        self.opc_service.check_online_status()
        self.event.emit("OpcuaService", "OpcuaServerHandle running")

    async def main(self) -> None:
        """
        Main function for opcua server
        """
        try:
            self.event.emit("OpcuaService", "OpcuaServerHandle started")
            self.idx = await self.setup_server()
            self.event.emit("OpcuaService", "Server setup completed")
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
            self.event.emit("OpcuaService", "Load and create agent variables")
            await self._create_agent_nodes(self.idx)
            self.event.emit("OpcuaService", "Load and create inventory variables")
            await self._create_inventory_nodes(self.idx)
            self.event.emit("OpcuaService", "Load and create commission variables")
            self.commission_vars= self._load_commission_values_from_model()
            await self._create_commission_nodes(self.idx)
            # loop
            async with self.opcuaServer:
                while self.running:
                    await asyncio.sleep(0.5)
                    # Perform inventory update
                    self._update_inventory_values()
                    #self.event.emit("OpcuaService", "Mainloop: updated inventory")
                    await self._update_inventory_vars()
                    #self.event.emit("OpcuaService", "Mainloop: updated inventory vars")
                    # listen to agent variables
                    await self._listen_agentvars()
                    #self.event.emit("OpcuaService", "Mainloop: listened to agentvars")
                    # example var
                    new_val = await myvar.get_value() + 0.1
                    await myvar.write_value(new_val)
        except Exception as e:
            self.event.emit("OpcuaService", f"Error in Mainloop: {e}")
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
    event = Signal(str, str)

    def __init__(self, preferenceController : PreferenceController,
                 inventory_controller: invController, commission_controller: CommissionController,
                 agentservice: AgentService, rfidcontroller: RfidController, parent: QObject | None = None) -> None:
        super().__init__(parent)
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
            agentservice= self.agentservice,
            rfidcontroller = self.rfid_controller,
            opc_service= self
        )
        self.opcuaServerHandle.event.connect(self.event.emit)
        self.commission_controller.prepared_commission.connect(self.opcuaServerHandle.handle_prepared_commission)
        self.opcuaServerHandle.sig_commission.connect(self.commission_controller.handle_opcua_commission)
        self.event.emit("OpcuaService", "OpcuaService started")
        self.online.emit(True)
        self.opcuaServerHandle.start()
        
        
    @Slot()
    def stopOpcuaService(self):
        try:
            asyncio.run(self.opcuaServerHandle.quit())
        except Exception as e:
            #TODO: This is dirty... but no clue how to do it right
            pass
        self.online.emit(False)
        self.event.emit("OpcuaService", "OpcuaService stopped")

    @Slot()
    def check_online_status(self):
        print("check_online emitted")
        self.online.emit(self.isRunning)

    def handle_rfid_update(self, ipAddr, timestamp, iid, dsfid, last_valid_timestamp, last_valid_iid, last_valid_dsfid):
        asyncio.run(self.opcuaServerHandle._update_rfid_vars(ipAddr, timestamp, iid, dsfid, last_valid_timestamp, last_valid_iid, last_valid_dsfid))

class agentlib_worker(QThread):
    """ 
    Re-Implementation of Lars Kistners Agentlib. 
    Basically a copy with modifications of agentlibs AgentServerWorkerBase class.
    To make this threadsafe, communication with opcuaservice need to be implemented using signals and slots. 
    """

    #TODO: handler for stationlockid, stationlockrequest, function_ready, response_ready
    sig_started = Signal(bool)
    sig_stopped = Signal(bool)
    sig_status = Signal(int)
    sig_keepalive = Signal(int)
    sig_working = Signal(bool)
    sig_unused = Signal(bool)
    sig_lockrequest = Signal(int)
    sig_functionready = Signal(int)
    sig_responseready = Signal(int)
    sig_responseid = Signal(int)
    sig_done = Signal(int)
    sig_cleanupfunctionids = Signal()
    sig_cleanupresponseids = Signal()
    sig_event = Signal(str, str)
    sig_stationlockid = Signal(int)
    sig_stationlockrequest = Signal(int)
    sig_response_1 = Signal(str)
    sig_response_2 = Signal(str)
    sig_comission = Signal()
    sig_commission = Signal(bool, bool, bool, bool, bool, bool, int, int ) #(prepare, execute, to_storage, to_robot, cup, product, cup_id, product_id )

    def __init__(self, parent = None):
        super().__init__(parent)
        self.last_request :float = 0
        self.longest_request_time:float = 10
        self.wait_time_short: float= 1/800
        self.running: bool = True
        self.status: int = 0
        self.working: int = 0
        self.function_ready:int = 0
        self.response_ready:int = 0
        self.function_id:int = 0
        self.done: int = 0
        self.stationlockid:int = 0
        self.stationlockrequest:int = 0
        self.function_param_1: str = ""
        self.function_param_2: str = ""
        self.function_param_3: str = ""
        self.function_param_4: str = ""
        self.function_param_5: str = ""
        self.response_param_1: str = ""
        self.response_param_2: str = ""

    
    @Slot(bool)
    def handle_prepared_commission(self, result):
        self.fetch_function_result(result)

    @Slot(str) 
    def handle_function_param_1(self, param): 
        self.function_param_1 = param
        self.sig_event.emit("agentworker:", f"updated function parmeter 1: {self.function_param_1}, submitted:{param}")
    
    @Slot(str)
    def handle_function_param_2(self, param): 
        self.function_param_2 = param
        self.sig_event.emit("agentworker:", f"updated function parmeter 2: {self.function_param_2}, submitted:{param}")

    @Slot(str)
    def handle_function_param_3(self, param): 
        self.function_param_3 = param
        self.sig_event.emit("agentworker:", f"updated function parmeter 3: {self.function_param_3}, submitted:{param}")

    @Slot(str)
    def handle_function_param_4(self, param): 
        self.function_param_4 = param
        self.sig_event.emit("agentworker:", f"updated function parmeter 4: {self.function_param_4}, submitted:{param}")

    @Slot(str)
    def handle_function_param_5(self, param): 
        self.function_param_5 = param
        self.sig_event.emit("agentworker:", f"updated function parmeter 5: {self.function_param_5}, submitted:{param}")

    @Slot(bool)
    def handle_running(self, running): 
        self.running = running

    @Slot(int)
    def handle_function_ready(self, function_ready):
        self.function_ready = function_ready
        self.handle_requests()

    @Slot(int)
    def handle_response_ready(self, response_ready):
        self.response_ready = response_ready
        self.handle_requests()

    @Slot(int)
    def handle_function_id(self, function_id):
        self.function_id = function_id
        self.handle_requests()
    
    @Slot(int)
    def handle_lock_request(self, lock_request):
        self.stationlockrequest = lock_request
        self.handle_requests()

    @Slot(int)
    def handle_lock_id(self, lock_id):
        self.stationlockid = lock_id
        self.handle_requests()

    def start(self): super().start()

    def set_status(self):
        """set status related variables to there default values."""
        self.sig_status.emit(self.status)
        self.sig_keepalive.emit(10)
        self.sig_working.emit(self.working)
        self.sig_unused.emit(42)
        self.sig_lockrequest.emit(0)
        
    def reset_function_status(self):
        """cleanup functions status variables."""
        self.sig_functionready.emit(0)
        self.sig_responseready.emit(0)
        self.sig_done.emit(0)

    def reset_functioncall(self):
        """cleanup function call variables"""
        self.sig_cleanupfunctionids.emit()

    def reset_response(self):
        """cleanup response variables"""
        self.sig_cleanupresponseids.emit()

    def copy_function_to_response(self, parameters):
        #TODO: Implement
        """copy function variables to response variables (debug only)"""
        self.reset_functioncall()
        self.mb_write(MMAP_ResponseID, parameters)

    def function_handler(self, function):
        """
        Begins a function handling. 
        From muPlant operator two types of functons can be ordered: 
        
        - a transport from robot to storage
        - a transport from storage to robot. 
        further a specific cup or a product canbe ordered. 

        The main problem is, that an order can either be prepared or executed. 
        So the original function ist cut in two. 
        """
        self.reset_response()
        if function == 2:
            # decode function parameters 
            security = self.function_param_1 # to be ignored
            #cup = self.function_param_4 == 0b00000001
            #product = self.function_param_4 == 0b00000010
            cup = int(self.function_param_4) == 1
            product = int(self.function_param_4) == 2
            cup_id = int(self.function_param_5) if cup else None
            product_id = int(self.function_param_5) if product else None 
            execute = int(self.function_param_2) == 2
            prepare = int(self.function_param_2) == 1
            to_storage = int(self.function_param_3) == 1
            to_robot = int(self.function_param_3) == 2
            # cases
            self.sig_commission.emit(prepare, execute, to_storage, to_robot, cup, product, cup_id, product_id )
        elif function == 3:
            pass
        else:
            raise NotImplementedError("You need to implemented this function on your own")

    @Slot(bool)
    def fetch_function_result(self, result):
        # write rsponse to opc ua and clean up
        self.sig_event.emit("agentworker", f"fetch_function_result: {result}")
        self.sig_response_1.emit(int(result))
        self.function_id = 0
        self.reset_functioncall()
        self.done = 1
        self.stationlockrequest = 0
        self.stationlockid = 0
        self.sig_stationlockid.emit(0)
        self.sig_stationlockrequest.emit(0)
        self.sig_done.emit(1)
        self.handle_requests()


    def handle_requests(self):
        """check for request and if any forwards them to
        `function_handler()`, read the log comments bellow and see
        bachelor thesis of Lars Kistner to understand agent system
        """ 

        if self.stationlockid == 0 and self.stationlockrequest == 0:
            self.sig_event.emit("AgentLib:","No work todo! Set status")
            self.set_status()
            self.sleep(self.wait_time_short)

        elif self.stationlockid == 0 and self.stationlockrequest != 0:
            self.sig_event.emit("Agentlib: ","Requested Lock granted")
            self.stationlockid = self.stationlockrequest
            self.sig_stationlockid.emit(self.stationlockrequest)
            self.done = 0
            self.sig_done.emit(0)
            self.last_request = time.time()

        elif self.function_id > 0 and self.function_ready == 0:
            self.sig_event.emit("Agentlib:", "got function ID but function not ready!")

        elif self.function_ready == 1:
            self.sig_event.emit("Agentlib:","Call function {}".format(str(self.function_id)))
            self.sig_done.emit(0)
            try:
                self.function_handler(self.function_id)
            except Exception as e:
                self.sig_event.emit("Agentlib:", str(e))
                self.sig_responseid.emit(2) # RESPONSE_ID_ERROR
            self.sig_functionready.emit(0)
            self.sig_responseready.emit(1)

        elif self.done != 0:
            self.sig_event.emit("Agentlib:","Clean up")
            self.sig_functionready.emit(0)
            self.last_request = time.time()


        else:
            if time.time() - self.last_request > self.longest_request_time:
                self.event.emit("Agentlib:","Agent (ID {}) has lock for too long. Agent dead? Clean up, revoke lock.".format(self.station_lock_id))
                self.sig_functionready.emit(0)
                self.sig_done.emit(1)
        self.sig_event.emit("Agentlib:", f"handle_requests called. Actual status:\nlock id = {self.stationlockid}\nlock request = {self.stationlockrequest}\ndone = {self.done}\nfunction id = {self.function_id}\nfunction ready = {self.function_ready}\nlast request = {self.last_request}")


    def run(self):
        """start the worker thread"""
        self.sig_started.emit(True)
        while self.running:
            self.handle_requests()
            self.sleep(self.wait_time_short)
        self.sig_stopped.emit(True)

    def stop(self):
        """cleanly shutdown the worker thread"""
        self.running = False
        self.wait()
        self.deleteLater()


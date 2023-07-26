#!/usr/bin/env python
"""Generic implementation of agent system (see bachelor thesis
Lars Kistner). THIS IS A GENERIC LIBRARY, IT SHOULDN'T BE NEEDED
TO ADD FUNCTION OR STATION SPECIFIC CODE HERE.

Copyright 2016, Lars Kistner <LarsKistner@sr4l.de>
see LICENSE and README for more information
"""

# Standard Python
from __future__ import (
    absolute_import, division, print_function, unicode_literals)
from time import time, sleep
import threading

# 3rd party librarys
import pymodbus
from pymodbus.client.sync import ModbusTcpClient as ModbusClient
from pymodbus.server.sync import ModbusTcpServer
from pymodbus.device import ModbusDeviceIdentification
from pymodbus.datastore import ModbusSequentialDataBlock
from pymodbus.datastore import ModbusSlaveContext, ModbusServerContext

import asyncua as ua
from asyncua import Client


# project internal librarys
from .muplant_params import *

# setup logging
import logging
logging.basicConfig()
log = logging.getLogger()
# log.setLevel(logging.INFO)
log.setLevel(logging.WARN)
# log.setLevel(logging.FATAL)

VERSION = "13.11.18"

# important agent system adresses
MMAP_Status = 1
MMAP_KeepAlive = 2
MMAP_Working = 3
MMAP_unused = 4
MMAP_FunctionReady = 5
MMAP_ResponseReady = 6
MMAP_Done = 7
MMAP_StationLockID = 8
MMAP_StationLockRequest = 9
MMAP_FunctionID = 10
MMAP_FuncParameter1 = 11
MMAP_FuncParameter32 = 42
MMAP_ResponseID = 43
MMAP_RespParameter1 = 44
MMAP_RespParameter32 = 75
MMAP_DataRecorder = 100

# important OPC agent system adresses
OPC_Status = "agentStatus" #1
OPC_KeepAlive = "agentKeepAlive" #2
OPC_Working = "agentWorking" #3
OPC_unused = "agentUnused" #4
OPC_FunctionReady = "agentFunctionReady" #5
OPC_ResponseReady = "agentResponseReady" #6
OPC_Done = "agentDone" #7
OPC_StationLockID = "agentAgentLockID" #8
OPC_StationLockRequest = "agentAgentLockRequest" #9
OPC_FunctionID = "agentFunctionID" #10
OPC_FuncParameter = "agentFuncParameter" #array #11-42
OPC_ResponseID = "agentResponseID" #43
OPC_RespParameter = "agentRespParameter" #array #44-75
#OPC_DataRecorder = "" #never implemented #100

# default network config
IP = "0.0.0.0" # Modbus
URL = "opc.tcp://default" # OPC
NODE = "Agentensystem" # OPC
PORT = 5020
SLAVE_ID = 255  # -> broadcasting
OFFSET = 0

# ENUM for pymodbus
HOLDING_REGISTER = 3
INPUT_REGISTER = 4

# default keepalive value
KEEPALIVE = 3


class NotConnected(Exception):
    """Raised exception when trying to read or
    write while not connected."""
    pass

class AlreadyConnected(Exception):
    """Raised if trying to connect, while connected."""
    pass

class Timeout(Exception):
    """Raised if an operation took `to long`."""
    pass

class ConnectionError(Exception):
    """Raised if something on network layer goes wrong."""
    pass

class ConnectionErrorAdressInvaild(Exception):
    """Raised if a client tries to read or write from/to an address that
    is not supposed to be used by the server"""
    pass

class BaseAgent(object):
    """BaseAgent is a class with functions/capabilities
    that are used in sever and client mode."""
    
    def connect(self, force=False):
        """Connect to a station.
        
        Connection parameter are given one initialization.
        If forced: no `already connected` check is performed.
        """
        if self.client and not force:
            raise AlreadyConnected()
        self.client = ModbusClient(self.ip, self.port)

    def disconnect(self, force=False):
        """Disconnect from a station.
        
        If forced: no `connected` check is performed.
        """
        if not self.client and not force:
            raise NotConnected()
        elif not force:
            self.client.close()
        self.client = False

    def reconnect(self, force=False):
        """Disconnect and than connect in one call.
        
        If forced: see function connect and disconnect"""
        self.disconnect(force)
        self.connect(force)

    def mb_write(self, addr, values, verify=False):
        """Write values to modbus holding registers.
        
        * addr   -- register address the first value is written.
        * values -- a single value or a list of values (only 16bit numbers 
                    allowed, DATA TYPE NOT CHECKED, garbage in garbage out).
        * verify -- if True read data and compare to `values`, if not
                    start over .
        """
        if not self.client:
            raise NotConnected()
        if type(values) not in [type([]), type(())]:
            values = [values,]
        while True:
            try:
                ret = self.client.write_registers(addr+self.offset, values, unit=self.slave_id)
            except:
                raise ConnectionError("Can't write to client {}:{}! Connection failed".format(self.ip, self.port))
            if ret == None:
                raise ConnectionError("Can't write to client {}:{}! Still connected? (1)".format(self.ip, self.port))
            elif type(ret) == pymodbus.exceptions.ModbusIOException:
                raise ConnectionError("Can't write to client {}:{}! Still connected? (2)".format(self.ip,self.port))
            elif not ret.function_code < 0x80:
                raise ConnectionErrorAdressInvaild("Can't write to client {}:{}! Is {} vaild register/coil address?".format(self.ip, self.port, addr))
            elif verify and self.mb_read(addr, len(values), False) not in [values, values[0]]:
                #write failed, retry
                #raise IOError("Write failed")
                # ToDo: this is bad solution
                sleep(self.wait_time_short)
                continue
            else:
                # write succeded
                break

    def mb_write_coil(self, addr, values, verify=True):
        """Write values to modbus holding registers.
        
        * addr   -- register address the first value is written.
        * values -- a single value or a list of values (only 16bit numbers 
                    allowed, DATA TYPE NOT CHECKED, garbage in garbage out).
        * verify -- if True read data and compare to `values`, if not
                    start over .
        """
        if not self.client:
            raise NotConnected()
        if type(values) not in [type([]), type(())]:
            values = [values,]
        while True:
            try:
                ret = self.client.write_coils(addr+self.offset_coil, values, unit=self.slave_id)
            except:
                raise ConnectionError("Can't write to client {}:{}! Connection failed (Coils)".format(self.ip, self.port))
            if ret == None:
                raise ConnectionError("Can't write to client {}:{}! Still connected? (C1)".format(self.ip, self.port))
            elif type(ret) == pymodbus.exceptions.ModbusIOException:
                raise ConnectionError("Can't write to client {}:{}! Still connected? (C2)".format(self.ip,self.port))
            elif not ret.function_code < 0x80:
                raise ConnectionErrorAdressInvaild("Can't write to client {}:{}! Is {} vaild register/coil address? (Coil)".format(self.ip, self.port, addr+self.offset_coil))
            elif verify and self.mb_read_coil(addr, len(values), False) not in [values, values[0]]:
                #write failed, retry
                #raise IOError("Write failed")
                # ToDo: this is bad solution
                sleep(self.wait_time_short)
                continue
            else:
                # write succeded
                break

    def mb_read(self, addr, count=1, align_one = True):
        """Read values from modbus holding registers.
        
        * addr   -- register address of the the first value to read from.
        * count     -- number of registers to read (min 1 ~ 125).
        * align_one -- if True first register is list index 1 (data[1]
                       not data[0], idea: index == address)
        """
        if not self.client:
            raise NotConnected()
        try:
            ret = self.client.read_holding_registers(addr+self.offset, count, unit=self.slave_id)
        except:
            raise ConnectionError("Can't read from client {}:{}! Connection failed (Register)".format(self.ip, self.port))
        if ret == None:
            raise ConnectionError("Can't read from client {}:{}! Still connected? (R1)".format(self.ip, self.port))
        elif type(ret) == pymodbus.exceptions.ModbusIOException:
            raise ConnectionError("Can't read from client {}:{}! Still connected? (R2)".format(self.ip, self.port))
        elif not ret.function_code < 0x80:
           raise ConnectionErrorAdressInvaild("Can't read from client {}:{}! Is {} vaild register/coil address? (Register)".format(self.ip, self.port, addr))

        if count == 1:
            return ret.registers[0]
        if align_one:
            return [0] + ret.registers
        return ret.registers

    def mb_read_coil(self, addr, count=1, align_one = True):
        """Read values from modbus coils.
        
        * addr   -- coil address of the the first value to read from.
        * count     -- number of coils to read (min 1 ~ 125).
        * align_one -- if True first register is list index 1 (data[1]
                       not data[0], idea: index == address)
        """
        if not self.client:
            raise NotConnected()
        try:
            ret = self.client.read_coils(addr+self.offset_coil, count, unit=self.slave_id)
        except:
            raise ConnectionError("Can't read from client {}:{}! Connection failed (Coil)".format(self.ip, self.port))
        if ret == None:
            raise ConnectionError("Can't read from client {}:{}! Still connected? (C1)".format(self.ip, self.port))
        elif type(ret) == pymodbus.exceptions.ModbusIOException:
            raise ConnectionError("Can't read from client {}:{}! Still connected? (C2)".format(self.ip, self.port))
        elif not ret.function_code < 0x80:
           raise ConnectionErrorAdressInvaild("Can't read from client {}:{}! Is {} vaild register/coil address? (Coil)".format(self.ip, self.port, addr+self.offset_coil))

        if count == 1:
            return ret.bits[0]
        if align_one:
            return [0] + ret.bits[:count]
        return ret.bits[:count]

    def __enter__(self):
        """Support **with**-statement."""
        self.connect()
        return self

    def __exit__(self, type, value, traceback):
        """Support **with**-statement."""
        self.disconnect()


class AgentClient(BaseAgent):

    """implementation of an agent client system
    
    * agent_id -- must be a number, if two clients have the same agent_id
                  and access the same AgentServer in the same time the
                  system is not thread-safe anymore, behavior is than
                  undefined.
    * ip, port -- ip and port of target (AgentServer) system.
    * slave_id -- slave_id should be irrelevant in Modbus/TCP but isn't
                  depending on implementation of Modbus/TCP server. `0`,
                  `1`, `255` are good values to start with.
    * offset   -- offset between Modbus address and first agent system
                  variable (`status`). E.g. status is expected on Modbus
                  address 1 but is 16 offset is 15.
    * timeout  -- roughly the maximum value in seconds a read or write is
                  canceled
    """
    def __init__(self, agent_id, ip=IP, port=PORT, slave_id = SLAVE_ID, offset = OFFSET, offset_coil = OFFSET, timeout = 30):
        """initialization of agent client"""
        # needed for BaseAgent
        self.ip = ip
        self.port = port
        self.slave_id = slave_id
        self.client = False
        self.offset = offset
        self.offset_coil = offset_coil

        # needed for AgentClient
        self.agent_id = agent_id
        self.wait_time_short = 0.001 # 1 kHz (~333Hz is maximum * 2 ~= 700)
        self.timeout = timeout

        self.lz_compatibility_mode = False

    def call(self, function_code, function_parameters=[], read_response=True):
        """safe way to call a function_code with parameters
        
        * function code -- 16bit integer selecting the function to be
                           executed, for valid numbers see documentation
                           e.g. Lars Kistner BA thesis.
        * function_parameter -- 16 integer, valid numbers depend on
                           executed function
        * read_response -- bool, if True returned the response code and
                           additional information, if not this data is
                           ignored
        """
        try:
            return self.call_raw(function_code, function_parameters, read_response)
        except (ConnectionError, ConnectionErrorAdressInvaild, Timeout):
            tmp = [RESPONSE_ID_ERROR,]
            tmp.extend(32*[0])
            return tmp

    def call_raw(self, function_code, function_parameters=[], read_response=True):
        """ raw method to call a function, you have to handle raised
        erros, see documentation of `call` for more informations
        """
        if not self.client:
            raise NotConnected()

        while True:
            # read all data
            read = self.mb_read(MMAP_Status, MMAP_RespParameter32)
            log.info(read)

            if read[MMAP_StationLockID] == 0:
                log.info("Station is free, acquire lock")
                self.mb_write(MMAP_StationLockRequest, self.agent_id, verify=False)
            elif read[MMAP_StationLockID] != self.agent_id:
                log.info("Some one else has the lock")
                sleep(self.wait_time_short)

            elif read[MMAP_StationLockID] == self.agent_id and (read[MMAP_Done] == 1 and not self.lz_compatibility_mode):
                log.info("I hold the lock, but finished")
                sleep(self.wait_time_short)
            elif read[MMAP_StationLockID] == self.agent_id and (read[MMAP_Done] == 0 or self.lz_compatibility_mode):
                log.info("I hold the lock")
                function_data = [function_code,]
                function_data.extend(function_parameters)

                log.info("Write function: {}".format(function_data))
                self.mb_write(MMAP_FunctionID, function_data)
                self.mb_write(MMAP_FunctionReady, 1)

                if read_response:
                    timeout_count = 0
                    while self.mb_read(MMAP_ResponseReady) == 0:
                        log.info("Wait for answer")
                        sleep(self.wait_time_short)
                        timeout_count += self.wait_time_short
                        if timeout_count > self.timeout:
                            raise Timeout("ResponseReady Timeout from IP {}".format(self.ip))

                    response = self.mb_read(MMAP_ResponseID, 33, False)
                else:
                    response = None

                log.info("Response: {}".format(response))
                log.info("Write that I finished")
                self.mb_write(MMAP_Done, 1)

                return response
            else:
                log.error("This should not have happend!")
                raise NotImplementedError("This should not have happend!")

    def get_robot_status(self):
        """a 'ready to use' call of ROBOT_STATUS, returns information
        about whether it's save for a robot to leave a station
        """
        ret = self.call(FUNCTION_ID_ROBOTER_STATUS)
        if ret[0] == RESPONSE_ID_ROBOTER_STATUS:
            return ret[1:3]
        else:
            log.error("Station has no ROBOTER_STATUS implemented?!")
            return False

    def get_status(self):
        """returns the status of a station
        status = (0 unknown, 1 automatic, 2 manual, 3 error)
        """
        try:
            return self.mb_read(MMAP_Status)
        except (ConnectionError, ConnectionErrorAdressInvaild):
            return 0

    def dummy(self, *kargs):
        """Just returns a the response of a successfully executed
        function. Utilized for non-mobile-robot orders. See
        `muplant_order`.Order.get_step() for more background information.
        """
        tmp = [RESPONSE_ID_SUCCESS,]
        tmp.extend(32*[0])
        return tmp

    def call_legacy(self, function_code, function_parameters=[], read_response=True):
        """like call_raw, but opens a connection for each request and
        close it afterwards, for more information see documentation
        of `call_raw`.
        """
        if self.client:
            raise AlreadyConnected()

        with ModbusClient(self.ip, self.port) as client:
            self.client = client
            response = self.call(function_code, function_parameters, read_response)
            self.client = False
            return response

    def is_alive(self):
        """ checks the state of a station, returns True for fully alive
        (Modbus on, program running) station, None for only Modbus
        available and False for no connection to Modbus server.
        """
        try:
            keep_alive = self.mb_read(MMAP_KeepAlive)
        except (ConnectionError):
            return False
        except ConnectionErrorAdressInvaild:
            return None

        if keep_alive > 0:
            try:
                self.mb_write(MMAP_KeepAlive, keep_alive-1, verify=False)
            except (ConnectionError, ConnectionErrorAdressInvaild):
                pass
            return True
        else:
            return None

    def free_station(self):
        self.mb_write(MMAP_Done, 1)
        return True


class AgentClientOPC():
    """implementation of an agent client system

    * agent_id -- must be a number, if two clients have the same agent_id
                  and access the same AgentServer in the same time the
                  system is not thread-safe anymore, behavior is than
                  undefined.
    * ip, port -- ip and port of target (AgentServer) system.
    * slave_id -- slave_id should be irrelevant in Modbus/TCP but isn't
                  depending on implementation of Modbus/TCP server. `0`,
                  `1`, `255` are good values to start with.
    * offset   -- offset between Modbus address and first agent system
                  variable (`status`). E.g. status is expected on Modbus
                  address 1 but is 16 offset is 15.
    * timeout  -- roughly the maximum value in seconds a read or write is
                  canceled
    """
    def __init__(self, agent_id, url=URL, port=PORT, slave_id = SLAVE_ID, offset = NODE, offset_coil = OFFSET, timeout = 30):
        """initialization of agent client"""
        # needed for BaseAgent
        self.url = url
        self.port = port
        if self.url in [OPC_PI1_URL, OPC_FZL_URL, OPC_FZR_URL, OPC_AUE1_URL, OPC_AUE2_URL]:
            self.uri = "urn:BeckhoffAutomation:Ua:{}".format(self.port)
        else:
            print("Anlage noch nicht implementiert")
        self.var_location = offset # TODO: rename
        #self.user = ""
        #self.password = ""
        self.cert = "Beckhoff_OpcUaServer.der"
        self.key = "Beckhoff_OpcUaServer.pem"
        self.security_string = "Basic256Sha256,Sign,{},{}".format(self.cert, self.key)

        self.slave_id = slave_id
        self.client = False
        self.offset = offset
        self.offset_coil = offset_coil

        # needed for AgentClient
        self.agent_id = agent_id
        self.wait_time_short = 0.001 # 1 kHz (~333Hz is maximum * 2 ~= 700)
        self.timeout = timeout

        self.lz_compatibility_mode = False

    def connect(self, force=False):
        """Connect to a station.

        Connection parameter are given one initialization.
        If forced: no `already connected` check is performed.
        """
        if self.client and not force:
            raise AlreadyConnected()
        try:
            self.client = Client(self.url)
            #self.client.set_user(self.user)
            #self.client.set_password(self.password)
            self.client.set_security_string(self.security_string)
            self.client.connect()
            print("Connected to "+self.name)
        except:
            print("{} offline!".format(self.name))
        

    def disconnect(self, force=False):
        """Disconnect from a station.

        If forced: no `connected` check is performed.
        """
        if not self.client and not force:
            raise NotConnected()
        elif not force:
            self.client.disconnect()
        self.client = False

    def reconnect(self, force=False):
        """Disconnect and than connect in one call.

        If forced: see function connect and disconnect"""
        print("Attempting to reconncet to "+self.name)
        try:
            self.disconnect(force)
        except:
            pass # already disconnected
        self.connect(force)
    
    def get_node(self, var_name, var_location=None):
        """Get node of a variable in the connected server's namespace. 
        The Node is later used to read and write it's value.

        * var_name     -- Variable name
        * var_location -- Location of the variable. If None then the clients 
                          default (self.var_location) is used.
        """
        ns = self.client.get_namespace_index(self.uri)
        if var_location == None:
            var_location = self.var_location
        node_id = "ns={}; s={}.{}".format(ns, var_location, var_name)
        node = self.client.get_node(node_id)
        return node
        
    def mb_write(self, var_list, val_list, var_location= None, verify=True):
        """Write values to connected OPC server's default port.

        * addr   -- register address the first value is written.
        * values -- a single value or a list of values (only 16bit numbers
                    allowed, DATA TYPE NOT CHECKED, garbage in garbage out).
        * verify -- if True read data and compare to `values`, if not
                    start over .
        """
        if var_list != "agentKeepAlive":
            print("in write function: {} to {} in {}:{} at {}".format(val_list, var_list,self.url,self.port, self.var_location))
        if not self.client:
            raise NotConnected()
        while True:
            try:
                if type(var_list) == list:
                    for count, var_name in enumerate(var_list):
                        if var_name != "agentKeepAlive":
                            print("I am at {} in the list.".format(var_name))
                        node = self.get_node(var_name, var_location)
                        data_type = node.get_data_type_as_variant_type()
                        node.set_attribute(ua.ua.AttributeIds.Value, ua.ua.DataValue(ua.ua.Variant([val_list[count]], data_type)))
                else:
                    var_name = var_list
                    node = self.get_node(var_name, var_location)
                    data_type = node.get_data_type_as_variant_type()
                    node.set_attribute(ua.ua.AttributeIds.Value, ua.ua.DataValue(ua.ua.Variant([val_list], data_type)))
                      
            except:
                print("write except :(")
                raise ConnectionError("Can't write to client {}:{}! Connection failed".format(self.url, self.port))
                continue
                
            else:
                break
            
            
    def mb_read(self, var_list, var_location=None):
        """Read values from connected OPC server's default port.

        * addr   -- register address of the the first value to read from.
        * count     -- number of registers to read (min 1 ~ 125).
        * align_one -- if True first register is list index 1 (data[1]
                       not data[0], idea: index == address)
        """
        if not self.client:
            raise NotConnected()
        try:
            ret = []
            if type(var_list) == list:
                print(var_list)
                for var_name in var_list:
                    node = self.get_node(var_name, var_location)
                    if (var_name != OPC_KeepAlive) and (var_name != OPC_Status):
                        print("reading list var {} in node {}".format(var_name, node))
                    value = node.get_value()
                    ret.append(value)
            else:
                var_name = var_list
                node = self.get_node(var_name, var_location)
                if (var_name != OPC_KeepAlive) and (var_name != OPC_Status):
                    print("rading var {} in node {}".format(var_name, node))
                value = node.get_value()
                ret = value
                
        except:
            raise ConnectionError("Can't read from client {}:{}! Connection failed".format(self.url, self.port))
        
        if ret == None:
            raise ConnectionError("Can't read from client {}:{}! Still connected? (R1)".format(self.url, self.port))
        return ret
        
    def __enter__(self):
        """Support **with**-statement."""
        self.connect()
        return self

    def __exit__(self, type, value, traceback):
        """Support **with**-statement."""
        self.disconnect()

    def call(self, function_code, function_parameters=[], read_response=True):
        """safe way to call a function_code with parameters

        * function code -- 16bit integer selecting the function to be
                           executed, for valid numbers see documentation
                           e.g. Lars Kistner BA thesis.
        * function_parameter -- 16 integer, valid numbers depend on
                           executed function
        * read_response -- bool, if True returned the response code and
                           additional information, if not this data is
                           ignored
        """
        try: #TODO 
            return self.call_raw(function_code, function_parameters, read_response)
        except (ConnectionError, ConnectionErrorAdressInvaild, Timeout):
            tmp = [RESPONSE_ID_ERROR,]
            tmp.extend(32*[0])
            return tmp

    def call_raw(self, function_code, function_parameters=[], read_response=True):
        """ raw method to call a function, you have to handle raised
        erros, see documentation of `call` for more informations
        """
        if not self.client:
            raise NotConnected()
        while True:
            # read all data
            #read = self.mb_read(MMAP_Status, MMAP_RespParameter32)
            read_OPC_StationLockID = self.mb_read(OPC_StationLockID)
            read_OPC_Done = self.mb_read(OPC_Done)
            #log.info(read)

            if read_OPC_StationLockID == 0:
                log.info("Station is free, acquire lock")
                self.mb_write(OPC_StationLockRequest, self.agent_id, verify=False)
            elif read_OPC_StationLockID != self.agent_id:
                log.info("Some one else has the lock")
                sleep(self.wait_time_short)

            elif read_OPC_StationLockID == self.agent_id and ( read_OPC_Done == 1 and not self.lz_compatibility_mode):
                log.info("I hold the lock, but finished")
                sleep(self.wait_time_short)
            elif read_OPC_StationLockID == self.agent_id and ( read_OPC_Done == 0 or self.lz_compatibility_mode):
                log.info("I hold the lock")

                log.info("Write function: {}, {}".format(function_code, function_parameters))

                self.mb_write(OPC_FunctionID, function_code)
                if function_parameters != []:
                    function_parameters.extend([0] * (32 - len(function_parameters)))
                    self.mb_write(OPC_FuncParameter, function_parameters)
                    
                self.mb_write(OPC_FunctionReady, 1)

                if read_response:
                    timeout_count = 0
                    while self.mb_read(OPC_ResponseReady) == 0:
                        log.info("Wait for answer")
                        sleep(self.wait_time_short)
                        timeout_count += self.wait_time_short
                        if timeout_count > self.timeout:
                            raise Timeout("ResponseReady Timeout from IP {}".format(self.ip))
                    response = [self.mb_read(OPC_ResponseID),]
                    response.extend(self.mb_read(OPC_RespParameter))
                else:
                    response = None

                log.info("Response: {}".format(response))
                log.info("Write that I finished")
                self.mb_write(OPC_Done, 1)
                return response
            else:
                log.error("This should not have happend!")
                raise NotImplementedError("This should not have happend!")

    def get_robot_status(self):
        """a 'ready to use' call of ROBOT_STATUS, returns information
        about whether it's save for a robot to leave a station
        """
        ret = self.call(FUNCTION_ID_ROBOTER_STATUS)
        if ret[0] == RESPONSE_ID_ROBOTER_STATUS:
            return ret[1:3]
        else:
            log.error("Station has no ROBOTER_STATUS implemented?!")
            return False

    def get_status(self):
        """returns the status of a station
        status = (0 unknown, 1 automatic, 2 manual, 3 error)
        """
        try:
            return self.mb_read(OPC_Status)
        except (ConnectionError, ConnectionErrorAdressInvaild):
            return 0

    def dummy(self, *kargs):
        """Just returns a the response of a successfully executed
        function. Utilized for non-mobile-robot orders. See
        `muplant_order`.Order.get_step() for more background information.
        """
        tmp = [RESPONSE_ID_SUCCESS,]
        tmp.extend(32*[0])
        return tmp

    def call_legacy(self, function_code, function_parameters=[], read_response=True):
        """like call_raw, but opens a connection for each request and
        close it afterwards, for more information see documentation
        of `call_raw`.
        """
        if self.client:
            raise AlreadyConnected()

        with ModbusClient(self.ip, self.port) as client:
            self.client = client
            response = self.call(function_code, function_parameters, read_response)
            self.client = False
            return response

    def is_alive(self):
        """ checks the state of a station, returns True for fully alive
        (Modbus on, program running) station, None for only Modbus
        available and False for no connection to Modbus server.
        """
        try:
            keep_alive = self.mb_read(OPC_KeepAlive)
        except (ConnectionError):
            return False
        except ConnectionErrorAdressInvaild:
            return None

        if keep_alive > 0:
            try:
                self.mb_write(OPC_KeepAlive, keep_alive-1)
            except (ConnectionError, ConnectionErrorAdressInvaild):
                pass 
            return True
        else:
            return None

    def free_station(self):
        
        self.mb_write(OPC_Done, 1)
        return True


class AgentServerWorkerBase(BaseAgent, threading.Thread):
    """ the minimum a agent sever should implement. Inherit this class
    implement function_handler and you are good to go with you own
    server.
    
    * IP - IP of plain Modbus server to connect to
    * PORT - PORT of modbus server
    * slave_id - slave id of modbus server
    * offset - offset if agent system variable not start at address 1
    """
    def __init__(self, ip=IP, port=PORT, slave_id = SLAVE_ID, offset = OFFSET):
        threading.Thread.__init__(self)

        # needed for BaseAgent
        self.ip = ip
        self.port = port
        self.slave_id = slave_id
        self.client = False
        self.offset = offset

        # needed for AgentServer
        self.wait_time_short = 1 / 800 # 800 Hz (~360 is maximum * 2 ~= 800)
        self.last_request = 0
        self.longest_request_time = 10
        self.running = True
        self.status = 0
        self.working = 0

        self.daemon = True

    def set_status(self):
        """set status related variables to there default values."""
        self.mb_write(MMAP_Status, self.status)
        self.mb_write(MMAP_KeepAlive, KEEPALIVE)
        self.mb_write(MMAP_Working, self.working)
        self.mb_write(MMAP_unused, 42)
        self.mb_write(MMAP_StationLockRequest, 0)
        #log.info(self.mb_read(1,75))

    def reset_function_status(self):
        """cleanup functions status variables."""
        self.mb_write(MMAP_FunctionReady, 0)
        self.mb_write(MMAP_ResponseReady, 0)
        self.mb_write(MMAP_Done, 0)

    def reset_functioncall(self):
        """cleanup function call variables"""
        self.mb_write(MMAP_FunctionID, [0]*33)

    def reset_response(self):
        """cleanup response variables"""
        self.mb_write(MMAP_ResponseID, [0]*33)

    def copy_function_to_response(self, parameters):
        """copy function variables to response variables (debug only)"""
        self.reset_functioncall()
        self.mb_write(MMAP_ResponseID, parameters)

    def function_handler(self, function):
        """this is run multiple times per second, here is where the
        function code handling, processing and appropriate responses
        are happening."""
        raise NotImplementedError("You need to implemented this function on your own")

    def data_recorder(self):
        """if you want to have data recording write values to some
        modbus addresses here. Pack your data in a big data array and
        write it like: `self.mb_write(agent.MMAP_DataRecorder, data)`"""
        #raise NotImplementedError("You can implement this function")
        pass

    def handle_requests(self):
        """check for request and if any forwards them to
        `function_handler()`, read the log comments bellow and see
        bachelor thesis of Lars Kistner to understand agent system
        """
        function_ready = self.mb_read(MMAP_FunctionReady)
        done = self.mb_read(MMAP_Done)
        station_lock_id = self.mb_read(MMAP_StationLockID)
        station_lock_request = self.mb_read(MMAP_StationLockRequest)

        if station_lock_id == 0 and station_lock_request == 0:
            log.info("No work todo! Set status")
            self.set_status()

            if time() - self.last_request > 1.0:
                # No request in last second than recheck
                # for work only 10x per second
                sleep(0.1)
            else:
                sleep(0.001)

        elif station_lock_id == 0 and station_lock_request != 0:
            log.info("Requested Lock granted")
            self.mb_write(MMAP_StationLockID, station_lock_request)
            self.mb_write(MMAP_StationLockRequest, 0)
            self.last_request = time()

        elif done != 0: # and function_ready == 0:
            log.info("Clean up")
            self.mb_write(MMAP_FunctionReady, [0]*70)
            self.last_request = time()

        elif function_ready == 1:
            function = self.mb_read(MMAP_FunctionID, count=33, align_one=False)
            log.info("Call function {}".format(str(function)))
            try:
                self.function_handler(function)
            except Exception as e:
                log.error(e)
                self.mb_write(MMAP_ResponseID, RESPONSE_ID_ERROR)
            self.mb_write(MMAP_FunctionReady, 0)
            self.mb_write(MMAP_ResponseReady, 1)

        else:
            if time() - self.last_request > self.longest_request_time:
                log.warn("Agent (ID {}) has lock for too long. Agent dead? Clean up, revoke lock.".format(station_lock_id))
                self.mb_write(MMAP_FunctionReady, 0)
                self.mb_write(MMAP_Done, 1)

    def run(self):
        """start the worker thread"""
        print("Start worker thread")
        sleep(3)
        self.connect()
        while self.running:
            self.handle_requests()
            self.data_recorder()
            sleep(self.wait_time_short)
        self.disconnect()
        print("Finished worker thread")

    def shutdown(self):
        """cleanly shutdown the worker thread"""
        self.running = False

class AgentServer(threading.Thread):
    """this is a plain Modbus/TCP server, you do not need to change any
    code here, the functionality is done through `AgentServerWorkerBase`
    class
    
    * IP - IP of the Modbus/TCP server, could be 0.0.0.0 for all interfaces
    * PORT - PORT of the Modbus/TCP server, default is 502
    """
    def __init__(self, ip=IP, port=PORT):
        threading.Thread.__init__(self)

        self.ip = ip
        self.port = port

        # needed for AgentServer
        store = ModbusSlaveContext(
            di = ModbusSequentialDataBlock(0, [0]*2**16),
            co = ModbusSequentialDataBlock(0, [0]*2**16),
            hr = ModbusSequentialDataBlock(0, [0]*2**16),
            ir = ModbusSequentialDataBlock(0, [0]*2**16))
        self.context = ModbusServerContext(slaves=store, single=True)

        self.identity = ModbusDeviceIdentification()
        self.identity.VendorName  = 'pymodbus'
        self.identity.ProductCode = 'PM'
        self.identity.VendorUrl   = 'http://github.com/bashwork/pymodbus/'
        self.identity.ProductName = 'pymodbus Server'
        self.identity.ModelName   = 'pymodbus Server'
        self.identity.MajorMinorRevision = '1.0'

        self.running = True

    def run(self):
        """start the server thread"""
        print("Start Server thread")
        server = ModbusTcpServer(self.context, identity=self.identity, address=(self.ip, self.port))
        server.timeout = 0.5
        while self.running:
            server.handle_request()
        server.server_close()
        print("Finish Server thread")

    def shutdown(self):
        """cleanly shutdown the server, exit thread"""
        self.running = False

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright 2016, Lars Kistner <LarsKistner@sr4l.de>
see LICENSE and README for more information
"""

# Standard Python library
from __future__ import absolute_import, division, print_function, unicode_literals
from time import sleep, time
from random import randint, choice
from collections import Counter, defaultdict

from .muplant_params import *
from . import agent

#
# All the stations
#
class RosStation(agent.AgentClient):
    """ Robot Operating System station for sending commands to ROS system """
    name = "ROS"
    station_id = STATION_ID_ROS
    
    def new_transport_order(self, transport_id, cup_size, stations):
        """ new transport order with unique `transport_id` (if not unique
        you are updating an old order) with cup_size (1 small, 2 big) and
        a list of stations (e.g. [STATION_ID_LZ, STATION_ID_FZL,
        STATION_ID_L2])"""
        params = [transport_id, cup_size]
        params.extend(stations)
        ret = self.call(FUNCTION_ID_ROS_NEW_TRANSPORT_ORDER, params)
        return ret
    
    def transport_order_status(self, transport_id):
        """ status of an order with `transport_id` returns finished_steps,
        steps to go, state of robot (1 other, 2 pending, 3 traveling, 
        4 docking, 5 docked, 6 undocking) and assigned robot number.
        """
        ret = self.call(FUNCTION_ID_ROS_TRANSPORT_ORDER_STATUS, [transport_id,])
        return ret
    
    def transport_order_start_next_step(self, transport_id):
        """ send a robot with `transport_id` the command to start next
        step (drive and dock to next_station).
        """
        ret = self.call(FUNCTION_ID_ROS_TRANSPORT_ORDER_START_NEXT_STEP, [transport_id,])
        return ret
    
    def abort_transport_order(self, transport_id, becher_entleeren=False, becher_einlagern=False, fahre_zu_ladestation=False):
        """ abort transport order to given transport_id.
        **TODO:** other parameter are not yet transmitted
        """
        ret = self.call(FUNCTION_ID_ROS_ABORT_TRANSPORT_ORDER, [transport_id,])
        return ret
    
    def update_cup_state(self, cup_product, transport_id=False, robot=False):
        """ update cup product for `transport_id`or `robot`to given
        cup_product, so the robot knows what he transports
        """
        ret = self.call(FUNCTION_ID_ROBOT_UPDATE_CUP_STATE, [transport_id, robot, cup_product])
        return ret

class AueStation(agent.AgentClientOPC):
    """ Abfuell und Entleer station for sending commands to AuE1 or 2"""
    name = "AuE"
    station_id = False
    
    def priming(self, quantity, valve_position=0, security_level=SECURITY_LEVEL):
        """ priming (vorfüllen) of tank (Vorlagebehaelter) with given
        quantity in ml, valve_position defines where to pull water from
        """
        ret = self.call(FUNCTION_ID_AUE_PRIMING, [security_level, valve_position, quantity])
        return ret
    
    def botteling(self, security_level=SECURITY_LEVEL):
        """ open valve and let water flow from tank into cup """
        ret = self.call(FUNCTION_ID_AUE_BOTTLEING, [security_level])
        return ret
    
    def emptying(self, security_level=SECURITY_LEVEL):
        """ take big cup and empty it """
        ret = self.call(FUNCTION_ID_AUE_EMPTYING, [security_level])
        return ret

class LzStation(agent.AgentClient):
    """ Lagerzelle station """
    name = "LZ"
    station_id = STATION_ID_LZ
    
    robot_to_storage_cmd = 1
    storage_to_robot_cmd = 2
    prepare = 1
    execute = 2
    
    def __storage_command(self, to_storage, prefetch, cup_id, product_id):
        """ low level storage command, read LZ docs to understand it """
        if not cup_id and not product_id:
            raise ArgumentError("Need atleast one. product_id or cup_id")
        elif cup_id and product_id:
            raise ArgumentError("Need only one. product_id or cup_id")
            
        if to_storage:
            parameter1 = self.robot_to_storage_cmd
        else:
            parameter1 = self.storage_to_robot_cmd
        
        if prefetch:
            parameter2 = self.prepare
        else:
            parameter2 = self.execute
            
        if cup_id:
            parameter3 = 0b00000001
            parameter4 = becher_id
        elif product_id:
            parameter3 = 0b00000010
            parameter4 = product_id
        
        parameters = [SECURITY_LEVEL, parameter1, parameter2, parameter3, parameter4]
        ret = self.call(FUNCTION_ID_STORAGE_ORDER, parameters)
        return ret
    
    def robot_to_storage(self, prefetch = False, cup_id = False, product_id = False):
        """ cup from robot to storage, prefetch prepares (True = palette
        to K1, False also cup to K1 and palate from K1 to storage), 
        a explicit cup_id or a product_id must be given.
        """
        return self.__storage_command(True, prefetch, cup_id, product_id)
    
    def storage_to_robot(self, prefetch = False, cup_id = False, product_id = False):
        """ cup from storage to robot, prefetch prepares (True = palette
        to K1, False also cup to robot and palate from K1 to storage), 
        a explicit cup_id or a product_id must be given.
        """
        return self.__storage_command(False, prefetch, cup_id, product_id)
    
    def get_cups_ids(self):
        """ get all cup_ids in storage, starting up left, pallet front
        to back, 0-no cup, 1+ cup_id
        """
        try:
            ids = self.mb_read(1024, 36)
        except:
            return False
        return ids
    
    def get_cups_products(self, filter_ids = []):
        """ get all product_ids in storage with amount, 0-no cup,
        1-empty cup, 2-unknown, 3+ product, filter_ids will be removed
        from list
        """
        try:
            prod = self.mb_read(1060, 36)
        except:
            return False
        prod_id_count = Counter(prod)
        prod_id_count_dict = defaultdict(int)
        for k, v in prod_id_count.items():
            if k not in filter_ids:
                prod_id_count_dict[k] = v
        return prod_id_count_dict


class FzlStation(agent.AgentClientOPC):
    """ Fertigungszelle links"""
    name = "FZL"
    station_id = STATION_ID_FZL

    def emptying(self, security_level=SECURITY_LEVEL):
        """empty/recycle a cup"""
        ret = self.call(FUNCTION_ID_FZL_EMPTY_BIN, [security_level])
        return ret
    
    def emptying_tank(self, to_pi2=False, security_level=SECURITY_LEVEL):
        """empty the tank, bool to_pi2 decides whether to empty to
        zentraltank of PI1 or PI2
        """
        if to_pi2:
            parameter2 = True
        else:
            parameter2 = False
        
        ret = self.call(FUNCTION_ID_FZL_EMPTY_TANK, [security_level, parameter2])
        return ret


class FzrStation(agent.AgentClientOPC):
    """ Fertigungszelle rechts"""
    name = "FZR"
    station_id = STATION_ID_FZR

    def add_balls(self, red, yellow, blue, security_level=SECURITY_LEVEL):
        """ add balls to cup, parameter red, yellow and blue, defines
        the amount of balls """
        ret = self.call(FUNCTION_ID_FZR_ADD_BALLS, [security_level, red, yellow, blue])
        return ret

class Pi1Station(agent.AgentClientOPC):
    """ Prozessinsel 1"""
    name = "PI1"
    station_id = STATION_ID_PI1
    
    def fill_water(self, quantity, security_level=SECURITY_LEVEL):
        """fill `quantity`in ml water in tank 04."""
        ret = self.call(FUNCTION_ID_PI1_FILL_WATER, [security_level, quantity])
        return ret
    
    def mix_water(self, quantity_sirup, security_level=SECURITY_LEVEL):
        """mix `quantity_sirup`in ml with all water from tank 04."""
        ret = self.call(FUNCTION_ID_PI1_MIX_WATER, [security_level, quantity_sirup])
        return ret
    
    def is_mix_finished(self, security_level=SECURITY_LEVEL):
        """ returns success if mixing water and syrup is finished. """
        ret = self.call(FUNCTION_ID_PI1_MIX_FINISHED, [security_level])
        return ret
    
    def product_bottled(self, security_level=SECURITY_LEVEL):
        """ restores initial_state like state but keep syrup
        tank untouched. """
        ret =  self.call(FUNCTION_ID_PI1_PRODUCT_BOTTLED, [security_level])
        return ret
    
    def initial_state(self, quantity, security_level=SECURITY_LEVEL):
        """ restores initial state (all tanks empty, syrup tank with
        `quantity` in ml. """
        ret =  self.call(FUNCTION_ID_PI1_INITIAL_STATE, [security_level, True, quantity])
        return ret
    
    def water_to_pi2(self, pump_on, pump_level=100, security_level=SECURITY_LEVEL):
        """ activate or deactivate pump for PI2 according to
        bool pump_on, pump_level defines pump output in percent. """
        ret =  self.call(FUNCTION_ID_PI1_WATER_TO_PI2, [security_level, pump_on, pump_level])
        return ret

class Pi2Station(object):
    """ Prozessinsel2.
    
    This class is much more complicated because PI2 is not a Agent-System
    station, functions set pure Modbus functions.
    """
    def __init__(self):
        self.name = "PI2"
        self.station_id = STATION_ID_PI2
        self.coil_map = ["initalisiere", "produzieren", "pumpe_an",
                        "zulauf_ventil_auf", "am_produzieren"]
        
        self.register_map = ["initial_produkttank_inhalt", "pumpen_leistung",
                            "produktions_menge", "produktions_zeit", "status",
                            "momentaner_produkttank_inhalt", "reservoirinhalt"]
    
    def coil(self, adress, count = 0, write = False, slave_id=255):
        """ read or write coil (bit), handles exceptions """
        try:
            return self.coil_raw(adress, count, write, slave_id)
        except (agent.ConnectionError):
            return False
    
    def coil_raw(self, adress, count = 0, write = False, slave_id=255):
        """ read or write coil (bit), exceptions must be handled by
        programmer """
        try:
            with agent.ModbusClient(MODBUS_PI2_IP, MODBUS_PI2_PORT) as client:
                if write:
                    client.write_coils(adress+MODBUS_PI2_OFFSET, write, unit=slave_id)
                    return True
                else:
                    rr = client.read_coils(adress+MODBUS_PI2_OFFSET, count, unit=slave_id)
                    if rr == None:
                        return False
                    elif type(rr) in (agent.pymodbus.exceptions.ConnectionException, agent.pymodbus.exceptions.ModbusIOException):
                        raise agent.ConnectionError("PI2 Connection Error")
                    elif rr.function_code < 0x80:
                        return rr.bits[:count]
                    return False
        except agent.pymodbus.exceptions.ConnectionException:
            raise agent.ConnectionError("PI2 Connection Error")
    
    def register(self, adress, count = 0, write = False, slave_id=255):
        """ read or write register (16bit), handles exceptions """
        try:
            return self.register_raw(adress, count, write, slave_id)
        except agent.ConnectionError:
            return False
    
    def register_raw(self, adress, count = 0, write = False, slave_id=255):
        """ read or write register (16bit), exceptions must be handled
        by programmer """
        try:
            with agent.ModbusClient(MODBUS_PI2_IP, MODBUS_PI2_PORT) as client:
                if write:
                    client.write_registers(adress+MODBUS_PI2_OFFSET, write, unit=slave_id)
                    return True
                else:
                    rr = client.read_holding_registers(adress+MODBUS_PI2_OFFSET, count, unit=slave_id)
                    if rr == None:
                        return False
                    elif type(rr) in (agent.pymodbus.exceptions.ConnectionException, agent.pymodbus.exceptions.ModbusIOException):
                        raise agent.ConnectionError("PI2 Connection Error")
                    elif rr.function_code < 0x80:
                        return rr.registers
                    return False
        except agent.pymodbus.exceptions.ConnectionException:
            raise agent.ConnectionError("PI2 Connection Error")
    
    def initialisieren(self, produkt_tank_inhalt):
        """ initialise station, set `produkt_tank_inhalt` in ml """
        suc = True
        ret = self.register(self.register_map.index("initial_produkttank_inhalt"), write=[produkt_tank_inhalt,])
        if not ret: suc = False
        ret = self.coil(self.coil_map.index("initalisiere"), write=[True,])
        if not ret: suc = False
        
        tmp = [RESPONSE_ID_SUCCESS if suc else RESPONSE_ID_ERROR,]
        tmp.extend(32*[0])
        return tmp
    
    def free_station(self):
        """ dummy function, station is not thread-safe so can't be blocked """
        return True
        
    def pumpe(self, an=False, leistung=50):
        """ pump on or off with power `leistung` in percent
        from PI2-Produkttank1 to AuE2"""
        suc = True
        ret = self.register(self.register_map.index("pumpen_leistung"), write=[leistung,])
        if not ret: suc = False
        ret = self.coil(self.coil_map.index("pumpe_an"), write=[an,])
        if not ret: suc = False
        
        tmp = [RESPONSE_ID_SUCCESS if suc else RESPONSE_ID_ERROR,]
        tmp.extend(32*[0])
        return tmp
    
    def produziere(self, menge, zeit):
        """produce `menge` in ml in `zeit` seconds to PI2-Produkttank1"""
        # check if Pi2 is already producing (ret[0] not RESPONSE_ID_SUCCESS)
        # if so return original return code
        ret = self.get_am_produzieren()
        if ret[0] != RESPONSE_ID_SUCCESS:
            return ret
        
        # otherwise start production
        suc = True
        ret = self.register(self.register_map.index("produktions_menge"), write=[menge,])
        if not ret: suc = False
        ret = self.register(self.register_map.index("produktions_zeit"), write=[zeit,])
        if not ret: suc = False
        ret = self.coil(self.coil_map.index("produzieren"), write=[True,])
        if not ret: suc = False
        
        tmp = [RESPONSE_ID_SUCCESS if suc else RESPONSE_ID_ERROR,]
        tmp.extend(32*[0])
        sleep(1) # give pi2 some time to process
        return tmp

    def zulauf_ventil_auf(self, auf):
        """ open or close valve to let water in to zentral tank"""
        suc = True
        ret = self.coil(self.coil_map.index("zulauf_ventil_auf"), write=[auf,])
        if not ret: suc = False
        tmp = [RESPONSE_ID_SUCCESS if suc else RESPONSE_ID_ERROR,]
        tmp.extend(32*[0])
        return tmp
    
    def get_status(self):
        """ return status (auto, manual, error) """
        try:
            return self.register(self.register_map.index("status"), 1)[0]
        except TypeError:
            return 0
    
    def get_produkttank_inhalt(self):
        """ get PI2-Produkttank1 amout in ml """
        return self.register(self.register_map.index("momentaner_produkttank_inhalt"), 1)
        
    def get_reservoir_inhalt(self):
        """ get PI2-Zentraltrank amout in 100ml """
        return self.register(self.register_map.index("reservoirinhalt"), 1)
        
    def get_am_produzieren(self):
        """ get status of working or not """
        data = self.coil(self.coil_map.index("am_produzieren"), 1)
        if not data:
            tmp = [RESPONSE_ID_ERROR,]
        elif data[0]:
            tmp = [RESPONSE_ID_NOT_READY,]
        else:
            tmp = [RESPONSE_ID_SUCCESS,]
        tmp.extend(32*[0])
        return tmp
    
    
    def is_alive(self):
        """ get status station running/online or not """
        try:
            self.register(self.register_map.index("status"), 1)
            return True
        except:
            return False

    def dummy(self, *kargs):
        """Just returns a the response of a successfully executed
        function. Utilized for non-mobile-robot orders. See
        `muplant_order`.Order.get_step() for more background information.
        """
        tmp = [RESPONSE_ID_SUCCESS,]
        tmp.extend(32*[0])
        return tmp

class DummyStation(object):
    """ a virtual station with limit functionality
    FOR DEVELOPING/TESTING ONLY.
    """
    def __init__(self):
        self.name = "DummyStation"
        self.st = False
        self.wait_time = 15
    
    def waste_time(self):
        tmp = [RESPONSE_ID_NOT_READY,]
        if self.st:
            if (time() - self.st) > self.wait_time:
                self.st = False
                tmp = [RESPONSE_ID_SUCCESS,]
        else:
            self.st = time()
        tmp.extend(32*[0])
        return tmp
    
    def prepare(self, ratio, quantity):
        return self.waste_time()
    
    def blend(self):
        return self.waste_time()
    
    def is_alive(self):
        return True

if __name__ == "__main__":
    pass
    

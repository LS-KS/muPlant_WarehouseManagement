#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Class Order is a class used by order_manager to define the goal of an
order and keep the state. It also has a lot of functions to start with
an empty order to a `multi step` order. That order steps a coherent
(make sense) is in programmers responsibility. See the functions in this
file for an example how to build an order from scratch.

Copyright 2016, Lars Kistner <LarsKistner@sr4l.de>
see LICENSE and README for more information
"""

# Standard Python library
from __future__ import absolute_import, division, print_function, unicode_literals
from datetime import datetime
from time import sleep, time
from random import randint, choice

#
# An order
#
class Order():
    """define the goal of an order and keep the state of this order,
    also has functions to build up a custom order"""
    
    def __init__(self, description = ""):
        self.description = description
        self.order_id = randint(2**14, 2**16)
        self.cup_size = 1
        self.need_ros = True
        self.assigned_robot_number = None
        self.depend_on_order = []
        
        self.step = 0
        self.substep = 0
        self.stations = []
        self.steps = []
        self.runtime = []
        self.color = choice(['red', 'blue', 'green', 'cyan', 'magenta', 'yellow'])
        
        self.started = None
        self.finished = None
    
    def is_active(self):
        """ returns bool about active state of an order """
        if len(self.steps) <= self.step:
            if self.finished == None:
                self.finished = datetime.now()
            return False
        else:
            return True
    
    def add_depend_on_order(self, order):
        """add another Order-class instance (not oder_id) as dependency
        order will only be executed if the dependend order is finished
        (not `is_active()`)
        """
        self.depend_on_order.append(order)
    
    def get_step(self):
        """get step of an order.
        
        **Notice:** orders connsist of N steps and 2 substeps, substeps
        are:
        **0**: robot not yet there
        **1**: prepare step (robot in position in front of a station,
        station can start with operations that do not need to interact
        with the robot)
        **2**: an execute step (robot docked in station, station
        operations that need to interact with mobile robot)
        **For non-mobile-robot orders:** same system is used but if you
        use a prepare command is up to the programmer, otherwise the
        `dummy-function is used.
        """
        return self.steps[self.step]
    
    def get_substep(self):
        """get substep of an order, see `get_step` for more details"""
        return self.get_step()[1][self.substep]
    
    def set_time_for_current_step(self, end=False):
        """set the start (end=False) and end-timestamp (end=True) for
        current step, used for visualization purpose"""
        if end:
            x = 1
        else:
            x = 0
        if self.runtime[self.step][x] == None:
            self.runtime[self.step][x] = datetime.now()
    
    def add_aue_botteling(self, station, quantity, valve_position=0):
        """add AuE botteling to an order (robot with cup->aue).
        
        * station - the instance of an AuE station `muplant_station.AueStation()`
        * quantity - quantity of prodoct to bottle in ml
        * valve_position - defines position of directional valve
        """
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.priming, [quantity, valve_position]],
            [station.botteling, []],
            ]])
    
    def add_aue_emptying(self, station):
        """add AuE emptying to an order (robot with big cup->aue).
        
        * station - the instance of an AuE station `muplant_station.AueStation()`
        """
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.emptying, []],
            ]])
    
    def add_lz_to_robot(self, station, cup_id = False, product_id = False):
        """add from storage to robot to an order (robot w/o cup-> robot with cup).
        
        * station - the instance of LZ station `muplant_station.LzStation()`
        * cup_id - cup id, one id must be supplied
        * product_id - product id, one id must be supplied
        """
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
                [station.storage_to_robot, [True, cup_id, product_id]],
                [station.storage_to_robot, [False, cup_id, product_id]],
                ]])
    
    def add_lz_to_storage(self, station, cup_id = False, product_id = False):
        """add from robot to storage to an order (robot with cup-> robot w/o cup).
        
        * station - the instance of LZ station `muplant_station.LzStation()`
        * cup_id - cup id (optional)
        * product_id - product id (required)
        """
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
                [station.robot_to_storage, [True, cup_id, product_id]],
                [station.robot_to_storage, [False, cup_id, product_id]],
                ]])
    
    def add_fzr_add_balls(self, station, red, yellow, blue):
        """add FZ right add balls to an order.
        
        * station - the instance of FZR station `muplant_station.FzrStation()`
        * red - number of balls
        * yellow - number of balls
        * blue - number of balls
        """
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.add_balls, [red, yellow, blue]],
            ]])
    
    def add_fzl_emptying(self, station):
        """add FZ left recycling to an order.
        
        * station - the instance of FZL station `muplant_station.FzlStation()`
        """
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.emptying, []],
            ]])
    
    def add_pi1_production(self, station, quantity_water, quantity_sirup=0, initial_state=0):
        """add Pi1 production to an order.
        
        * station - the instance of Pi1 station `muplant_station.Pi1Station()`
        * quantity_water - quantity of water in ml
        * quantity_sirup - quantity of syrup in ml (default 0)
        * initial_state - if not 0, pi1 is initialized with `initial_state`
                          of syrup before production
        """
        if initial_state > 0:
            self.runtime.append([None, None])
            self.stations.append(station.station_id)
            self.steps.append([station,[
                [station.dummy, []],
                [station.initial_state, [initial_state]],
                ]])
        
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.fill_water, [quantity_water]],
            ]])
        
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.mix_water, [quantity_sirup]],
            ]])
        
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.is_mix_finished, []],
            ]])

    def add_pi1_purging(self, station):
        """empty tanks, syrup tank stays untouched"""
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.product_bottled, []],
            ]])
    
    def add_pi2_production(self, station, quantity_sirup, production_time=60, initial_state=0):
        """add Pi2 production to an order.
        
        * station - the instance of Pi2 station `muplant_station.Pi2Station()`
        * quantity_sirup - quantity of syrup to produce in ml
        * production_time - production time
        * initial_state - if not 0, pi2 is initialized with `initial_state`
                          of syrup before production
        """
        if initial_state > 0:
            self.runtime.append([None, None])
            self.stations.append(station.station_id)
            self.steps.append([station,[
                [station.dummy, []],
                [station.initialisieren, [initial_state]],
                ]])
        
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.produziere, [quantity_sirup, production_time]],
            ]])
        
        self.runtime.append([None, None])
        self.stations.append(station.station_id)
        self.steps.append([station,[
            [station.dummy, []],
            [station.get_am_produzieren, []],
            ]])

#
# Helper functions to build orders
#

def new_order_get_product(lz, aue, fzr, final_product_id, flavor):
    """creates a full order to process a new product.
    
    * lz, aue, fzr - the instance of station e.g. `muplant_station.LzStation()`
    * final_product_id - id of final product e.g. 33 for coce
    * flavor - array of balls [red, yellow, blue]
    """
    flavor_sum = sum(flavor)
    o = Order()
    o.description = "Herstellung neues Produkt {}".format(final_product_id)
    o.add_lz_to_robot(lz, False, product_id=1)
    o.add_aue_botteling(aue, 450-flavor_sum*25)
    if flavor_sum > 0:
        o.add_fzr_add_balls(fzr, *flavor)
    o.add_lz_to_storage(lz, False, product_id=final_product_id)
    return o

def new_order_recycle_product(lz, fzl, product_id):
    """creates a full order to recycle a product.
    
    * lz, fzl - the instance of station e.g. `muplant_station.LzStation()`
    * product_id - id of product for recycling e.g. 33 for coce
    """
    o = Order()
    o.description = "Produkt {} ausliefern".format(product_id)
    o.add_lz_to_robot(lz, False, product_id=product_id)
    o.add_fzl_emptying(fzl)
    o.add_lz_to_storage(lz, False, product_id=1)
    return o

def new_order_transport(quantity, from_station, to_station):
    """creates a full order to transport a product with big cup from
    to station.
    
    * from_station, to_station - the instance of AuE station (`muplant_station.AueStation()`)
    * quantity - quantity to transport from to station
    """
    o = Order()
    o.description = "{}ml Sirup von {} nach {} transportieren".format(quantity, from_station.name, to_station.name)
    o.cup_size = 2
    o.add_aue_botteling(from_station, int(quantity))
    o.add_aue_emptying(to_station)
    return o

def new_order_blend_product(pi1, quantity_water, quantity_sirup):
    """creates a full order to mix a product in Pi1.
    
    * pi1 - the instance of Pi1 station (`muplant_station.Pi1Station()`)
    * quantity_water - quantity water in ml
    * quantity_sirup - quantity syrup in ml
    """
    o = Order()
    o.description = "{}: Mische {}ml Wasser mit {}ml Sirup".format(pi1.name, quantity_water, quantity_sirup)
    o.need_ros = False
    o.add_pi1_production(pi1, int(quantity_water), int(quantity_sirup))
    return o

def new_order_purge_tank(pi1):
    """creates a full order to empty production tanks in pi1, syrup tank
    is untouched.
    
    * pi1 - the instance of Pi1 station (`muplant_station.Pi1Station()`)
    """
    o = Order()
    o.description = "{}: Produkte abgefüllt, Tanks leeren".format(pi1.name)
    o.need_ros = False
    o.add_pi1_purging(pi1)
    return o

def new_order_produce_sirup(pi2, quantity, time=60):
    """creates a full order to produce syrup in Pi2.
    
    * pi2 - the instance of Pi2 station (`muplant_station.Pi2Station()`)
    * quantity - quantity of syrup to produce
    * time - production time in seconds
    """
    o = Order()
    o.description = "{}: Produziere {}ml in {} Sekunden".format(pi2.name, quantity, time)
    o.need_ros = False
    o.add_pi2_production(pi2, int(quantity), time)
    return o



#
# Generate use cases
#
def generate_use_case3_short_orders_one_loop(brain):
    """creates a full chain of orders for a UseCase3
    
    * brain - instance of order_manager.Brain()
    """
    # Recycling (blau)
    cola_recycling = new_order_recycle_product(brain.lz, brain.fzl, 33)
    cola_recycling.color = "#1b26ff"
    
    # Sirup (gruen)
    pi2_order = new_order_produce_sirup(brain.pi2, 800, 120)
    pi2_order.color = "#99ff99"

    sirup_order = new_order_transport(750, brain.aue2, brain.aue1)
    sirup_order.add_depend_on_order(pi2_order)
    sirup_order.color = "#33ff33"
    
    # Cola Produktion (rot)
    pi1_order = new_order_blend_product(brain.pi1, 1250, 750)
    pi1_order.color = "#ff8686"

    cola_order = new_order_get_product(brain.lz, brain.aue1, brain.fzr, 33, [1, 1, 1])
    cola_order.add_depend_on_order(pi1_order)
    cola_order.color = "#ff6161"
    
    pi1_purge_order = new_order_purge_tank(brain.pi1)
    pi1_purge_order.add_depend_on_order(cola_order)
    pi1_purge_order.color = "#ff3131"
    
    # submit
    orders = [cola_recycling, pi2_order, sirup_order, pi1_order, cola_order, pi1_purge_order]
    brain.orders.extend(orders)
        
def generate_use_case3_short_orders(brain, runs = 1):
    """creates multiple full chain of orders for a UseCase3
    
    * brain - instance of order_manager.Brain()
    * runs - number of UseCase3 runs
    """
    last_pi1_order = False
    last_pi2_order = False
    last_sirup_order = False
    last_cola_order = False
    last_pi1_purge_order = False
    
    for i in range(runs):
        pi2_order = new_order_produce_sirup(brain.pi2, 800, 120)
        if last_sirup_order:
            pi2_order.add_depend_on_order(last_sirup_order)
    
        sirup_order = new_order_transport(750, brain.aue2, brain.aue1)
        sirup_order.add_depend_on_order(pi2_order)
        
        pi1_order = new_order_blend_product(brain.pi1, 1250, 750)
        if last_sirup_order:
            pi1_order.add_depend_on_order(last_sirup_order)
        if last_pi1_purge_order:
            pi1_order.add_depend_on_order(last_pi1_purge_order)
    
        cola_order = new_order_get_product(brain.lz, brain.aue1, brain.fzr, 33, [1, 0, 2])
        cola_order.add_depend_on_order(pi1_order)
        
        pi1_purge_order = new_order_purge_tank(brain.pi1)
        pi1_purge_order.add_depend_on_order(cola_order)
        
        cola_recycling = new_order_recycle_product(brain.lz, brain.fzl, 33)
        if last_cola_order:
            cola_recycling.add_depend_on_order(last_cola_order)
        
        # submit
        orders = [pi1_order, pi1_purge_order, pi2_order, sirup_order, cola_order, cola_recycling]
        
        last_pi1_order = pi1_order
        last_pi2_order = pi2_order
        last_sirup_order = sirup_order
        last_cola_order = cola_order
        last_pi1_purge_order = pi1_purge_order
        
        brain.orders.extend(orders)

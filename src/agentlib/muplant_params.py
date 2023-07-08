#!/usr/bin/env python
# coding: utf-8
"""muPlant specific parameters

Copyright 2016, Lars Kistner <LarsKistner@sr4l.de>
see LICENSE and README for more information
"""

#
# FUNCTION IDs
#
FUNCTION_ID_RFID = 1
FUNCTION_ID_STORAGE_ORDER = 2
FUNCTION_ID_ROBOTER_STATUS = 3
FUNCTION_ID_AUE_PRIMING = 4
FUNCTION_ID_AUE_BOTTLEING = 5
FUNCTION_ID_AUE_EMPTYING = 6
FUNCTION_ID_ROS_NEW_TRANSPORT_ORDER = 7
FUNCTION_ID_ROS_TRANSPORT_ORDER_STATUS = 8
FUNCTION_ID_ROS_TRANSPORT_ORDER_START_NEXT_STEP = 9
FUNCTION_ID_ROS_ABORT_TRANSPORT_ORDER = 10
FUNCTION_ID_FZL_EMPTY_BIN = 11
FUNCTION_ID_FZR_ADD_BALLS = 12
FUNCTION_ID_PI1_FILL_WATER = 13
FUNCTION_ID_PI1_MIX_WATER = 14
FUNCTION_ID_PI1_MIX_FINISHED = 15
FUNCTION_ID_PI1_PRODUCT_BOTTLED = 16
FUNCTION_ID_PI1_INITIAL_STATE = 17
FUNCTION_ID_PI1_WATER_TO_PI2 = 18
FUNCTION_ID_ROBOT_UPDATE_CUP_STATE = 19
FUNCTION_ID_FZL_EMPTY_TANK = 20

#
# RESPONSE IDs
#
RESPONSE_ID_SUCCESS = 1
RESPONSE_ID_ERROR = 2
RESPONSE_ID_NOT_READY = 3
RESPONSE_ID_NOT_FOUND = 4
RESPONSE_ID_UNKNOWN_FUNCTION = 501
RESPONSE_ID_TRANSPORT_ORDER_STATUS = 7
RESPONSE_ID_ROBOTER_STATUS = 8
RESPONSE_ID_RFID_WRITEBACK = 9

#
# STATION IDs
#
STATION_ID_LZ = 10
STATION_ID_AUE1 = 20
STATION_ID_AUE2 = 30
STATION_ID_FZL = 40
STATION_ID_FZR = 50
STATION_ID_L1 = 60
STATION_ID_L2 = 70
STATION_ID_L3 = 80
STATION_ID_L4 = 85
STATION_ID_PI1 = 90
STATION_ID_PI2 = 100
STATION_ID_BRAIN = 110
STATION_ID_ROS = 120
STATION_ID_RFID = 130
STATION_ID_DATARECORDER = 140
STATION_ID_ROS_GUI = 150
STATION_ID_CONTROLLER = 160

#
# MODBUS CONNECTION PARAMETER
#
OPC_AUE1_URL = "opc.tcp://mrt-pc147:4840"
OPC_AUE1_PORT = "AuE1"
OPC_AUE1_NODE = "Agentensystem"

OPC_AUE2_URL = "opc.tcp://mrt-pc147:4840"
OPC_AUE2_PORT = "AuE2"
OPC_AUE2_NODE = "Agentensystem"

MODBUS_AUE1_IP = "141.51.45.93"
MODBUS_AUE1_PORT = 502
MODBUS_AUE1_OFFSET = 14287

MODBUS_AUE2_IP = "141.51.45.93"
MODBUS_AUE2_PORT = 502
MODBUS_AUE2_OFFSET = 16287

MODBUS_ROS_IP = "141.51.45.69"
MODBUS_ROS_PORT = 5020
MODBUS_ROS_OFFSET = 0

MODBUS_LZ_IP = "141.51.45.176"
MODBUS_LZ_PORT = 50200
MODBUS_LZ_OFFSET = 0

OPC_PI1_URL = "opc.tcp://mrt-pc141:4840"
OPC_PI1_PORT = "UseCase3"
OPC_PI1_NODE = "Agentensystem"

MODBUS_PI1_IP = "141.51.45.87"
MODBUS_PI1_PORT = 502
MODBUS_PI1_OFFSET = 12303

MODBUS_PI2_IP = "141.51.45.91"
MODBUS_PI2_PORT = 502
MODBUS_PI2_OFFSET = 1

OPC_FZL_URL = "opc.tcp://mrt-pc147:4840"
OPC_FZL_PORT = "Fertigungszelle"
OPC_FZL_NODE = "AgentensystemFZL"

OPC_FZR_URL = "opc.tcp://mrt-pc147:4840"
OPC_FZR_PORT = "Fertigungszelle"
OPC_FZR_NODE = "AgentensystemFZR"

MODBUS_FZL_IP = "141.51.45.93"
MODBUS_FZL_PORT = 502
MODBUS_FZL_OFFSET = 12287

MODBUS_FZR_IP = "141.51.45.93"
MODBUS_FZR_PORT = 502
MODBUS_FZR_OFFSET = MODBUS_FZL_OFFSET+100

#
# DATARECORDING
#
DATA_AUE1_OFFSET = 100 - 15
DATA_AUE1_LENGTH = 18
DATA_AUE1_NAMES = ["reserved", "Nothalt (0,1)", "SPS-Start (0,1)",
    "Motor Geschwindigkeit (%)", "Motor Position", "Motor Bremse (0,1)",
    "Endschalter oben (0,1)", "Endschalter unten (0,1)", "Induktivsensor 1 (0,1)",
    "Induktivsensor 2 (0,1)", "Tank oben (ml)", "Tank unten (ml)",
    "Pumpe oben (%)", "Pumpe unten (%)", "Binaerventil abfuellen (0,1)",
    "Binaerventil Zulauf (0,1)", "Wegeventil Zulauf (0,1)",
    "Wegeventil Ablauf (0,1)"]
DATA_AUE1_FILENAME = "{}-AUE1.csv"

DATA_AUE2_OFFSET = 100 - 15
DATA_AUE2_LENGTH = 18
DATA_AUE2_NAMES = DATA_AUE1_NAMES
DATA_AUE2_FILENAME = "{}-AUE2.csv"

DATA_ROS_OFFSET = 100
DATA_ROS_LENGTH = 100
DATA_ROS_NAMES = ["all_robots_count", "small_cup_robots_count",
    "big_cup_robots_count", "all_active_robots_count",
    "small_cup_active_robots_count", "big_cup_active_robots_count",
    "count_of_active_orders", "order_placing_algo", "new_order_robot_select_algo",
    "robot_behavior_after_order", "unused", "unused", "unused", "unused",
    "unused", "unused", "unused", "unused", "unused", "unused"]
for r in range(4):
    ROBOT = ["r{}_number".format(r), "r{}_enabled".format(r), "r{}_is_charging".format(r),
        "r{}_battery_level".format(r), "r{}_is_small_cup".format(r), "r{}_has_cup".format(r),
        "r{}_order_id".format(r), "r{}_state".format(r), "r{}_traveling_since".format(r),
        "r{}_station".format(r), "r{}_unused".format(r), "r{}_unused".format(r),
        "r{}_unused".format(r), "r{}_unused".format(r), "r{}_unused".format(r),
        "r{}_unused".format(r), "r{}_unused".format(r), "r{}_unused".format(r),
        "r{}_unused".format(r), "r{}_unused"]
    DATA_ROS_NAMES.extend(ROBOT)
DATA_ROS_FILENAME = "{}-ROS.csv"

DATA_LZ_OFFSET = 1024
DATA_LZ_LENGTH = 82
DATA_LZ_NAMES = [""]*DATA_LZ_LENGTH
DATA_LZ_FILENAME = "{}-LZ.csv"

DATA_PI1_OFFSET = 100 - 15
DATA_PI1_LENGTH = 57
DATA_PI1_NAMES_OPC = ["T","BV", "PV", "P", "MID"]
DATA_PI1_NAMES = ["T01", "T02", "T03", "T04", "T05", "T06", "T07", "T08", "T09", "T10",
    "BV01", "BV02", "BV03", "BV04", "BV05", "BV06", "BV07", "BV08", "BV09", "BV10",
    "PV01", "PV02", "PV03", "PV04", "PV05", "PV06", "PV07", "PV08", "PV09", "PV10",
    "P01", "P02", "P03", "P04", "P05", "P06", "P07", "P08", "P09", "P10", "P11", "P12", "P13",
    "MID01", "MID02", "MID03", "MID04", "MID05", "MID06", "MID07", "MID08", "MID09", "MID10", "MID11", "MID12", "MID13"]
DATA_PI1_FILENAME = "{}-PI1.csv"

DATA_PI2_OFFSET = 0
DATA_PI2_LENGTH = 73
DATA_PI2_COILS_OFFSET = 0
DATA_PI2_COILS_LENGTH = 26
DATA_PI2_NAMES = ["InitialProdukttankInhalt (ml)", "Pumpenleistung (%)",
    "Produktionsmenge (ml)", "Produktionszeit (s)", "Status",
    "Volumen Produkt1 (ml)", "Volumen Reservoir (l/10)", "TS_100 (°C/100)",
    "FR_100_V (ml)", "MID_100 (ml/min)", "FR100_out", "TS_200 (°C/100)",
    "FR_200_V (ml)", "MID_200 (ml/min)", "FR200_out", "TS_300 (°C/100)",
    "MR300_V (ml)", "MID_310 (ml/min)", "MID_220 (ml/min)", "MID_320 (ml/min)",
    "T410_V (ml)", "T420_V (ml)", "T430_V (ml)", "T440_V (ml)", "TS_500 (°C/100)",
    "MID_110 (ml/min)", "MID_210 (ml/min)", "MID_221 (ml/min)", "MID_311 (ml/min)",
    "MID_330 (ml/min)", "MID_400 (ml/min)", "HZ_100 (%)", "HZ_100_set (%)",
    "HZ_200 (%)", "HZ_200_set (%)", "HZ_300 (%)", "HZ_300_set (%)", "DE_110 (%)",
    "DE_110_set (%)", "DE_200 (%)", "DE_200_set (%)", "FR100_T_soll", "FR100_V_soll",
    "FR200_T_soll", "FR200_V_soll", "MR300_T_soll", "MR300_V_soll", "PV_220 (%)",
    "PV_220_i (raw 16bit)", "PV_220_set (%)", "PV_221 (%)", "PV_221_i (raw 16bit)",
    "PV_221_set (%)", "PV_311 (%)", "PV_311_i (raw 16bit)", "PV_311_set (raw 16bit)",
    "PV_312 (%)", "PV_312_i (raw 16bit)", "PV_312_set (%)", "PV_400 (%)",
    "PV_400_i (raw 16bit)", "PV_400_set (%)", "PV_401 (%)", "PV_401_i (raw 16bit)",
    "PV_401_set (%)", "P_100_i (raw 16bit)", "P_110_i (raw 16bit)",
    "P_200_i (raw 16bit)", "P_210_i (raw 16bit)", "P_220_i (raw 16bit)",
    "P_310_i (raw 16bit)", "P_320_i (raw 16bit)", "P_400_i (raw 16bit)",
    # BOOLs
    "TCP_initial", "TCP_produziere", "TCP_pumpen", "TCP_zulauf",
    "TCP_produziert", "BV_410", "BV_420", "BV_430", "BV_440", "BV_450",
    "BV_401", "BV_402", "BV_403", "BV_404", "BV_300", "BV_210", "BV_200",
    "BV_201", "BV_110", "BV_100", "BV_101", "BV_411", "BV_421", "BV_431",
    "BV_441", "BV_501",
    ]
DATA_PI2_FILENAME = "{}-PI2.csv"

DATA_FZ_OFFSET= 200 - 15
DATA_FZ_LENGTH = 43
DATA_FZ_NAMES = ["reseved", "Nothalt (0,1)", "SPS-Start (0,1)",
    "Motor Geschwindigkeit (%)", "Motor Position", "Motor Bremse (0,1)",
    "Endschalter oben (0,1)", "Endschalter unten (0,1)",
    "Induktivsensor links 1 (0,1)", "Induktivsensor links 2 (0,1)",
    "Fuellstand Tank (in ml)", "Durchfluss MID (in ml/min)", "Pumpenleistung (%)",
    "Binaerventil 1 (0,1)", "Binaerventil 2 (0,1)", "Lufterwaermer (%)",
    "Geblaese (%)", "PT100 (in Zehntelgrad)", "Gleichstrommotor (%)",
    "Pyrometer (in Zehntelgrad)", "Lichtschranke 1 (0,1)",
    "Pneumatikventil 1 vorne (0,1)", "Pneumatikventil 2 hinten (0,1)",
    "Farbsensor", "Lichtschranke 2 (0,1)", "Pneumatikventil 3 blau (0,1)",
    "Pneumatikventil 4 gelb (0,1)", "Pneumatikventil 5 rot (0,1)",
    "Induktivsensor rechts 1 (0,1)", "Induktivsensor rechts 2 (0,1)",
    "Lichtschranke 3 gelb (0,1)", "Lichtschranke 4 blau (0,1)",
    "Lichtschranke 5 rot (0,1)", "Lichtschranke 6 (0,1)",
    "Pneumatikventil 6 gelb 1 (0,1)", "Pneumatikventil 7 gelb 2 (0,1)",
    "Pneumatikventil 8 blau 1 (0,1)", "Pneumatikventil 9 blau 2 (0,1)",
    "Pneumatikventil 10 rot 1 (0,1)", "Pneumatikventil 11 rot 2 (0,1)",
    "Kugelanzahl Rot (0-200)", "Kugelanzahl Gelb (0-200)",
    "Kugelanzahl Blau (0-200)"]
DATA_FZ_FILENAME = "{}-FZ.csv"

#
# OTHERS
#
SECURITY_LEVEL = 1024 # full security level, not overwriting ANY checks

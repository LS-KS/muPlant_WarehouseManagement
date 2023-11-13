/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_BASIC_H
#define FEDM_BASIC_H

// API transporter classes to exchange data between App and Lib
// All classes defined here do NOT have methods to communicate with reader !

#include <FedmConst.h>
#include <FedmConnector.h>
#include <FedmNetAddr.h>
#include <FedmCfgParInfo.h>
#include <FedmCfgId.h>
#include <FedmRdrId.h>
#include <FedmRdrIdLayout.h>
#include "FedmRdrInfo.h"
#include "FedmRdrDiag.h"
#include "FedmDateTime.h"
#include "FedmNoiseLevel.h"
#include "FedmOutSett.h"
#include "FedmOutSett04.h"
#include "FedmPeerInfo.h"
#include "FedmRssiItem.h"
#include "FedmInvParam.h"
#include "FedmAppLogParam.h"
#include "FedmTagItem.h"
#include "FedmBrmItem.h"
#include "FedmBrmLayout.h"
#include "FedmTagEventItem.h"
#include "FedmDiagEventItem.h"
#include "FedmTagEventLayout.h"
#include "FedmTagEventSignals.h"
#include "FedmInputEventItem.h"
#include "FedmBufferInfo.h"
#include "FedmKeys.h"
#include "FedmSmartCardItem.h"
#include "FedmCustomXml.h"
#include "FedmCardInfo14443.h"
#include "Utility/HexConvert.h"

#endif // FEDM_BASIC_H

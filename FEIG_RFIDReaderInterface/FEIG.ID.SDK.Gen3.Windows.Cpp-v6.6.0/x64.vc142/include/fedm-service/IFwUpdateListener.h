/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FWUPDATE_LISTENER_H
#define FEDM_FWUPDATE_LISTENER_H

#include <FedmServiceBasic.h>



namespace FEDM {

/// @brief LISTENER class for firmware update messages
class FEDM_SERVICE_CLASS_DEF IFwUpdateListener
{
public:
	/// This function is running in an own thread.
	virtual void onNewFwUpdMessage(const FwUpdateMessage & message) { }

}; // end of class FwUpdateListener

}; // end of namespace FEDM

#endif // FEDM_FWUPDATE_LISTENER_H

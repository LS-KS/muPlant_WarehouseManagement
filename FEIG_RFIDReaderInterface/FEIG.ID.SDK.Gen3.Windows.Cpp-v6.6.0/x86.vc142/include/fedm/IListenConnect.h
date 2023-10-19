/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_CONNECT_LISTENER_H
#define FEDM_CONNECT_LISTENER_H

#include "FedmBasic.h"



namespace FEDM {

/// @brief LISTENER for readers connection requests
class FEDM_CLASS_DEF IConnectListener
{
public:
	/// This function is running in an own thread.
    /// @param[in] peerInfo Of the connected reader
	virtual void onConnect(PeerInfo peerInfo)
	{ }

	/// This function is running in an own thread.
	virtual void onDisconnect(void)
	{ }

}; // end of class IConnectListener

}; // end of namespace FEDM

#endif // FEDM_CONNECT_LISTENER_H

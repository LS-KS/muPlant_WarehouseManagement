/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_RDR_LISTENER_H
#define FEDM_RDR_LISTENER_H

#include "FedmBasic.h"



namespace FEDM {

/// @brief LISTENER for reader requests
///
/// Use the event type queue of group async to obtain information about the request.<br>
/// The associated request information is available in various data queues.
class FEDM_CLASS_DEF IReaderListener
{
public:
	/// This function is running in an own thread.<br>
    /// The overloaded implementation must be reentrant.
	virtual void onNewRequest(void)
	{ }

}; // end of class IReaderListener

}; // end of namespace FEDM

#endif // FEDM_RDR_LISTENER_H

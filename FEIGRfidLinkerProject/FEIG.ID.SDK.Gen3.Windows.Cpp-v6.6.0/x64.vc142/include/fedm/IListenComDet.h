/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_COMDET_LISTENER_H
#define FEDM_COMDET_LISTENER_H

#include "FedmBasic.h"



namespace FEDM {

/// @brief LISTENER for serial COM detection
class FEDM_CLASS_DEF IComDetListener
{
public:
	/// @param[in] connector The actual connetion parameter of the detection test
    ///
    /// This function is called in the same thread in which detectSerial() was called.
	virtual void onTryDetect(Connector connector) { }

}; // end of class ComDetListener

}; // end of namespace FEDM

#endif // FEDM_COMDET_LISTENER_H

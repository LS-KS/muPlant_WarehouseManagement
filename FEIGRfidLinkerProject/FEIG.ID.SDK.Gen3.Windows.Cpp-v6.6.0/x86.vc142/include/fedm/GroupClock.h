/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_CLOCK_H
#define FEDM_GROUP_CLOCK_H

#include "FedmBasic.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief GROUP class for readers date and time settings
class FEDM_CLASS_DEF Clock
{
	friend class ReaderModule;
	
public:
	/// @brief Set readers date and time (command 0x85 or 0x87)
	/// @param[in] dateTime Some reader types do not support date settings
	/// @return #{DOC_LIB_RETURN_VALUE}
	int setSystemClock(const DateTime & dateTime);

	/// @brief Get readers date and time (command 0x86 or 0x88)
	/// @param[out] dateTime Some reader types do not support date settings
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getSystemClock(DateTime & dateTime);

	/// @brief Set readers timezone (command 0x89)
	/// @param[in] timezone New timezone
	/// @return #{DOC_LIB_RETURN_VALUE}
	int setSystemTimezone(const std::string & timezone);

protected:
	Clock();
	~Clock();

	Internal::ReaderBase  *m_rdrBase; // set by a friend

};

}; // end of namespace FEDM

#endif // FEDM_GROUP_CLOCK_H

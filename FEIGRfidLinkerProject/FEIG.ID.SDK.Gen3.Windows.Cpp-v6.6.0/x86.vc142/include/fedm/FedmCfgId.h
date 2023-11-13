/**
*
* Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
*
* This software is the confidential and proprietary information of
* FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
* disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered
* into with FEIG ELECTRONIC GmbH.
*/

#ifndef FEDM_CONFIG_ID_H
#define FEDM_CONFIG_ID_H

#include "FedmBase.h"



namespace FEDM {

/// @brief DATA class with identification information of a configuration value
class FEDM_CLASS_DEF ConfigId
{
	friend class FedmFriend;
public:
	ConfigId(uint32_t id = 0);

	void clear(void) { m_id = 0; }
	
	bool isValid(void) const { return m_id != 0; }
	uint32_t id(void) const { return m_id; }

	int layoutId(void) const;
	int customId(void) const;
	int versionHigh(void) const;
	int versionLow(void) const;

private:
	uint32_t m_id;
};

}; // end of namespace FEDM

#endif // FEDM_CONFIG_ID_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_COM_MANAGER_H
#define FEDM_COM_MANAGER_H

#include <string>
#include <vector>

#include "FedmBasic.h"



namespace FEDM {

/// @brief MANAGER class for serial COM port discovering
class FEDM_CLASS_DEF ComManager
{
public:
	/// @brief Create a list of available COM ports
	///
	/// @param[in] portPrefix:
	/// Under Windows use 'COM', 'com' or an empty string
	/// Under Linux this is something like '/dev/ttyS'
	///
	/// @param[in] fromPortNo, toPortNo:
	/// Under Windows port numbers start at 1.
	/// Under Linux port numbers start at 0.
	///
	/// @param[out] portList A list of available COM ports.
	/// Use these strings as settings for classes Connector and DetectorSerial
	///
	/// @return #{DOC_LIB_ERROR_VALUE}
	static int comPortList(const std::string & portPrefix, int fromPortNo, int toPortNo, std::vector<std::string> & portList);

	static int lastError(void);
	static std::string lastErrorText(void);

}; // end of class ComManger

}; // end of namespace FEDM

#endif // FEDM_COM_MANAGER_H

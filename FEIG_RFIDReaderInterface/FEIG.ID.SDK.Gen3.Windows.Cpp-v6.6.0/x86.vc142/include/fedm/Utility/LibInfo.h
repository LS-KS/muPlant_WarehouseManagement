/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_LIB_INFO_H
#define FEDM_LIB_INFO_H

#include "FedmConst.h"


namespace FEDM {

/// @brief The namespace for utility classes
namespace Utility {

/// @brief Library version dependencies
class FEDM_CLASS_DEF LibInfo
{
public:
	/// @brief Query the version string of FEDM library
	/// @return The version string of FEDM library
	static std::string libVersion(void);

	static int libVersionMajor(void) { return FEDM_VERSION_MAJOR; }
	static int libVersionMinor(void) { return FEDM_VERSION_MINOR; }
	static int libVersionDevel(void) { return FEDM_VERSION_DEVEL; }
	static std::string libVersionRevision(void) { return std::string(FEDM_VERSION_REVISION); }

	/// @brief Check the versions of dependent FEISP library
	/// @return True, if all dependent FEISP library has the expected version, false otherwise
	///
	/// The low level communication libraries are loaded on demand. A version check is automatically performed at load time.
	static bool evaluateLibDependencies(void);

	/// @brief Query a summary version string of the dependent FEISP library
	/// @return A summary version string of the dependent FEISP library
	static std::string getDependentLibVersions(void);

}; // end of class LibInfo

}; // end of namespace Utility

}; // end of namespace FEDM

#endif // FEDM_LIB_INFO_H

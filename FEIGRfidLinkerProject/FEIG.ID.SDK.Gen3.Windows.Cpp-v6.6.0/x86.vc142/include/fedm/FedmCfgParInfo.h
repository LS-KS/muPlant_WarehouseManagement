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

#ifndef FEDM_CONFIG_PARAM_INFO_H
#define FEDM_CONFIG_PARAM_INFO_H

#include "FedmBase.h"



namespace FEDM {

/// @brief DATA class with physical information of a configuration value
///
/// A configuration parameter can be:<br>
/// - An one or multi bit value (we have byte length = 0, bit length > 0)<br>
/// - An one or multi byte value (we have byte length > 0, bit length = 0)<br>
/// In theory the bit length of multi bit values can be more than 8.
class FEDM_CLASS_DEF ConfigParamInfo
{
	friend class FedmFriend;

public:
	ConfigParamInfo();
	ConfigParamInfo(size_t page, size_t startByte, size_t byteLength);
	ConfigParamInfo(size_t page, size_t startByte, size_t startBit, size_t bitLength);

	/// @brief Check the validity of the RssiItem
	/// @return True, if the configuration parameter item is valid
	bool isValid(void) const { return (m_byteLength > 0) || (m_bitLength > 0); }

	/// @return True, if the parameter is a one bit value (bit length = 1)
	bool isBool(void) const { return m_bitLength == 1; }

	/// @return True, if the parameter is a multi bit value (length > 1)
	bool isMultiBit(void) const { return m_bitLength > 1; }

	/// @return True, if the parameter is a one byte value (byte length = 1)
	bool isByte(void) const { return m_byteLength == 1; }

	/// @return True, if the parameter is a multi byte value (length > 1)
	bool isMultiByte(void) const { return m_byteLength > 1; }

	/// @return The configuration page number
	size_t page(void) const { return m_page; }

	/// @return The first byte index of the parameter in the configuration page
	size_t startByte(void) const { return m_startByte; }

	/// @return<br>
	/// \> 0: The byte length of the parameter<br>
	/// = 0: This is an one or multi bit value
	size_t byteLength(void) const { return m_byteLength; }

	/// @return The first bit of the parameter within the start byte
	size_t startBit(void) const { return m_startBit; }

	/// @return<br>
	/// \> 0: The bit length of the parameter<br>
	/// = 0: This is an one or multi byte value
	size_t bitLength(void) const { return m_bitLength; }

private:
	size_t m_page;
	size_t m_startByte;
	size_t m_byteLength;
	size_t m_startBit;
	size_t m_bitLength;
};

}; // end of namespace FEDM

#endif // FEDM_CONFIG_PARAM_INFO_H

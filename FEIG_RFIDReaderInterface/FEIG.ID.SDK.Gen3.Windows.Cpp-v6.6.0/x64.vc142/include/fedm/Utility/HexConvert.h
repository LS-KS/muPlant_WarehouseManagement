/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_HEX_CONVERT_H
#define FEDM_HEX_CONVERT_H

#include <vector>

#include "FedmConst.h"



namespace FEDM {

namespace Utility {

/// @brief Class providing common conversion methods
///
/// All methods of this class are static.
class FEDM_CLASS_DEF HexConvert
{
public:
    /// @brief Convert an unsigned integer value to hex. string
    ///
    /// @param[in] val The unsigned integer value
    /// @param[in] minLength The minimum length of the hex. string. Shorter strings are padded with trailing '0' characters.
    /// @return The hex. string in upper case.
	static std::string toString(uint32_t val, size_t minLength = 0);

    /// @brief Convert a hex. string to an unsigned integer
    ///
    /// @param[in] hexVal The hex. string
    /// @return The unsigned integer value. In case of an error 0 is returned.
	static uint32_t toUInt32(const std::string & hexVal);

    /// @brief Convert a byte vector to a hex. string
    ///
    /// @param[in] vec The byte vector
    /// @param[out] str The hex. string in upper case
    /// @param[in] byteSeparator An optional separator character to put into the hex. string between two consequtive bytes. If 0 no separator character is inserted.
	static void vectorToString(const std::vector<uint8_t> & vec, std::string & str, char byteSeparator = 0);

    /// @brief Convert a hex. string to a byte vector
    ///
    /// @param[in] str The hex. string
    /// @param[out] vec The byte vector
    /// @param[in] byteSeparator An optional check separator character. If 0 the hex. string must not contain separator characters.
    /// @return true: The convertion is successful. All separator characters are matching.<br>
    /// false: The are non hex. characters in the string or there are non matching separator characters.
	static bool stringToVector(const std::string & str, std::vector<uint8_t> & vec, char byteSeparator = 0);

}; // end of class HexConvert

}; // end of namespace Utility

}; // end of namespace FEDM

#endif // FEDM_HEX_CONVERT_H

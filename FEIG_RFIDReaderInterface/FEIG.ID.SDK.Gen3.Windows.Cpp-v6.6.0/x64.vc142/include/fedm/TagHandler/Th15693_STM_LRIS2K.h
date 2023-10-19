/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_STM_LRIS2K_H
#define FEDM_TH_ISO15693_STM_LRIS2K_H

#include "TagHandler/Th15693_STM.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type LRIS2K from manufacturer STMicroelectronics SA
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of LRIS2K. Thus, you must refer to the Technical Datasheet of the LRIS2K to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>STMicroelectronics Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_STM_LRIS2K : public ThIso15693_STM
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA6] Kill
	/// @param[in] killCode 32-bit Kill-Code value
	/// @return #{DOC_LIB_RETURN_VALUE}
	int kill(const std::vector<uint8_t>&  killCode);

	/// @brief Command [0xB1][0xB1] Write Kill
	/// @param[in] killCode 32-bit Kill-Code
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeKill(const std::vector<uint8_t> & killCode);

	/// @brief Command [0xB1][0xB1] Write Password
	/// @param[in] passwordNumber Password number
	/// @param[in] password 32-bit Password or 32-bit Kill code
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writePassword(PasswordNumber passwordNumber, const std::vector<uint8_t> & password);

	/// @brief Command [0xB1][0xB2] Lock Kill
	/// @param[in] protectStatus Protect status
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockKill(uint8_t protectStatus);

	/// @brief Command [0xB1][0xB2] Lock Password
	/// @param[in] passwordNumber Password area
	/// @param[in] protectStatus Protect status
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockPassword(PasswordNumber passwordNumber, uint8_t protectStatus);

	/// @brief Command [0xB1][0xB2] Lock Memory Area
	/// @param[in] blockNumber Block number
	/// @param[in] protectStatus Protect status
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockMemoryArea(size_t blockNumber, uint8_t protectStatus);

	/// @brief Command [0xB1][0xB3] Present Password
	/// @param[in] passwordNumber Password number
	/// @param[in] password 32-bit Password
	/// @return #{DOC_LIB_RETURN_VALUE}
	int presentPassword(PasswordNumber passwordNumber, const std::vector<uint8_t> & password);

	/// @brief The Manufacturer Name is specified with Manufcturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_STM_LRIS2K();

protected:
	ThIso15693_STM_LRIS2K(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_STM_LRIS2K

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_STM_LRIS2K_H

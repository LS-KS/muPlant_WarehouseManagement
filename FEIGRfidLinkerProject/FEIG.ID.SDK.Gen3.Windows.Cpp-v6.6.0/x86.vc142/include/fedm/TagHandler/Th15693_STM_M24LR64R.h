/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_STM_M24LR64R_H
#define FEDM_TH_ISO15693_STM_M24LR64R_H

#include "TagHandler/Th15693_STM.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type M24LR64-R from manufacturer STMicroelectronics SA
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of M24LR64-R. Thus, you must refer to the Technical Datasheet of the M24LR64-R to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>STMicroelectronics Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_STM_M24LR64R : public ThIso15693_STM
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xB1] Write Sector Password
	/// @param[in] passwordNumber
	/// @param[in] password
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeSectorPassword(PasswordNumber passwordNumber, const std::vector<uint8_t>& password);

	/// @brief Command [0xB1][0xB2] Lock Sector Password
	/// @param[in] sectorNumber Number of the sector
	/// @param[in] sectorSecurityStatus Sector security status
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockSectorPassword(size_t sectorNumber, uint8_t sectorSecurityStatus);

	/// @brief Command [0xB1][0xB3] Present Sector Password
	/// @param[in] passwordNumber Password number
	/// @param[in] password 32-bit Password
	/// @return #{DOC_LIB_RETURN_VALUE}
	int presentSectorPassword(PasswordNumber passwordNumber, const std::vector<uint8_t>& password);

	/// @brief The Manufacturer Name is specified with Manufcturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_STM_M24LR64R();

	/// @brief Builder for creating the bit array for the sector security status
	/// @param[in] rw read write protection bits
	/// @param[in] passwordNumber password number
	/// @return sector security status
	static uint8_t createSectorSecurityStatus(size_t rw, PasswordNumber passwordNumber = PasswordNumber::Password_CFG) {
		if(rw < 0 || rw > 4) {
			return 0x00;
		}
		uint8_t securityStatus = static_cast<uint8_t>(rw);

		switch (passwordNumber) {
			case PasswordNumber::Password1:
				return securityStatus | 0x04;
			case PasswordNumber::Password2:
				return securityStatus | 0x08;
			case PasswordNumber::Password3:
				return securityStatus | 0x0C;				
			default:
				return securityStatus;
		}
	}

protected:
	ThIso15693_STM_M24LR64R(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_STM_M24LR64R

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_STM_M24LR64R_H

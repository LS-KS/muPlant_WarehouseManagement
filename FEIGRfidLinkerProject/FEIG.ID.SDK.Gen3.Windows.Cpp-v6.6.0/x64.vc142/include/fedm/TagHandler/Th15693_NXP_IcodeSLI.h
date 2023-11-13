/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_NXP_ICODESLI_H
#define FEDM_TH_ISO15693_NXP_ICODESLI_H

#include "TagHandler/Th15693_NXP.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type I-CODE SLI from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of I-CODE SLI. Thus, you must refer to the Technical Datasheet of the I-CODE SLI to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>NXP Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_NXP_IcodeSLI : public ThIso15693_NXP
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA2]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int setEas();

	/// @brief Command [0xB1][0xA3]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int resetEas();

	/// @brief Command [0xB1][0xA4]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockEas();

	/// @brief Command [0xB1][0xA5]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int easAlarm();

	/// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_NXP_IcodeSLI();

protected:
	ThIso15693_NXP_IcodeSLI(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

	int passwordProtectEas();
	int passwordProtectAfi();
	int writeEasId(const std::vector<uint8_t> & easId);
	int readEpc(std::vector<uint8_t> & epc);
	int getRandomNumber(size_t & randomNo);
	int setPassword(PasswordIdentifier passwordIdentifier, const std::vector<uint8_t> & password);
	int writePassword(PasswordIdentifier passwordIdentifier, const std::vector<uint8_t> & password);
	int lockPassword(PasswordIdentifier passwordIdentifier);
	int protectPage(size_t pageNumber, ProtectionStatus  protectionStatus);
	int protectPageExt(uint8_t ppa, uint8_t extProtectionStatus);
	int lockPageProtectionCondition(size_t pageNumber);
	int getMultipleBlockProtectionStatus(size_t firstDataBlock, size_t noOfDataBlocks, std::vector<uint8_t> & securityStatus);
	int destroy();
	int enablePrivacy();
	int passwordProtection(bool enable);
	int getSystemInformation(SystemInfo & systemInfo);
	int readSignature(std::vector<uint8_t> & signature);

	static const uint8_t CUSTOM_COMMAND = 0xB1;
	static const uint8_t TRANSPARENT_COMMAND = 0xBF;
	static const uint8_t MANUFACTURER_CODE = FEDM::Iec7816_MfrCode::Nxp;

}; // end of class ThIso15693_NXP_ICODESLI

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_NXP_ICODESLI_H

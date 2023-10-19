/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_NXP_ICODESLIX2_H
#define FEDM_TH_ISO15693_NXP_ICODESLIX2_H

#include "TagHandler/Th15693_NXP_IcodeSLIX_L.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type I-CODE SLIX2 from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of I-CODE SLIX2. Thus, you must refer to the Technical Datasheet of the I-CODE SLIX2 to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>NXP Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_NXP_IcodeSLIX2 : public ThIso15693_NXP_IcodeSLIX_L
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA8]
	/// @param[out] epc 
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readEpc(std::vector<uint8_t> & epc);

	/// @brief Command [0xB1][0xAB]
	/// @param[out] protectionPointerAddress Actual protection pointer address
	/// @param[out] protectionConditions Actual protection conditions for the password protection
	/// @param[out] lockBits Actual lock bit settings
	/// @param[out] featureFlags Supported commands and features
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getSystemInformation(ThIso15693_NXP::SystemInfo & systemInfo);

	/// @brief Command [0xB1][0xB6]
	/// @param[in] pageNumber Number of the page
	/// @param[in] extProtectionStatus Extended protection status
	/// @return #{DOC_LIB_RETURN_VALUE}
	int protectPage(uint8_t ppa, uint8_t extProtectionStatus);

	/// @brief Command [0xB1][0xB7]
	/// @param[in] pageNumber
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockPageProtectionCondition(size_t pageNumber);

	/// @brief Command [0xB1][0xBB]
	/// @param[in] passwordParameter
	/// @return #{DOC_LIB_RETURN_VALUE}
	int passwordProtection(bool enable);

	/// @brief Command [0xB1][0xBD]
	/// @param[out] signature
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readSignature(std::vector<uint8_t> & signature);

	/// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_NXP_IcodeSLIX2();

protected:
	ThIso15693_NXP_IcodeSLIX2(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_NXP_ICODESLIX2

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_NXP_ICODESLIX2_H

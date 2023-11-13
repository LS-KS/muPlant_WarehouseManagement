/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_NXP_ICODESLIX_H
#define FEDM_TH_ISO15693_NXP_ICODESLIX_H

#include "TagHandler/Th15693_NXP_IcodeSLI.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type I-CODE SLI from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of I-CODE SLIX. Thus, you must refer to the Technical Datasheet of the I-CODE SLIX to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>NXP Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_NXP_IcodeSLIX : public ThIso15693_NXP_IcodeSLI
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA6]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int passwordProtectEas();

	/// @brief Command [0xB1][0xA6]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int passwordProtectAfi();

	/// @brief Command [0xB1][0xB2]
	/// @param[out] randomNo Random number  
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getRandomNumber(size_t & randomNo);

	/// @brief Command [0xB1][0xB3]
	/// @param[in] passwordIdentifier Password identifier
	/// @param[in] password Password
	/// @return #{DOC_LIB_RETURN_VALUE}
	int setPassword(PasswordIdentifier passwordIdentifier, const std::vector<uint8_t> & password);

	/// @brief Command [0xB1][0xB4]
	/// @param[in] passwordIdentifier Password identifier
	/// @param[in] password Password
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writePassword(PasswordIdentifier passwordIdentifier, const std::vector<uint8_t> & password);

	/// @brief Command [0xB1][0xB5]
	/// @param[in] passwordIdentifier Password identifier
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockPassword(PasswordIdentifier passwordIdentifier);

	/// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_NXP_IcodeSLIX();

protected:
	ThIso15693_NXP_IcodeSLIX(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_NXP_ICODESLIX

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_NXP_ICODESLIX_H

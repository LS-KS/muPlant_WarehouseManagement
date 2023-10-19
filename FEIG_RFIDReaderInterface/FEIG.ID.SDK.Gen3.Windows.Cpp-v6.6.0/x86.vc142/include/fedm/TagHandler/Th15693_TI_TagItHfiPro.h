/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_TI_TAGITHFIPRO_H
#define FEDM_TH_ISO15693_TI_TAGITHFIPRO_H

#include "TagHandler/Th15693_TI.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type Tag-it HFI Pro from manufacturer Texas Instruments
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of Tag-it HF-I Pro. Thus, you must refer to the Technical Datasheet of the Tag-it HF-I Pro to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>TI Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_TI_TagItHfiPro : public ThIso15693_TI
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA4] Kill
	/// @param[in] password Password for execution the function successfully
	/// @return #{DOC_LIB_RETURN_VALUE}
	int kill(const std::vector<uint8_t> & password);

	/// @brief Command [0xB1][0xA5] Write Single Block Password
	/// @param[in] password Password for execution the function successfully
	/// @param[in] dbAddr Address of the data block to be written to the transponder
	/// @param[in] db Data of the data block to be written to the transponder
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeSingleBlockPwd(const std::vector<uint8_t> & password, size_t dbAddr, const std::vector<uint8_t> & db);

	/// @brief The Manufacturer Name is specified with Manufcturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_TI_TagItHfiPro();

protected:
	ThIso15693_TI_TagItHfiPro(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_TITagitHFI_Pro

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_TI_TAGITHFIPRO_H

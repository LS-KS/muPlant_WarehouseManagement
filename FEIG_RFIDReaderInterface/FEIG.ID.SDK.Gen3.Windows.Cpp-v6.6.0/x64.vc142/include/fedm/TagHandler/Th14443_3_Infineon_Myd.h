/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_Infineon_MYD_H
#define FEDM_TH_ISO14443_3_Infineon_MYD_H

#include "TagHandler/Th14443_3.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant Transponders of type my-d from manufacturer Infineon Technologies AG
///
/// High-level class for easy-to-use Transponder specific communication.
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_Infineon_Myd : public ThIso14443_3
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @param[in] keyTagAddress Address where the key is stored in the Transponder. The address can have any value between 4 and 31.
	/// @param[in] authentCounterAddress Address of the Authentication Counter of the Transponder (Default: 0x03).
	/// @param[in] IsEntireCardAuthentication Defines the authentication sequence.<br>
	/// - false: Accelerated card authentication<br>
	/// - true: Entire card authentication<br>
	/// @param[in] keyAddressSam Address of the key in the security access module (SAM). The address can have any value between 1 and 28.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Authentication command
	/// The Authent my-d command is realized with the Reader command [0xB2][0xB1] ISO14443 Special Host Commands.<br>
	int authentication(size_t keyTagAddress,
			size_t authentCounterAddress,
			bool isEntireCardAuthentication,
			size_t keyAddressSam);

	virtual ~ThIso14443_3_Infineon_Myd();

protected:
	ThIso14443_3_Infineon_Myd(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

}; // end of class ThIso14443_3_Infineon_Myd

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_Infineon_MYD_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_NXP_MIFAREULTRALIGHT_H
#define FEDM_TH_ISO14443_3_NXP_MIFAREULTRALIGHT_H

#include "TagHandler/Th14443_3.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant Transponders of type MIFARE Ultralight from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_NXP_MifareUltralight : public ThIso14443_3
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB2] Authenticate
	/// @param[in] readerKeyIndex Reader key index
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// This method is only applicable, if the Transponder is in selected mode.
	int authenticate(uint8_t readerKeyIndex);

	/// @brief Command [0xB5] Get Product Version
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// This method is only applicable, if the Transponder is in selected mode.
	int getVersion(std::vector<uint8_t> & responseData);

	virtual ~ThIso14443_3_NXP_MifareUltralight();

protected:
	ThIso14443_3_NXP_MifareUltralight(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem(), const CardInfo14443 & cardInfo = CardInfo14443());

}; // end of class ThIso14443_3_NXP_MifareUltralight

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_NXP_MIFAREULTRALIGHT_H

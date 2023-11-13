/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_INNOVATRON_H
#define FEDM_TH_ISO14443_INNOVATRON_H

#include "TagHandler/Th14443.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-4 compliant Transponders of type Innovatron (ISO 14443B')
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_Innovatron : public ThIso14443
{
	friend class Internal::ReaderBase;

public:
	const size_t InnovatronApduBufferSize = 2048;

	virtual std::string transponderName() const override;

	/// @return card info byte or 0 in case of error
	///
	/// Command [0xB0][0x25]: Return of Card Info read with last TagSelect call. <br>
	int getCardInfo();

	/// @return Verlog value (negative values are indicating invalid data)
	///
	/// Command [0xB0][0x01]: of Verlog value read with last Inventory call
	int getVerlog();

	/// @return Config value (negative values are indicating invalid data)
	///
	/// Command [0xB0][0x01]: Return of Config value read with last Inventory call
	int getConfig();

	/// @param[out] atr Buffer with ATR
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Command [0xB0][0x01]: Return of ATR value read with last Inventory call.<br>
	int getAtr(std::vector<uint8_t> & atr);

	/// @param[in] requestData Buffer with APDU request
	/// @param[out] responseData Buffer for APDU response
	/// @return #{DOC_LIB_RETURN_VALUE}		
	///
	/// Command [0xB2][0xBB]: APDU command ISO 14443-B.<br>
	int apdu(const std::vector<uint8_t> & requestData, std::vector<uint8_t> & responseData);

	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Command [0xB2][0xBB] Discard.<br>
	int discard();

	virtual ~ThIso14443_Innovatron();

protected:
	ThIso14443_Innovatron(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

}; // end of class ThIso14443_Innovatron

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_INNOVATRON_H

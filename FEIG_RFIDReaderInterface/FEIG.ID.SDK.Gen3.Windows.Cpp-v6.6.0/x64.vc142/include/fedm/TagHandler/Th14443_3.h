/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_H
#define FEDM_TH_ISO14443_3_H

#include "TagHandler/Th14443_2.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing basic commands for all ISO 14443-3 compliant Transponders
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3 : public ThIso14443_2
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// See Reader&apos;s System Manual for detailed information about the method parameters
	int getProtocolInfo(uint8_t & maxFrameSize, uint8_t & protocolType );

	/// @brief Return of Protocol Info, read with last Inventory call
	///
	/// @param[out] maxFrameSize Maximal Frame Size according ISO 14443-3-2001
	/// @param[out] protocolType Protocol Type according ISO 14443-3-2001
	/// @return #{DOC_LIB_RETURN_VALUE}

	/// @brief [0xB2][0xC0] : Halt command (only for selected Transponder)
	///
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// See Reader&apos;s System Manual for detailed information about the command
	int halt();

	virtual ~ThIso14443_3();

protected:
	ThIso14443_3(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

}; // end of class ThIso14443_3

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_H

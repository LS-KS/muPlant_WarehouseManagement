/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_H
#define FEDM_TH_ISO14443_H

#include "TagHandler/ThBase.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing basic commands for all ISO 14443 compliant Transponders
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443 : public ThBase
{
	friend class Internal::ReaderBase;

public:

	/// @brief Return of Card Info, read with last select call of the group hm
	///
	/// @param[out] cardInfoFormat Reference to Format
	/// @param[out] cardInfo Pointer to array for Card Info
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// See Reader&apos;s System Manual for detailed information about the command and the method parameters
	const CardInfo14443 & cardInfo(void) const;

	/// @brief The Manufacturer Name is specified with Manufcturer Code, which is located in byte 1 of the UID
	///
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const;

								
	virtual ~ThIso14443();

protected:
	ThIso14443(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem(), const CardInfo14443 & cardInfo = CardInfo14443());

	CardInfo14443 m_cardInfo;
}; // end of class TH_Base

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_H

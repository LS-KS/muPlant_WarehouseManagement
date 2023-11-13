/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_2_H
#define FEDM_TH_ISO14443_2_H

#include "TagHandler/Th14443.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing basic commands for all ISO 14443-2 compliant Transponders
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_2 : public ThIso14443
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;
	virtual ~ThIso14443_2();

protected:
	ThIso14443_2(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

}; // end of class ThIso14443_2

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_14443_2_H

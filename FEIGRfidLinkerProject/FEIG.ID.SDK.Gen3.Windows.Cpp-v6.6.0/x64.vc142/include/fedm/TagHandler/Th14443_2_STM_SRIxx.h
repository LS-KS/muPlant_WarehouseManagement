/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_2_STM_SRIxx_H
#define FEDM_TH_ISO14443_2_STM_SRIxx_H

#include "TagHandler/Th14443_2.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-2 compliant Transponder of type SRIxxx series from manufacturer STMicroelectronics SA
///
/// High-level class for easy-to-use Transponder specific communication.
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_2_STM_SRIxx : public ThIso14443_2
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;
	virtual ~ThIso14443_2_STM_SRIxx();

protected:
	ThIso14443_2_STM_SRIxx(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

}; // end of class ThIso14443_2_STM_SRIxx

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_2_STM_SRIxx_H

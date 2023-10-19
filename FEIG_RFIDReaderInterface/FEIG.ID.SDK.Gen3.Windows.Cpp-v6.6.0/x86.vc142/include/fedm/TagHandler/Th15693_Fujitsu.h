/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_FUJITSU_H
#define FEDM_TH_ISO15693_FUJITSU_H

#include "TagHandler/Th15693.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders from manufacturer Fujitsu Limited
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_Fujitsu : public ThIso15693
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;
	virtual ~ThIso15693_Fujitsu();

protected:
	ThIso15693_Fujitsu(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_Fujitsu

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_FUJITSU_H

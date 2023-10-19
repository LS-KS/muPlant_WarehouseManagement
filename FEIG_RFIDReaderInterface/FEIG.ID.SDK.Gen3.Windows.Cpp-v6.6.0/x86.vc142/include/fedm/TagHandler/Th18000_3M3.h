/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO18000_3M3_H
#define FEDM_TH_ISO18000_3M3_H

#include "TagHandler/ThEpcC1G2.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing basic commands for all ISO 18000-3M3 compliant Transponders
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the EPC Class 1 Gen 2 standard (<A HREF="http://www.gs1.org/epcglobal">http://www.gs1.org/epcglobal</A>)
/// as ISO 18000-3M3 is based on this standard
class FEDM_CLASS_DEF ThIso18000_3M3 : public ThEpcClass1Gen2
{
	friend class Internal::ReaderBase;

public:


								
	virtual ~ThIso18000_3M3();

protected:
	ThIso18000_3M3(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class TH_Base

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO18000_3M3_H

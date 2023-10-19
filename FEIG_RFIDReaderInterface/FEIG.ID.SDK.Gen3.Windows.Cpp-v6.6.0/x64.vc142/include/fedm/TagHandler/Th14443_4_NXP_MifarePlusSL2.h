/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_4_NXP_MIFAREPlUSSL2_H
#define FEDM_TH_ISO14443_4_NXP_MIFAREPlUSSL2_H

#include "TagHandler/Th14443_4_NXP_MifarePlus.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-4 compliant Transponders of type MIFARE Plus in Security Level 2 from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// This class implements the communication with [0xC2] Reader commands.<br>
/// Detailed description about the command interface can be found in:
/// - Product Datasheet for MIFARE Plus from NXP Semiconductors
/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_4_NXP_MifarePlusSL2 : public ThIso14443_4_NXP_MifarePlus
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	virtual ~ThIso14443_4_NXP_MifarePlusSL2();

protected:
	ThIso14443_4_NXP_MifarePlusSL2(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

}; // end of class ThIso14443_4_NXP_MifarePlusSL2

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_4_NXP_MIFAREPlUSSL2_H

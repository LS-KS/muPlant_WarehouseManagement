/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_NXP_MIFAREPlUSSL1_H
#define FEDM_TH_ISO14443_3_NXP_MIFAREPlUSSL1_H

#include "TagHandler/Th14443_3_NXP_MifarePlus.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant Transponders of type MIFARE Plus in Security Level 1 from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// This class implements the communication with [0xC2] Reader commands.<br>
/// Detailed description about the command interface can be found in:
/// - Product Datasheet for MIFARE Plus from NXP Semiconductors
/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_NXP_MifarePlusSL1: public ThIso14443_3_NXP_MifarePlus
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0x77] MIFARE Plus, realized with Reader command [0xC2][0x77] MFP_SL1_AESAuthent
	/// @param[in] readerKeyIndex Reader key index
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// This method is a Security Level 1 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int aesAuthenticate(uint8_t readerKeyIndex);

	virtual ~ThIso14443_3_NXP_MifarePlusSL1();

protected:
	ThIso14443_3_NXP_MifarePlusSL1(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem(), const CardInfo14443 & cardInfo = CardInfo14443());

}; // end of class ThIso14443_3_NXP_MifarePlusSL1

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_NXP_MIFAREPlUSSL1_H

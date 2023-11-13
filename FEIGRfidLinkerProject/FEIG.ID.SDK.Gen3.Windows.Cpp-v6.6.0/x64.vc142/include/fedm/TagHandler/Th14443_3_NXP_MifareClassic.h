/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_NXP_MIFARECLASSIC_H
#define FEDM_TH_ISO14443_3_NXP_MIFARECLASSIC_H

#include "TagHandler/Th14443_3.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant Transponders of type MIFARE Classic (Mini, 1K, 4K) from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_NXP_MifareClassic : public ThIso14443_3
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @param[in] command First data block address
	/// @param[in] sourceAddress Source address
	/// @param[in] value Value
	/// @param[in] destinationAddress Destination address
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Command [0xB2][0x30] Value command
	int valueCommand(uint8_t command, size_t sourceAddress, uint32_t value, size_t destinationAddress);

	/// @param[in] firstDataBlock First data block address
	/// @param[in] keyType Key type
	/// @param[in] keyAddress Key address
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Command [0xB2][0xB0] Authenticate Mifare with key from Reader&apos;s EEPROM
	/// Read of 4 Blocks (RD4B) command
	int authenticate(size_t firstDataBlock, uint8_t keyType, size_t keyAddress);

	/// @param[in] firstDataBlock First data block address
	/// @param[in] keyType Key type
	/// @param[in] key Authentication key
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	// Command [0xB2][0xB0] Authenticate Mifare with key from protocol
	int authenticate(size_t firstDataBlock, uint8_t keyType, const std::array<uint8_t, 6> & key);

	virtual ~ThIso14443_3_NXP_MifareClassic();

protected:
	ThIso14443_3_NXP_MifareClassic(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem(), const CardInfo14443 & cardInfo = CardInfo14443());

}; // end of class ThIso14443_3_NXP_MifareClassic

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_NXP_MIFARECLASSIC_H

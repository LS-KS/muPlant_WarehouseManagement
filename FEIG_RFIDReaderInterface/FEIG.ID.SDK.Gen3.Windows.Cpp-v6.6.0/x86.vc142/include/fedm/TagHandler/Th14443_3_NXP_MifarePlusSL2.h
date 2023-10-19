/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_NXP_MIFAREPLUSSL2_H
#define FEDM_TH_ISO14443_3_NXP_MIFAREPLUSSL2_H

#include "TagHandler/Th14443_3_NXP_MifarePlus.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant Transponders of type MIFARE Plus in Security Level 2 from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// This class implements the communication with [0xC2] Reader commands.<br>
/// Detailed description about the command interface can be found in:
/// - Product Datasheet for MIFARE Plus from NXP Semiconductors
/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_NXP_MifarePlusSL2 : public ThIso14443_3_NXP_MifarePlus
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0x75], realized with Reader command [0xC2][0x75] MFP_SL2_AESandCRYPTO1Authent
	/// @param[in] dbAddr database address
	/// @param[in] keyType Key type
	/// @param[in] keyNo Key number
	/// @param[in] readerKeyIndex Reader key index
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// This method is a Security Level 2 command.
	int aesAndCrypto1Authenticate(size_t dbAddr, uint8_t keyType, uint8_t keyNo, uint8_t readerKeyIndex);

	/// @brief Command [0x38], realized with Reader command [0xC2][0x38] MFP_SL2_MultiBlockRead
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// This method is a Security Level 2 command.
	int multiBlockRead(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief Command [0xA8], realized with Reader command[0xC2][0xA8] MFP_SL2_MultiBlockWrite
	/// @param[in] firstBlock First block number to be written
	/// @param[in] blockCount Block count
	/// @param[in] requestData Request data
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// This method is a Security Level 2 command.
	int multiBlockWrite(size_t firstBlock, size_t blockCount, const std::vector<uint8_t> & requestData);

	virtual ~ThIso14443_3_NXP_MifarePlusSL2();

protected:
	ThIso14443_3_NXP_MifarePlusSL2(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem(), const CardInfo14443 & cardInfo = CardInfo14443());

}; // end of class ThIso14443_3_NXP_MifarePlusSL2

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_NXP_MIFAREPLUSSL2_H

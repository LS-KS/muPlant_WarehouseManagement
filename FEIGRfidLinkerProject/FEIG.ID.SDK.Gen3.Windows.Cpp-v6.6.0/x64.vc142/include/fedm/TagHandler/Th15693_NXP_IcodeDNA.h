/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_NXP_ICODEDNA_H
#define FEDM_TH_ISO15693_NXP_ICODEDNA_H

#include "TagHandler/Th15693_NXP_IcodeSLI.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type I-CODE DNA from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of I-CODE DNA. Thus, you must refer to the Technical Datasheet of the I-CODE DNA to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>NXP Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_NXP_IcodeDNA : public ThIso15693_NXP_IcodeSLI
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA6]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int passwordProtectEas();

	/// @brief Command [0xB1][0xA6]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int passwordProtectAfi();

	/// @brief Command [0xB1][0xA7]
    /// @param[in] easId New EAS ID that will be stored
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeEasId(const std::vector<uint8_t> & easId);

	/// @brief Command [0xB1][0xB2]
	/// @param[out] randomNo 16 Bit Random Number for password calculation
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getRandomNumber(size_t & randomNo);

	/// @brief Command [0xB1][0xAB]
	/// @param[out] protectionPointerAddress Actual protection pointer address
    /// @param[out] protectionConditions Actual protection conditions for the password protection
	/// @param[in] lockBits Actual lock bit settings
    /// @param[in] featureFlags Supported commands and features
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getSystemInformation(ThIso15693_NXP::SystemInfo & systemInfo);

	/// @brief Command [0xB1][0xB6]
    /// @param[in] ppa Protection pointer address
	/// @param[in] extProtectionStatus Extended protection status
	/// @return #{DOC_LIB_RETURN_VALUE}
	int protectPage(uint8_t ppa, uint8_t extProtectionStatus);

	/// @brief Command [0xB1][0xB7]
	/// @param[in] pageNumber Page number
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockPageProtectionCondition(size_t pageNumber);

	/// @brief Command [0xB1][0xBD]
	/// @param[out] signature
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readSignature(std::vector<uint8_t> & signature);

	/// @brief Command [0xBF][0xC0]: Length of data-array must be 4 x numOfBlocks
	/// @param[in] blockAddr Start block to be read
	/// @param[in] numOfBlocks Number of blocks to be read
	/// @param[out] data Byte container for config data blocks
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readConfig(	size_t blockAddr,
					size_t numOfBlocks,
					std::vector<uint8_t> & data);

	/// @brief Command [0xBF][0xC1]
	/// @param[in] blockAddr Start block to be read
	/// @param[in] data Data to be written
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeConfig(	size_t blockAddr,
						const std::vector<uint8_t> & data);

	/// @brief Command [0xBF][0xC3]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int pickRandomId();

	/// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_NXP_IcodeDNA();

protected:
	ThIso15693_NXP_IcodeDNA(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

private:
	static uint8_t setRequestFlags(uint8_t requestFlags, bool isSelected, bool isNonAddressed ) { 
		if (requestFlags & 0x04) 
		{
			// inventory flag is zero, configure bit 5,6,7,8
			// Bit 5 0x00: AFI Field ist not present 0x10: AFI Field is present 
			// Bit 6 0x00: Nb_slots flag 16 Slots 0x20: 1 Slots 
			// Bit 7 0x00: Option Flag no effect 0x40: no effect
			// Bit 8 0x00: FFU 0x80: FFU		
			requestFlags |= 0x00;	
		}
		else
		{
			// Inventory flag is set, configure bit 5,6,7,8
			// If selected:			Bit 5 0x10: Select Flag every ST25DV64K answers 0x10: only the selected ST25DV64K answers 
			// if non addressed:   	Bit 6 0x00: Address flag The request is executed by all ST25DV64Ks
			// if addressed:       	Bit 6 0x20: Address flag 0x20: UID field is present only the Tag with the UID anwers	
			// Bit 7 0x00: Option not activated  0x40: Option activated 
			// Bit 8 0x00: RFU 0x80: RFU
			if (isSelected)
				requestFlags |= 0x10;   
			else if (isNonAddressed)
				requestFlags |= 0x00;	
			else
				requestFlags |= 0x20;	
		}
		return requestFlags;
	}

}; // end of class ThIso15693_NXP_ICODEDNA

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_NXP_ICODEDNA_H

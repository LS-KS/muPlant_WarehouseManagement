/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_INFINEON_MYDMOVE_H
#define FEDM_TH_ISO14443_3_INFINEON_MYDMOVE_H

#include "TagHandler/Th14443_3.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant Transponders of type my-d move from manufacturer Infineon Technologies AG
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// Detailed description about the command interface can be found in the Product Datasheet for my-d move from Infineon Technologies AG.
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_Infineon_MydMove : public ThIso14443_3
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @param[in] address Address: 0x00...0x25
	/// @param[out] data Data buffer with Transponder data (at least 16 bytes)
	/// @param[in] dataBufferLen Size of the Transponder data buffer
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Read of 4 Blocks (RD4B) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command ISO14443A Transparent Command.<br>
	int read4Blocks(size_t address, std::vector<uint8_t> & data);

	/// @param[in] address Address: 0x02...0x24
	/// @param[out] pucData Data buffer with Transponder data (4 bytes)
	/// @param[in] dataBufferLen Number of bytes in the Transponder data buffer 
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Write of 1 block (WR1B) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command [0xBD] ISO14443A Transparent Command.<br>
	int write1Block(size_t address, const std::vector<uint8_t> & data);
	
	/// @param[in] address
	/// @param[out] data Data buffer with Transponder data (4 bytes)
	/// @param[in] dataBufferLen Number of bytes in the Transponder data buffer
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Compatibility Write (CPTWR) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command [0xBD] ISO14443A Transparent Command.<br>
	int compatibilityWriteCmd(size_t address, const std::vector<uint8_t> & data);

	/// @param[in] address
	/// @param[out] data Data buffer with Transponder data
	/// @param[in] dataBufferLen Size of the Transponder data buffer (at least 8 bytes)
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Read of 2 blocks (RD2B) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command [0xBD] ISO14443A Transparent Command.<br>
	int read2Blocks(size_t address, std::vector<uint8_t> & data);

	/// @param[in] address 
	/// @param[out] data Pointer to buffer with Transponder data (8 bytes)
	/// @param[in] dataBufferLen Number of bytes in the Transponder data buffer
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Write of 2 Blocks (WR2B) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command [0xBD] ISO14443A Transparent Command.<br>
	int write2Blocks(size_t address, const std::vector<uint8_t> & data);

	/// @param[in] password Hex-coded password with even number of chars
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Set Password (SPWD) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command [0xBD] ISO14443A Transparent Command.<br>
	/// Detailed description about the command and the parameters can be found in the Product Datasheet for my-d move from Infineon Technologies AG
	///
	/// @note Hex-coded string means, that a hex value of 0xAB39F1D9 must be set as "AB39F1D9".
	int setPassword(const std::vector<uint8_t> & password);

	/// @param[in] password Hex-coded, 4 byte password
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Access (ACS) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command [0xBD] ISO14443A Transparent Command.<br>
	///
	/// @note Hex-coded string means, that a hex value of 0xAB39F1D9 must be set as "AB39F1D9".
	int access(const std::vector<uint8_t> & password);

	/// @param[in,out] counterValue Value Counter value (LSByte = CNT0, MSByte = CNT1)
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Decrement (DCR16) command
	/// The Transponder must be selected first with function hm().select().<br>
	/// This command is realized with the Reader command [0xBD] ISO14443A Transparent Command.<br>
	int decrement(size_t & counterValue);

	virtual ~ThIso14443_3_Infineon_MydMove();

protected:
	ThIso14443_3_Infineon_MydMove(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());
}; // end of class ThIso14443_3_Infineon_MydMove

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_INFINEON_MYDMOVE_H

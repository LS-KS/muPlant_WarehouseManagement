/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_STM_ST25DVXXK_H
#define FEDM_TH_ISO15693_STM_ST25DVXXK_H

#include "TagHandler/Th15693_STM.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type ST25DVxxK series from manufacturer STMicroelectronics SA
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of M24LRxxE-R. Thus, you must refer to the Technical Datasheet of the ST25DVxxK to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>STMicroelectronics Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_STM_ST25DVxxK : public ThIso15693_STM
{
	friend class Internal::ReaderBase;

public:

	/// Register name
	enum class Pointer : uint8_t {
		GPO = 0x00,
		ITime = 0x01,
		EH = 0x02,
		Rfdis = 0x03,
		RFZ1SS = 0x04,
		End1 = 0x05,
		RFZ2SS = 0x06,
		End2 = 0x07,
		RFZ3SS = 0x08,
		End3 = 0x09,
		RFZ4SS = 0x0A,
		Lock_Ccfile = 0x0C,
		MB_EN = 0x0D,
		MB_WDG = 0x0E,
		Lock_Cfg = 0x0F
	};

	/// Dynamic register pointer address
	enum class PointerAddress : uint8_t {
		GPO_CTRL_Dyn = 0x00,
		EH_CTRL_Dyn = 0x02,
		MB_CTRL_Dyn = 0x0D
	};

	virtual std::string transponderName() const override;

	/// @brief Set of new command response delay value
	/// @param[in] cmdRspDelay Command response delay value
	/// @note Set of command response delay value is only for rare cases.<br>
	/// The command response delay value is preset to 0. This value let the Reader set the optimal value.<br>
	/// Any other value must be multiplicated with 590ns to calculate the command response delay.<br>
	/// Example: 543 * 590ns = 320.9 ?s (which is a typical value).
	void setCommandResponseDelay(size_t cmdRspDelay);

	/// @brief Command [0xB1/0xBF][0xA0] Read Configuration Byte
	/// @param[in] pointer Pointer address
	/// @param[out] data Configuration Byte
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Stores 8 bit value of STATIC configuration register specified by ptrAddr in variable regVal.<br>
	int readCfg(Pointer pointer, uint8_t & data);

	/// @brief Command [0xB1/0xBF][0xA1] Write Configuration Byte
	/// @param[in] pointer Pointer address
	/// @param[in] regVal Configuration Byte
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///  
	/// Writes 8 bit value regVal into STATIC configuration register specified by ptrAddr.<br>
	/// This command must be preceeded by a valid PresentPassword [0xB1/0xBF][0xB3].<br>
	int writeCfg(Pointer pointer, uint8_t regVal);

	/// @brief Command [0xB1/0xBF][0xA9] Manage GPO
	/// @param[in] gpoVal
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Forces GPO output level of transponder depending on gpoVal argument.<br>
	/// Refer to the Application Note <i>DS10925_ST25DV64K_rev04d.pdf</i> for possible values.<br>
	int manageGpo(uint8_t gpoVal);

	/// @brief Command [0xB1/0xBF][0xAA] Write Mail Box Message
	/// @param[in] msg Message data
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Writes message specified by msg to the Mailbox buffer of the transponder.<br>
	int writeMBMsg(const std::vector<uint8_t> & msg);

	/// @brief Command [0xB1/0xBF][0xAB] Read Mail Box Message Length
	/// @param[out] msgLen Length of the mail box message
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Reads total length of message in Mailbox buffer of transponder and stores value in msgLen.<br>
	int readMBMsgLength(size_t & msgLen);

	/// @brief Command [0xB1/0xBF][0xAC] Read Mail Box Message
	/// @param[in] mailBoxAddress Pointer to mail box address (start at 0x00)
	/// @param[in] numberOfBytes Number of bytes to read, if set to 0x00, all bytes of the message are returned.
	/// @param[out] msg Content of the mail box
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Refer to the transponder documentation by STM, where all parameters are described in detail.<br>
	/// If numberOfBytes is set to 0x00, all bytes of the message are returned starting from mailBoxAddress.<br>
	int readMBMsg(uint8_t mailBoxAddress, size_t numberOfBytes, std::vector<uint8_t> & msg);

	/// @brief Command [0xB1/0xBF][0xAD] Read Dynamic Register
	/// @param[in] pointer Dynamic Register Pointer address
	/// @param[out] regVal Register Value
	/// @return #{DOC_LIB_RETURN_VALUE}#
	/// Stores 8 bit value of DYNAMIC configuration register specified by ptrAddr in variable regVal.<br>
	int readDynCfg(PointerAddress ptrAddr, uint8_t & regVal);

	/// @brief Command [0xB1/0xBF][0xAE] Write Dynamic Register
	/// @param[in] pointer Dynamic Register Pointer address
	/// @param[in] regVal Register Value
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Writes 8 bit value regVal into DYNAMIC configuration register specified by ptrAddr.<br>
	int writeDynCfg(PointerAddress ptrAddr, uint8_t regVal);

	/// @brief Command [0xB1/0xBF][0xB1] Write Password
	/// @param[in] passwordNumber Password number
	/// @param[in] password 64-bit Password
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Sets the password specified by passwordNumber to the value of password.<br>
	/// This command must be preceeded by a valid PresentPassword [0xB1/0xBF][0xB3].<br>
	int writePassword(PasswordNumber passwordNumber, const std::vector<uint8_t> & password);

	/// @brief Command [0xB1/0xBF][0xB3] Present Password
	/// @param[in] passwordNumber Password number
	/// @param[in] password 64-bit Password
	/// @return #{DOC_LIB_RETURN_VALUE}
	/// 
	/// Presents password to the transponder depending on passwordNumber.
	int presentPassword(PasswordNumber passwordNumber, const std::vector<uint8_t> & password);

	/// @brief The Manufacturer Name is specified with Manufcturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;


	virtual ~ThIso15693_STM_ST25DVxxK();

protected:
	ThIso15693_STM_ST25DVxxK(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

private:
	int readCfgCust(size_t ptrAddr, uint8_t& regVal);
	int readCfgTransp(size_t ptrAddr, uint8_t& regVal);
	int writeCfgCust(size_t ptrAddr, uint8_t regVal);
	int writeCfgTransp(size_t ptrAddr, uint8_t regVal);
	int manageGpoCust(uint8_t gpoVal);
	int manageGpoTransp(uint8_t gpoVal);
	int writeMBMsgCust(const std::vector<uint8_t>& msg);
	int writeMBMsgTransp(const std::vector<uint8_t>& msg);
	int readMBMsgLengthCust(size_t & msgLen);
	int readMBMsgLengthTransp(size_t & msgLen);
	int readMBMsgCust(size_t mBptrAddr, size_t reqLen, std::vector<uint8_t>& msg);
	int readMBMsgTransp(size_t mBptrAddr, size_t reqLen, std::vector<uint8_t>& msg);
	int readDynCfgCust(size_t ptrAddr, uint8_t& regVal);
	int readDynCfgTransp(size_t ptrAddr, uint8_t& regVal);
	int writeDynCfgCust(size_t ptrAddr, uint8_t regVal);
	int writeDynCfgTransp(size_t ptrAddr, uint8_t regVal);
	int writePasswordCust(uint8_t passwordNumber, const std::vector<uint8_t> password);
	int writePasswordTransp(uint8_t passwordNumber, const std::vector<uint8_t> password);
	int presentPasswordCust(uint8_t passwordNumber, const std::vector<uint8_t> password);
	int presentPasswordTransp(uint8_t passwordNumber, const std::vector<uint8_t> password);

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

	size_t m_cmdRspDelay;

}; // end of class ThIso15693_STM_ST25DVxxK

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_STM_ST25DVXXK_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_EPC_C1G2_H
#define FEDM_TH_EPC_C1G2_H

#include "TagHandler/ThBase.h"



namespace FEDM {
namespace TagHandler {


/// @brief Transponder class providing basic commands for all EPC Class 1 Generation 2 compliant Transponders
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the EPC Class 1 Gen 2 standard (<A HREF="http://www.gs1.org/epcglobal">http://www.gs1.org/epcglobal</A>)
class FEDM_CLASS_DEF ThEpcClass1Gen2 : public ThBase
{
	friend class Internal::ReaderBase;

public:
	enum class Bank : uint8_t {
		Reserved = 0,
		Epc = 1,
		Tid = 2,
		User = 3
	};

	enum class LockParam : uint8_t {
		Unchanged = 0x00,
		Unlock = 0x20,
		UnlockPermanently = 0x31,
		Lock = 0x22,
		LockPermanently = 0x33
	};

	virtual std::string transponderName() const override;

	/// @return The protcol control of the tag
	uint16_t protocolControl(void) const;

	/// @return True if the tag has an extended protcol control, false otherwise
	bool isExtendedProtocolControlW1(void) const;

	/// @return The extended protcol control of the tag
	uint16_t extendedProtocolControlW1();


	/// @return True if IDD contains EPC and TID
	bool isEpcAndTid(void) const;

	/// @return The hex coded string of the IDD
	virtual std::string iddToHexString() const override;

	/// @return The hex coded string of the EPC
	std::string epcToHexString() const;

	/// @return The hex coded string of the TID
	std::string tidToHexString() const;


	/// @return The chip ID for an transponder of EPC Class 1 Gen 2 or ISO 18000 - 3M3 standard
	int tagModelNumber(void) const;

	/// @return The manufacturer ID of EPC Class 1 Gen 2 or ISO 18000 - 3M3 standard
	///
	/// Remark: This can be an EpcC1G2_MaskDesignerId or an Iec7816_MfrCode
	int maskDesignerID(void) const;

	/// @return The manufacturer name for an Transponder of EPC Class 1 Gen 2 or ISO 18000 - 3M3 standard
	std::string maskDesignerName(void) const;

	/// @brief [0xB0][0x23] Read Multiple Blocks command with READ_COMPLETE_BANK option
	/// @param[in] bank Bank number
	/// @param[out] data Vector container for received data blocks
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readCompleteBank(	Bank bank,
							std::vector<uint8_t> & data,
							const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief Basic [0xB0][0x23] Read Multiple Blocks command
	/// @param[in] firstDataBlock First data block address [0..255]
	/// @param[in] noOfDataBlocks Number of requested data blocks [0..255]
	/// @param[out] blockSize Number of bytes in each data block
	/// @param[out] data Byte container for received data blocks
	/// @return #{DOC_LIB_RETURN_VALUE}
	virtual int readMultipleBlocks(
		size_t firstDataBlock,
		size_t noOfDataBlocks,
		size_t & blockSize,
		std::vector<uint8_t> & data) override;

	/// @brief Basic [0xB0][0x24] Write Multiple Blocks command
	/// @param[in] firstDataBlock First data block address [0..255]
	/// @param[in] noOfDataBlocks Number of data blocks to transmit to [0..255]
	/// @param[in] blockSize Number of bytes in each data block
	/// @param[in] data Byte container with data blocks to transmit to
	/// @return #{DOC_LIB_RETURN_VALUE}
	virtual int writeMultipleBlocks(
		size_t firstDataBlock,
		size_t noOfDataBlocks,
		size_t blockSize,
		const std::vector<uint8_t> & data) override;

	/// @brief [0xB0][0x23] Read Multiple Blocks command
	/// @param[in] bank Bank number
	/// @param[in] firstDataBlock First data block address
	/// @param[in] noOfDataBlocks Number of requested data blocks
	/// @param[out] data Vector container for received data blocks
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readMultipleBlocks(	Bank bank,
							size_t firstDataBlock,
							size_t noOfDataBlocks,
							std::vector<uint8_t> & data,
							const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief Basic [0xB0][0x24] Write Multiple Blocks command
	/// @param[in] bank Bank number
	/// @param[in] firstDataBlock First data block address
	/// @param[in] noOfDataBlocks Number of data blocks to transmit to
	/// @param[in] data Vector container for data blocks to transmit to
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeMultipleBlocks(	Bank bank,
								size_t firstDataBlock,
								size_t noOfDataBlocks,
								const std::vector<uint8_t> & data,
								const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief Special [0xB0][0x24] Write Multiple Blocks command to write a new EPC number to the EPC bank of a transponder
	/// @param[in] newEpc Byte vector with the new EPC with even number of bytes.
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeEPC(const std::vector<uint8_t> & newEpc, const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief Basic [0xB3][0x0A] Select a tag subpopulation. See EPC Class 1 Gen 2 standard for detailed information.
	/// @param[in] target Indicates the modified flag: values 0..3 = Inventoried (S0..3), value 4 = SL
	/// @param[in] action Defines the behavior of matching and not matching tags. See documentation for details.
	/// @param[in] bank Memory bank specifies how a tag applies mask
	/// @param[in] maskBitPointer Specifies the starting bit address of the mask
	/// @param[in] maskBitLen Specifies the bit lenght of the mask. The bit lenght must not exceed 255!
	/// @param[in] mask The mask. The length of the vector must be (uiMaskBitLen+7)/8!
	/// @return #{DOC_LIB_RETURN_VALUE}
	int select(	uint8_t target,
				uint8_t action,
				Bank bank,
				size_t maskBitPointer,
				size_t maskBitLen,
				const std::vector<uint8_t> & mask);

	/// @brief The kill command can destroy the Transponder. See EPC Class 1 Gen 2 standard for detailed information, especially how to handle the Kill command with Recommissioning Bits.
	/// @param[in] recomAssertedLsb Recommissioning Bit Asserted LSB (preset: disabled)
	/// @param[in] recomAsserted2sb Recommissioning Bit Asserted 2LSB (preset: disabled)
	/// @param[in] recomAsserted3sb Recommissioning Bit Asserted 3LSB (preset: disabled)
	/// @param[in] password This command needs a password
	/// @return #{DOC_LIB_RETURN_VALUE}
	int kill(	bool recomAssertedLsb,
				bool recomAsserted2sb,
				bool recomAsserted3sb,
				const std::vector<uint8_t> & password);

	/// @brief [0xB3][0x22] Lock command to secure the access to a transponder
	/// @param[in] lockKill lock settings for kill
	/// @param[in] lockAccess lock settings for access pasword
	/// @param[in] lockEPC lock settings for  EPC memory
	/// @param[in] lockTID lock settings for TID memory
	/// @param[in] lockUser lock settings for User memory
	/// @param[in] password This command needs a password
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// The Lock command can lock permanently one bank or multiple banks of the Transponder. See EPC Class 1 Gen 2 standard for detailed information
	int lock(	LockParam lockKill,
				LockParam lockAccess,
				LockParam lockEpc,
				LockParam lockTid,
				LockParam lockUser,
				const std::vector<uint8_t> & password);

	/// @brief This is an optional command and must not be supported by the Transponder
	/// @param[in] bank Bank number
	/// @param[in] blockPointer first block (consider: vendor specific block size)
	/// @param[in] blockRange number of blocks (limited to 4)
	/// @param[in] mask Vector container with mask data to transmit to
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// See EPC Class 1 Gen 2 standard for detailed information.
	int blockPermalock(	Bank bank,
						size_t blockPointer,
						size_t blockRange,
						const std::vector<uint8_t> & mask,
						const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief This is an optional command and must not be supported by the Transponder
	/// @param[in] bank Bank number
	/// @param[in] blockPointer first block (consider: vendor specific block size)
	/// @param[in] blockRange number of blocks (limited to 4)
	/// @param[out] mask Vector container for received mask data
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// See EPC Class 1 Gen 2 standard for detailed information.
	int readPermalockStatus(	Bank bank,
								size_t blockPointer,
								size_t blockRange,
								std::vector<uint8_t> & mask,
								const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief This command hides parts of the tags TID, EPC and/or user memory.
	/// @param[in] uFlag : reserved, should be 0x00
	/// @param[in] hide  : specifies, what to hide (see manual)
	/// @param[in] range : specifies an operating range
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int untraceable(	uint8_t uFlag,
						uint16_t hide,
						uint8_t range,
						const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief This command performs tag, reader, or mutual authentication.
	/// @param[in] authMode Defines the format of the request and the response (see manual).
	/// @param[in] csi Crypto Suite Identifier
	/// @param[in] cryptoTime
	/// @param[in] rspLen
	/// @param[in] message Message defined by the specified crypto suite (see manual).
	/// @param[out] response Vector of the response data.
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int authenticate(	uint8_t authMode,
						uint8_t csi,
						uint8_t cryptoTime,
						const std::vector<uint8_t> & message,
						std::vector<uint8_t> & response,
						const std::vector<uint8_t> & password = std::vector<uint8_t>());

	/// @brief This command allows an interrogator to instruct multiple tags to simultaneously yet independently precompute and store a cryptographic value
	/// @param[in] authMode Defines the format of the request and the response (see manual).
	/// @param[in] csi Crypto Suite Identifier
	/// @param[in] cryptoTime
	/// @param[in] rspLen
	/// @param[in] message Message defined by the specified crypto suite (see manual).
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// No response is send from tag on a challenge command.
	int challenge(	uint8_t authMode,
					uint8_t csi,
					uint8_t cryptoTime,
					const std::vector<uint8_t> & message);

	/// @brief [0xB3][0x33]ReadBuffer: This command allows to read data stored in a tag response buffer.
	/// @param[in] startAddr
	/// @param[in] numOfBits If 0, the entire buffer will be read
	/// @param[out] data The content of the tag response buffer
	/// @param[in] password Optional password. Use an empty vector to disable password.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readBuffer(	size_t startAddr,
					size_t numOfBits,
					std::vector<uint8_t> & data,
					const std::vector<uint8_t> & password = std::vector<uint8_t>());

	virtual ~ThEpcClass1Gen2();

protected:
	ThEpcClass1Gen2(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

	int _readMultipleBlocks(	Bank bank,
								size_t firstDataBlock,
								size_t noOfDataBlocks,
								std::vector<uint8_t> & data,
								const std::vector<uint8_t> & password,
								bool firstData);

	int _writeMultipleBlocks(	Bank bank,
								size_t & firstDataBlock,
								size_t & noOfDataBlocks,
								const std::vector<uint8_t> & data,
								const std::vector<uint8_t> & password,
								size_t & dataIndex);

//	int m_tagModelNumber;
//	int m_maskDesignerID;

}; // end of class TH_EpcClass1Gen2

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_EPC_C1G2_H

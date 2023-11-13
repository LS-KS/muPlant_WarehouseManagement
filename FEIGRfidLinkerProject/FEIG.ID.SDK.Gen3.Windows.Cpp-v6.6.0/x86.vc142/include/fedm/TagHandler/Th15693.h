/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_H
#define FEDM_TH_ISO15693_H

#include "TagHandler/ThBase.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing basic commands for all ISO 15693 compliant Transponders
///
/// High-level class for easy-to-use Transponder specific communication.
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693 : public ThBase
{
	friend class Internal::ReaderBase;

public:
	class FEDM_CLASS_DEF SystemInfo
	{
		friend class ThIso15693;

	public:
		SystemInfo();

		void clear(void);

		/// @brief Returns true, if DSFID value is valid
		bool isValidDsfId(void) const { return (m_infoFlags & 0x01) != 0; }

		/// @brief Returns true, if AFI value is valid
		bool isValidAfi(void) const { return (m_infoFlags & 0x02) != 0; }

		/// @brief Returns true, if VICC memory size (i.e. block size and block count) is valid
		bool isValidMemorySize(void) const { return (m_infoFlags & 0x04) != 0; }

		/// @brief Returns true, if IC reference value is valid
		bool isValidIcReference(void) const { return (m_infoFlags & 0x08) != 0; }

		/// @brief Returns true, if command list is valid
		bool isValidCommandList(void) const { return (m_infoFlags & 0x20) != 0; }

		/// @brief Returns true, if crypto suite IDs are valid
		bool isValidCryptoSuiteIDs(void) const { return (m_infoFlags & 0x40) != 0; }

		uint8_t infoFlags() const { return m_infoFlags; }

		/// @brief Returns the Data Storage Format Identifier of the Transponder
		uint8_t dsfId() const { return m_dsfId; }

		/// @brief Returns the IDD of tag
		const std::vector<uint8_t> & idd() const { return m_idd; }

		/// @brief Get IDD hex string
		/// @return The hex coded string of the IDD
		std::string iddToHexString() const;

		/// @brief Returns the Application Family Identifier
		uint8_t afi() const { return m_afi; }

		/// @brief Returns the block size (part of VICC memory size information)
		size_t blockSize() const { return m_blockSize; }

		/// @brief Returns the block count (part of VICC memory size information)
		size_t blockCount() const { return m_blockCount; }

		/// @brief Returns the IC reference defined by the IC manufacturer
		uint8_t icReference() const { return m_icReference; }

		/// @brief Returns a list with supported commands. Byte 1 is index 0, byte 2 is index 1 and so forth.
		const std::vector<uint8_t> & commandList() const { return m_commandList; }

		/// @brief Returns a list with supported crypto suite IDs
		const std::vector<uint8_t> & cryptoSuiteIds() const { return m_cryptoSuiteIds; }

	private:
		uint8_t m_infoFlags;

		/// @brief Data Storage Format Identifier of the Transponder
		uint8_t m_dsfId;

		/// @brief IDD of tag
		std::vector<uint8_t> m_idd;

		/// @brief Application Family Identifier
		uint8_t m_afi;

		/// @brief block size (part of VICC memory size information)
		size_t m_blockSize;

		/// @brief block count (part of VICC memory size information)
		size_t m_blockCount;

		/// @brief IC reference defined by the IC manufacturer
		uint8_t m_icReference;

		/// @brief list with supported commands. Byte 1 is index 0, byte 2 is index 1 and so forth.
		std::vector<uint8_t> m_commandList;

		/// @brief list with supported crypto suite IDs
		std::vector<uint8_t> m_cryptoSuiteIds;
	}; // end of class SystemInfo



	/// @brief The Manufacturer Name is specified with Manufcturer Code, 
	/// which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	///
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const;

	/// Set response timeout for transparent commands
	void setTransparentResponseTimeout(size_t usec) { m_transparentResponseTimeout = usec; }

	/// @brief [0xB0][0x02] Stay Quiet command
	///
	/// @return #{DOC_LIB_RETURN_VALUE}
	int stayQuiet(void);

	/// @brief Basic [0xB0][0x22] Lock Multiple Blocks command
	/// @param[in] firstDataBlock First data block address [0..255] or [0..65535] with extended address mode
	/// @param[in] noOfDataBlocks Number of data blocks to be locked to [0..255]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockMultipleBlocks(size_t firstDataBlock, size_t noOfDataBlocks);

	/// @brief Extended [0xB0][0x23] Read Multiple Blocks command
	/// @param[in] firstDataBlock First data block address [0..255] or [0..65535] with extended address mode
	/// @param[in] noOfDataBlocks Number of requested data blocks [0..255]
	/// @param[out] blockSize Number of bytes in each data block
	/// @param[out] data Byte container for received data blocks
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readMultipleBlocks(
		size_t firstDataBlock,
		size_t noOfDataBlocks,
		size_t & blockSize,
		std::vector<uint8_t> & data) override;
	
	/// @brief Extended [0xB0][0x23] Read Multiple Blocks command
	/// @param[in] firstDataBlock First data block address [0..255] or [0..65535] with extended address mode
	/// @param[in] noOfDataBlocks Number of requested data blocks [0..255]
	/// @param[out] blockSize Number of bytes in each data block
	/// @param[out] securityStatus Array with received status information, one byte for each data block. The array dimension becomes noOfDataBlocks
	/// @param[out] data Byte container for received data blocks
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readMultipleBlocks(
		size_t firstDataBlock,
		size_t noOfDataBlocks,
		size_t & blockSize,
		std::vector<uint8_t> & securityStatus,
		std::vector<uint8_t> & data );

	/// @brief Extended [0xB0][0x24] Write Multiple Blocks command<br>
	/// @param[in] firstDataBlock First data block address [0..255] or [0..65535] with extended address mode
	/// @param[in] noOfDataBlocks Number of data blocks to transmit to [0..255]
	/// @param[in] blockSize Number of bytes in each data block
	/// @param[in] data Byte container with data blocks to transmit to
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeMultipleBlocks(
		size_t firstDataBlock,
		size_t noOfDataBlocks,
		size_t blockSize,
		const std::vector<uint8_t> & data) override;

	/// @brief [0xB0][0x26] : Reset To Ready command
	///
	/// @return #{DOC_LIB_RETURN_VALUE}
	int resetToReady(void);

	/// @brief [0xB0][0x27] Write AFI command
	///
	/// @param[in] afi AFI value
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeAFI(uint8_t afi);

	/// @brief [0xB0][0x28] Lock AFI command
	///
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockAFI(void);

	/// @brief [0xB0][0x29] Write DSFID command
	///
	/// @param[in] dsfId DSFID value
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeDsfId(uint8_t dsfId);

	/// @brief [0xB0][0x2A] Lock DSFID command
	///
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockDsfId(void);

	/// @brief Basic [0xB0][0x2B] Get System Information command
	///
	/// @param[out] systemInfo reference to a class with returned system information
	/// @param[in] isExtended If true then return the extended system information
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getSystemInformation(SystemInfo & systemInfo, bool isExtended);

	/// @brief Basic [0xB0][0x2C] Get Multiple Block Security Status command
	///
	/// @param[in] firstDataBlock First data block address [0..255] or [0..65535] with extended address mode
	/// @param[in] noOfDataBlocks Number of data blocks to be locked to [0..255]
	/// @param[out] securityStatus Array with received status information, one byte for each data block. The array dimension becomes noOfDataBlocks
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getMultipleBlockSecurityStatus(	size_t firstDataBlock,
										size_t noOfDataBlocks,
										std::vector<uint8_t> & securityStatus);

	/// @brief [0xB0][0x35] Authenticate. This command performs tag, reader, or mutual authentication.
	///
	/// @param[in] authMode Defines the format of the request and the response (see manual).
	/// @param[in] csi Crypto Suite Identifier
	/// @param[in] cryptoTime
	/// @param[in] rspLen
	/// @param[in] msg Message defined by the specified crypto suite (see manual).
	/// @param[out] rsp Vector of the response data.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int authenticate(	uint8_t authMode,
						uint8_t csi,
						uint8_t cryptoTime,
						size_t  rspLen,
						const std::vector<uint8_t> & msg,
						std::vector<uint8_t> & rsp);
	
	/// @brief [0xB0][0x39] Challenge
	/// @param[in] authMode Defines the format of the request and the response (see manual).
	/// @param[in] csi Crypto Suite Identifier
	/// @param[in] cryptoTime
	/// @param[in] rspLen
	/// @param[in] msg Message defined by the specified crypto suite (see manual).
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This command allows an interrogator to instruct multiple tags to simultaneously yet independently precompute and store a cryptographic value.
	/// No response is send from tag on a challenge command.
	int challenge(	uint8_t authMode,
					uint8_t csi,
					uint8_t cryptoTime,
					size_t  rspLen,
					const std::vector<uint8_t> & msg);

	/// @brief [0xB0][0x3A] Read Buffer. This command allows to read data stored in a tag response buffer.
	/// @param[out] sata The content of the tag response buffer
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readBuffer(std::vector<uint8_t> & data);

	/// @brief General implementation of the [0xBF] transparent command
	/// @param[in] mode          Mode (Bit0..3 = Options, Bit7 = TxCRCEnab, all other bits are RFU and must be set to zero)
	/// @param[in] rspBitLen     Length of the transponder response in bits without SOF and EOF
	///	@param[in] cmdRspDelay	 Response delay for transponder response
	/// @param[in] eofPulseDelay EOF pulse delay        (only for options 3,4)
	/// @param[in] multiGrids    Multiple 302µs grids   (only for option 5)
	/// @param[in] reqData       Request data
	/// @param[out] rspData      Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	int transparentCommand(	uint8_t mode,
							size_t  rspBitLen,
							size_t  cmdRspDelay,
							size_t  eofPulseDelay,
							size_t  multiGrids,
							const std::vector<uint8_t> & reqData,
							std::vector<uint8_t> & rspData);
								
	virtual ~ThIso15693();

protected:
	ThIso15693(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

	int initPaylRequestForTransparentCommand_BF(
		uint8_t mode,
		size_t  rspBitLen,
		size_t  cmdRspDelay,
		size_t  eofPulseDelay,
		size_t  multiGrids);

	size_t m_transparentResponseTimeout;

}; // end of class TH_Base

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_H

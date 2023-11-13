/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_BASE_H
#define FEDM_TH_BASE_H

#include "FedmBasic.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief The namespace of all tag handler classes
namespace TagHandler {

/// @brief Base class of all tag handler classes
class FEDM_CLASS_DEF ThBase
{
	friend class Internal::ReaderBase;
	friend class FedmFriend;

public:
	static const uint32_t TypeBase = 1; ///< Identifier for Base TagHandler class
	static const uint32_t TypeEpcClass1Gen2 = 10; ///< Identifier for Transponder class for EPC Class1 Generation2
	static const uint32_t TypeIso14443 = 20; ///< Identifier for ISO 14443 Transponder class
	static const uint32_t TypeIso14443_Innovatron = 21; ///< Identifier for ISO 14443-4 Transponder class, with extension for Innovatron (ISO 14443B')
	static const uint32_t TypeIso14443_2 = 30; ///< Identifier for ISO 14443-2 Transponder class
	static const uint32_t TypeIso14443_2_Innovision_Jewel = 31; ///< Identifier for ISO 14443-2 Transponder class, with extension for Innovision Jewel
	static const uint32_t TypeIso14443_2_STM_SR176 = 32; ///< Identifier for ISO 14443-2 Transponder class, with extension for SR176 of manufacturer STMicroelectronics SA
	static const uint32_t TypeIso14443_2_STM_SRIxx = 33; ///< Identifier for ISO 14443-2 Transponder class, with extension for SRIxx series of manufacturer STMicroelectronics SA
	static const uint32_t TypeIso14443_3 = 40; ///< Identifier for ISO 14443-3 Transponder class
	static const uint32_t TypeIso14443_3_Infineon_Myd = 41; ///< Identifier for ISO 14443-3 Transponder class, with extensions for my-d move of Manufacturer Infineon Technologies AG
	static const uint32_t TypeIso14443_3_Infineon_MydMove = 42; ///< Identifier for ISO 14443-3 Transponder class, with extensions for my-d move of Manufacturer Infineon Technologies AG
	static const uint32_t TypeIso14443_3_NXP_MifareClassic = 43; ///< Identifier for ISO 14443-3 Transponder class, with extensions for MIFARE Classic (Mini, 1K, 4K) of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso14443_3_NXP_MifareUltralight = 44; ///< Identifier for ISO 14443-3 Transponder class, with extensions for MIFARE Ultralight of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso14443_3_NXP_MifarePlusSL1 = 45; ///< Identifier for ISO 14443-3 Transponder class, with extensions for MIFARE Plus in Security Level 1 of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso14443_3_NXP_MifarePlusSL2 = 46; ///< Identifier for ISO 14443-3 Transponder class, with extensions for MIFARE Plus in Security Level 2 of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso14443_3_ASK_CTx = 47; ///< Identifier for ISO 14443-3 Transponder class, with extensions for CTx series of Manufacturer ASK
	static const uint32_t TypeIso14443_4 = 50; ///< Identifier for ISO 14443-4 Transponder class
	static const uint32_t TypeIso14443_4_NXP_MifareDesfire = 51; ///< Identifier for ISO 14443-4 Transponder class, with extensions for MIFARE DESFire of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso14443_4_NXP_MifarePlusSL1 = 52; ///< Identifier for ISO 14443-4 Transponder class, with extensions for MIFARE Plus in Security Level 1 of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso14443_4_NXP_MifarePlusSL2 = 53; ///< Identifier for ISO 14443-4 Transponder class, with extensions for MIFARE Plus in Security Level 2 of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso14443_4_NXP_MifarePlusSL3 = 54; ///< Identifier for ISO 14443-4 Transponder class, with extensions for MIFARE Plus in Security Level 3 of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso18000_3M3 = 100; ///< Identifier for Transponder class for ISO 18000-3M3
	static const uint32_t TypeIso15693 = 0xE0000000; ///< ISO 15693 Transponder class
	static const uint32_t TypeIso15693_STM = 0xE0020000; ///< Identifier for ISO 15693 Transponder class, with extensions for Manufacturer STMicroelectronics SA
	static const uint32_t TypeIso15693_STM_LRI2K = 0xE0022000; ///< Identifier for ISO 15693 Transponder class, with extensions for LRI2K of Manufacturer STMicroelectronics SA
	static const uint32_t TypeIso15693_STM_LRIS2K = 0xE0020280; ///< Identifier for ISO 15693 Transponder class, with extensions for LRIS2K of Manufacturer STMicroelectronics SA
	static const uint32_t TypeIso15693_STM_LRIS64K = 0xE0020440; ///< Identifier for ISO 15693 Transponder class, with extensions for LRIS64K of Manufacturer STMicroelectronics S
	static const uint32_t TypeIso15693_STM_M24LR64R = 0xE00202C0; ///< Identifier for ISO 15693 Transponder class, with extensions for M24LR64-R of Manufacturer STMicroelectronics SA
	static const uint32_t TypeIso15693_STM_M24LRxxER = 0xE00205C0; ///< Identifier for ISO 15693 Transponder class, with extensions for M24LRxxE-R series of Manufacturer STMicroelectronics SA
	static const uint32_t TypeIso15693_STM_ST25DVxxK = 0xE0022400; ///< Identifier for ISO 15693 Transponder class, with extensions for ST25DVxxK series of Manufacturer STMicroelectronics SA
	static const uint32_t TypeIso15693_NXP = 0xE0040000; ///< Identifier for ISO 15693 Transponder class, with extensions for Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeSLI = 0xE0040100; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE SLI of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeSLIX = 0xE0040110; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE SLIX of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeSLIX2 = 0xE0040108; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE SLIX2 of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeSLI_L = 0xE0040300; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE SLI-L of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeSLIX_L = 0xE0040310; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE SLIX-L of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeSLI_S = 0xE0040200; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE SLI-S of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeSLIX_S = 0xE0040210; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE SLIX-S of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_NXP_IcodeDNA = 0xE0040118; ///< Identifier for ISO 15693 Transponder class, with extensions for I-CODE DNA of Manufacturer NXP Semiconductors
	static const uint32_t TypeIso15693_Infineon = 0xE0050000; ///< Identifier for ISO 15693 Transponder class, with extensions for Manufacturer Infineon Technologies AG
	static const uint32_t TypeIso15693_Infineon_Myd = 0xE005FFFF; ///< Identifier for ISO 15693 Transponder class, with extensions for my-d of Manufacturer Infineon Technologies AG
	static const uint32_t TypeIso15693_TI = 0xE0070000; ///< Identifier for ISO 15693 Transponder class, with extensions for Manufacturer Texas Instruments
	static const uint32_t TypeIso15693_TI_TagItHfiPro = 0xE007E000; ///< Identifier for ISO 15693 Transponder class, with extensions for Tag-it HFI Pro of Manufacturer Texas Instruments
	static const uint32_t TypeIso15693_TI_TagItHfiPlus = 0xE0078000; ///< Identifier for ISO 15693 Transponder class, with extensions for Tag-it HFI Plus of Manufacturer Texas Instruments
	static const uint32_t TypeIso15693_Fujitsu = 0xE0080000; ///< Identifier for ISO 15693 Transponder class, with extensions for Manufacturer Fujitsu Limited
	static const uint32_t TypeIso15693_Fujitsu_MB89R1xx = 0xE0080001; ///< Identifier for ISO 15693 Transponder class, with extensions for MB89R1xx series of Manufacturer Fujitsu Limited
	static const uint32_t TypeIso15693_EM = 0xE0160000; ///< Identifier for ISO 15693 Transponder class, with extensions for Manufacturer EM Microelectronic-Marin SA
	static const uint32_t TypeIso15693_EM_EM4034 = 0xE0160004; ///< Identifier for ISO 15693 Transponder class, with extensions for EM4034 of Manufacturer EM Microelectronic-Marin SA


	/// @brief Get the tag handler type identifier
	/// @return The tag handler type identifier (ThBase::Type...)
	uint32_t tagHandlerType() const { return m_tagHandlerType; }

	/// @brief Get the transponder type
	/// @return The transponder type (see class TransponderType)
	int transponderType() const { return m_tagItem.trType(); }

	/// @brief Get the transponder type as readable string
	/// @return The transponder name as string
	virtual std::string transponderName() const;

	/// @brief Get IDD
	/// @return The raw byte data of the IDD
	const std::vector<uint8_t> & idd() const { return m_tagItem.idd(); }

	/// @brief Get IDD hex. string
	/// @return The tag IDD as hex coded string
	virtual std::string iddToHexString() const { return m_tagItem.iddToHexString(); }

	/// @brief Get RSSI values
	/// @return A vector of RssiItem-values. There are items for those antennas, where the transponder could be detected.
	const std::vector<RssiItem> & rssiValues(void) const { return m_tagItem.rssiValues(); }
	
	/// @brief Check if tag handler is in non addressed mode
	/// @return True if tag is in non addressed mode, false otherwise
	bool isNonAddressed() const;

	/// @brief Check if tag handler is in addressed mode
	/// @return True if tag is in addressed mode, false otherwise
	bool isAddressed() const;

	/// @brief Check if tag handler is in selected mode
	/// @return True if tag is in selected mode, false otherwise
	bool isSelected() const;

	/// @brief Get last transponder ISO error code
	/// @return The last transponder ISO error (see reader manual or ISO documentation)
	int lastIsoError() const;

	/// @brief Get transponder data block address after an error
	/// @return Transponder data block address after an error
	size_t errorDBAddress() const { return m_errorDbAddress; }

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
		std::vector<uint8_t> & data);
	
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
		const std::vector<uint8_t> & data);

	/// @brief To copy a ThBase is not allowed
    ThBase(ThBase& other) = delete;

    /// @brief To copy a ThBase is not allowed
    ThBase(const ThBase& other) = delete;

    /// @brief To copy a ThBase is not allowed
    ThBase& operator=(ThBase& other) = delete;

    /// @brief To copy a ThBase is not allowed
    ThBase& operator=(const ThBase& other) = delete;

	virtual ~ThBase();

protected:
	ThBase(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

	const TagItem & tagItem(void) const { return m_tagItem; }
	bool setTagSelected(void);

	int  setLastError(int error);
	int  setLastIsoError(int error);
	virtual void resetErrors(void);

	virtual int  transceive(void);
	virtual int  transceiveAndCheckIsoError(void);
	int transceiveAndCheckIsoError_BF(void); // For transparent command 0xBF

	int _readMultipleBlocks(
		size_t firstDataBlock,
		size_t noOfDataBlocks,
		size_t & blockSize,
		std::vector<uint8_t> & data,
		bool firstData);

	int _writeMultipleBlocks(
		size_t & firstDataBlock,
		size_t & noOfDataBlocks,
		size_t blockSize,
		const std::vector<uint8_t> & data,
		size_t & blockIndex);

	uint32_t  m_tagHandlerType;
	TagItem   m_tagItem;

	Internal::ReaderBase *m_readerBase;
	Logger::FedmLogger   *m_logger;
	Payload::PlBuf       *m_buf;

	/* Address mode setting for m_tag:
	 *
	 * Nonaddressed: if tagItem.isValid() returns false
	 * Addressed   : if tagItem.isValid() returns true
	 * Selected    : if setTagSelected() returns true, i.e. tagItem.isValid() returns true
	 */
	Internal::ThTag *m_tag;

	size_t m_errorDbAddress;

}; // end of class TH_Base

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_BASE_H

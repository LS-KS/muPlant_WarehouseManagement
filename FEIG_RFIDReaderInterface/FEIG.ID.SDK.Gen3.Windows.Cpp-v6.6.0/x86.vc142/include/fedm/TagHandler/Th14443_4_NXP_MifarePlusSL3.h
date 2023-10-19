/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_4_NXP_MIFAREPlUSSL3_H
#define FEDM_TH_ISO14443_4_NXP_MIFAREPlUSSL3_H

#include "TagHandler/Th14443_4_NXP_MifarePlus.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-4 compliant Transponders of type MIFARE Plus in Security Level 3 from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// This class implements the communication with [0xC2] Reader commands.<br>
/// Detailed description about the command interface can be found in:
/// - Product Datasheet for MIFARE Plus from NXP Semiconductors
/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_4_NXP_MifarePlusSL3 : public ThIso14443_4_NXP_MifarePlus
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief MIFARE Plus Command [0x78], realized with Reader command [0xC2][0x78] SL3 Reset Authent
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int resetAuthentication();

	/// @brief MIFARE Plus Command [0x30], realized with Reader command [0xC2][0x30] SL3 Read Encrypted
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readEncrypted(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0x31], realized with Reader command [0xC2][0x31] SL3 Read Encrypted Maced
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readEncryptedMaced(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0x32], realized with Reader command [0xC2][0x32] SL3 Read Plain
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readPlain(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0x33], realized with Reader command [0xC2][0x33] SL3 Read Plain Maced
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readPlainMaced(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0x34], realized with Reader command [0xC2][0x34] SL3 Read Encrypted Unmaced
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readEncryptedUnmaced(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0x35], realized with Reader command [0xC2][0x35] SL3 Read Encrypted Unmaced Respond Maced
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readEncryptedUnmacedRespondMaced(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0x36], realized with Reader command [0xC2][0x36] SL3 Read Plain Unmaced
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readPlainUnmaced(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0x37], realized with Reader command [0xC2][0x37] SL3 Read Plain Unmaced Respond Maced
	/// @param[in] firstBlock First block number to be read
	/// @param[in] blockCount Block count
	/// @param[out] responseData Response data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int readPlainUnmacedRespondMaced(size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);

	/// @brief MIFARE Plus Command [0xA0], realized with Reader command [0xC2][0xA0] SL3 Write Encrypted
	/// @param[in] firstBlock First block number to be written
	/// @param[in] blockCount Block count
	/// @param[in] requestData Request data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int writeEncrypted(size_t firstBlock, size_t blockCount, const std::vector<uint8_t> & requestData);

	/// @brief MIFARE Plus Command [0xA1], realized with Reader command [0xC2][0xA1] SL3 Write Encrypted Maced
	/// @param[in] firstBlock First block number to be written
	/// @param[in] blockCount Block count
	/// @param[in] requestData Request data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int writeEncryptedMaced(size_t firstBlock, size_t blockCount, const std::vector<uint8_t> & requestData);

	/// @brief MIFARE Plus Command [0xA2], realized with Reader command [0xC2][0xA2] SL3 Write Plain
	/// @param[in] firstBlock First block number to be written
	/// @param[in] blockCount Block count
	/// @param[in] requestData Request data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int writePlain(size_t firstBlock, size_t blockCount, const std::vector<uint8_t> & requestData);

	/// @brief MIFARE Plus Command [0xA3], realized with Reader command [0xC2][0xA3] SL3 Write Plain Maced
	/// @param[in] firstBlock First block number to be written
	/// @param[in] blockCount Block count
	/// @param[in] requestData Request data
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int writePlainMaced(size_t firstBlock, size_t blockCount, const std::vector<uint8_t> & requestData);

	/// @brief MIFARE Plus Command [0xB0], realized with Reader command [0xC2][0xB0] SL3 Increment Encrypted
	/// @param[in] sourceBlock Block number of the value to be incremented
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int incrementEncrypted(size_t sourceBlock, uint32_t data); 

	/// @brief MIFARE Plus Command [0xB1], realized with Reader command [0xC2][0xB1] SL3 Increment Encrypted Maced
	/// @param[in] sourceBlock Block number of the value to be incremented
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int incrementEncryptedMaced(size_t sourceBlock, uint32_t data); 

	/// @brief MIFARE Plus Command [0xB2], realized with Reader command [0xC2][0xB2] SL3 Decrement Encrypted
	/// @param[in] sourceBlock Block number of the value to be decremented
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int decrementEncrypted(size_t sourceBlock, uint32_t data); 

	/// @brief MIFARE Plus Command [0xB3], realized with Reader command [0xC2][0xB3] SL3 Decrement Encrypted Maced
	/// @param[in] sourceBlock Block number of the value to be decremented
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int decrementEncryptedMaced(size_t sourceBlock, uint32_t data); 

	/// @brief MIFARE Plus Command [0xB4], realized with Reader command [0xC2][0xB4] SL3 Transfer
	/// @param[in] destinationBlock Block number of the destination block
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int transfer(size_t destinationBlock);

	/// @brief MIFARE Plus Command [0xB5], realized with Reader command [0xC2][0xB5] SL3 Transfer Maced
	/// @param[in] destinationBlock Block number of the destination block
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int transferMaced(size_t destinationBlock);

	/// @brief MIFARE Plus Command [0xB6], realized with Reader command [0xC2][0xB6] SL3 Increment Transfer Encrypted
	/// @param[in] sourceBlock Block number of the source block
	/// @param[in] destinationBlock Block number of the destination block
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int incrementTransferEncrypted(size_t sourceBlock, size_t destinationBlock, uint32_t data);

	/// @brief MIFARE Plus Command [0xB7], realized with Reader command [0xC2][0xB7] SL3 Increment Transfer Encrypted Maced
	/// @param[in] sourceBlock Block number of the source block
	/// @param[in] destinationBlock Block number of the destination block
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int incrementTransferEncryptedMaced(size_t sourceBlock, size_t destinationBlock, uint32_t data);

	/// @brief MIFARE Plus Command [0xB8], realized with Reader command [0xC2][0xB8] SL3 Decrement Transfer Encrypted
	/// @param[in] sourceBlock Block number of the source block
	/// @param[in] destinationBlock Block number of the destination block
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int decrementTransferEncrypted(size_t sourceBlock, size_t destinationBlock, uint32_t data);

	/// @brief MIFARE Plus Command [0xB9], realized with Reader command [0xC2][0xB9] SL3 Decrement Transfer Encrypted Maced
	/// @param[in] sourceBlock Block number of the source block
	/// @param[in] destinationBlock Block number of the destination block
	/// @param[in] data 4 bytes value
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int decrementTransferEncryptedMaced(size_t sourceBlock, size_t destinationBlock, uint32_t data);

	/// @brief MIFARE Plus Command [0xC2], realized with Reader command [0xC2][0xC2] SL3 Restore
	/// @param[in] sourceBlock Block number of the source block
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int restore(size_t sourceBlock);

	/// @brief MIFARE Plus Command [0xC3], realized with Reader command [0xC2][0xC3] SL3 Restore Maced
	/// @param[in] sourceBlock Block number of the source block
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is a Security Level 3 command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int restoreMaced(size_t sourceBlock);

	virtual ~ThIso14443_4_NXP_MifarePlusSL3();

protected:
	ThIso14443_4_NXP_MifarePlusSL3(Internal::ReaderBase* readerBase, const TagItem & tagItem = TagItem(), const CardInfo14443 & cardInfo = CardInfo14443());

private:
	int _read (uint8_t command, size_t firstBlock, size_t blockCount, std::vector<uint8_t> & responseData);
	int _write(uint8_t command, size_t firstBlock, size_t blockCount, const std::vector<uint8_t> & requestData);
	int _count(uint8_t command, size_t sourceBlock, uint32_t data); // Increment and Decrement
	int _transfer(uint8_t command, size_t destinationBlock);
	int _restore (uint8_t command, size_t sourceBlock);
	int _countAndTransfer(uint8_t command, size_t sourceBlock, size_t destinationBlock, uint32_t data);

}; // end of class ThIso14443_4_NXP_MifarePlusSL3

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_4_NXP_MIFAREPlUSSL3_H

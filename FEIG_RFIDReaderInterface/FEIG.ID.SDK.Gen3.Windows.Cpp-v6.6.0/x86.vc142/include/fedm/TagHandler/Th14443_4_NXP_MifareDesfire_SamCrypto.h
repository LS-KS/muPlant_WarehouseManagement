/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_SAMCRYPTO_H
#define FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_SAMCRYPTO_H

#include "TagHandler/Th14443_4.h"



namespace FEDM {
namespace TagHandler {

class FEDM_CLASS_DEF ThIso14443_4_NXP_MifareDesfire_SamCrypto
{
	friend class ThIso14443_4_NXP_MifareDesfire;

public:

	/// @param[in] timeout Timeout value in milliseconds (only positive values are allowed)
	///
	/// Adjust timeout for Reader internal communication.
	/// In case the timeout is higher than the host receive timeout, the host receive timeout for this request is adjusted automatically
	/// 
	void setTimeout(int timeoutMilliseconds);

	/// Returns the current timeout (by default 90% of the current host receive timeout)
	///
	/// @returns the current SAM timeout (value in steps of 100ms)
	int timeout();

	//####################################################################
	// 5 security related commands

	/// @param[in] samSlotNo
	/// @param[in] desFireAuthMode
	/// @param[in] desFireKeyNo
	/// @param[in] samAuthMode
	/// @param[in] samKeyNo
	/// @param[in] samKeyVersion
	/// @param[in] samDiversificationInput
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x0A] Authenticate or [0x1A] AuthenticateISO or [0xAA] AuthenticateAES, realized with Reader command [0xC1][0xFA] Authent
	/// The explicite Authenticate method is defined by the Key, previously stored in the Reader with the Reader command [0xA3] Write DES/AES Reader Keys.<br>
	/// This method is a security related command.<br>
	int authenticate(uint8_t samSlotNo,
			uint8_t desFireAuthMode,
			uint8_t desFireKeyNo,
			uint8_t samAuthMode,
			uint8_t samKeyNo,
			uint8_t samKeyVersion,
			const std::vector<uint8_t> & divInput);
	
	/// @param[in] samSlotNo
	/// @param[in] newKeySettings
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x54] Change Key Settings, realized with Reader command [0xC3][0x54]
	/// This method is a security related command.<br>
	int changeKeySettings(uint8_t samSlotNo, uint8_t newKeySettings);
	
	/// @param[in] samSlotNo
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x45] Get Key Settings, realized with Reader command [0xC3][0x45]
	/// This method is a security related command.<br>
	int getKeySettings(uint8_t samSlotNo, std::vector<uint8_t> & responseData);

	/// @param[in] samSlotNo
	/// @param[in] samKeyCompilationMethod
	/// @param[in] samCfg
	/// @param[in] samKeyNoCurrentKey
	/// @param[in] samKeyVersionCurrentKey
	/// @param[in] samKeyNoNewKey
	/// @param[in] samKeyVersionNewKey
	/// @param[in] samDiversificationInput
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC4] Change Key, realized with Reader command [0xC3][0xC4].<br>
	/// This method is a security related command.<br>
	int changeKey(uint8_t samSlotNo,
			uint8_t samKeyCompilationMethod,
			uint8_t samCfg,
			uint8_t samKeyNoCurrentKey,
			uint8_t samKeyVersionCurrentKey,
			uint8_t samKeyNoNewKey,
			uint8_t samKeyVersionNewKey,
			const std::vector<uint8_t> & samDiversificationInput);

	/// @param[in] samSlotNo	
	/// @param[in] desFireKeyNo
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x64] Get Key Version, realized with Reader command [0xC3][0x64].<br>
	/// This method is a security related command.<br>
	int getKeyVersion(uint8_t samSlotNo, uint8_t desFireKeyNo, std::vector<uint8_t> & pucResponseData);


	//####################################################################
	// 10 PICC level commands

	/// @param[in] applicationId
	/// @param[in] keySetting1
	/// @param[in] keySetting2
	/// @param[in] isoFileId
	/// @param[in] dfName
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xCA] Create Application, realized with Reader command [0xC3][0xCA]
	/// This method is a PICC level related command.<br>
	int createApplication(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			uint32_t applicationId,
			uint8_t keySetting1,
			uint8_t keySetting2,
			uint16_t isoFileId,
			const std::string & dfName);

	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags,
	/// @param[in] applicationId
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xDA] Delete Application, realized with Reader command [0xC3][0xDA].<br>
	/// This method is a PICC level related command.<br>
	int deleteApplication(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			uint32_t applicationId);
	
	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6A] Get Application IDs, realized with Reader command [0xC3][0x6A].<br>
	/// This method is a PICC level related command.<br>
	int getApplicationIds(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			std::vector<uint8_t> & responseData);

	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6E] Free Memory, realized with Reader command [0xC3][0x6E].<br>
	/// This method is a PICC level related command.<br>
	int freeMemory(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			std::vector<uint8_t> & responseData);

	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6D] Get DF-Names, realized with Reader command [0xC3][0x6D].<br>
	/// This method is a PICC level related command.<br>
	int getDfNames(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			std::vector<uint8_t> & responseData);
	
	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags
	/// @param[in] applicationId
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x5A] Select Application, realized with Reader command [0xC3][0x5A].<br>
	/// This method is a PICC level related command.<br>
	int selectApplication(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			uint32_t applicationId);

	/// @param[out] samSlotNo
	/// @param[out] piccLevelFlags
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xFC] Format PICC, realized with Reader command [0xC3][0xFC].<br>
	/// This method is a PICC level related command.<br>
	int formatPicc(uint8_t samSlotNo, uint8_t piccLevelFlags);

	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x60] Get Version, realized with Reader command [0xC3][0x60].<br>
	/// This method is a PICC level related command.<br>
	int getVersion(uint8_t samSlotNo, uint8_t piccLevelFlags, std::vector<uint8_t> & responseData);

	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x51] Get Card-UID, realized with Reader command [0xC3][0x51].<br>
	/// This method is a PICC level related command.<br>
	int getCardUid(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			std::vector<uint8_t> & responseData);
	
	/// @param[in] samSlotNo
	/// @param[in] piccLevelFlags
	/// @param[in] requestData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x5C] Set Configuration, realized with Reader command [0xC3][0x5C].<br>
	/// This method is a PICC level related command.<br>
	int setConfiguration(uint8_t samSlotNo,
			uint8_t piccLevelFlags,
			const std::vector<uint8_t> & requestData);

	//####################################################################
	// 10 application level commands

	/// @param[in] samSlotNo
	/// @param[in] applicationLevelFlags
	/// @param[in] fileNo
	/// @param[in] newFileCommSettings
	/// @param[in] newFileReadWriteAccessRights
	/// @param[in] newFileChangeAccessRights
	/// @param[in] newFileReadAccessRights
	/// @param[in] newFileWriteAccessRights
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x5F] Change File Settings, realized with Reader command [0xC3][0x5F].<br>
	/// This method is an application level related command.<br>
	int changeFileSettings(uint8_t samSlotNo,
			uint8_t applicationLevelFlags,
			uint8_t fileNo,
			uint8_t newFileCommSettings,
			uint8_t newFileReadWriteAccessRights,
			uint8_t newFileChangeAccessRights,
			uint8_t newFileReadAccessRights,
			uint8_t newFileWriteAccessRights);

	/// @param[in] samSlotNo
	/// @param[in] applicationLevelFlags
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6F] Get File IDs, realized with Reader command [0xC3][0x6F].<br>
	/// This method is an application level related command.<br>
	int getFileIds(uint8_t samSlotNo,
			uint8_t applicationLevelFlags,
			std::vector<uint8_t> & responseData);

	/// @param[in] fileNo
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xF5] Get File Settings, realized with Reader command [0xC3][0x5F].<br>
	/// This method is an application level related command.<br>
	int getFileSettings(uint8_t samSlotNo,
			uint8_t applicationLevelFlags,
			uint8_t fileNo,
			std::vector<uint8_t> & responseData);

	/// @param[in] samSlotNo
	/// @param[in] applicationLevelFlags
	/// @param[in] fileNo
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] fileSize
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xCD] Create StdDataFile, realized with Reader command [0xC3][0xCD].<br>
	/// This method is an application level related command.<br>
	int createStdDataFile(uint8_t samSlotNo,
			uint8_t applicationLevelFlags,
			uint8_t fileNo,
			uint16_t isoFileId,
			uint8_t fileCommSettings,
			uint8_t fileReadWriteAccessRights,
			uint8_t fileChangeAccessRights,
			uint8_t fileReadAccessRights,
			uint8_t fileWriteAccessRights,
			size_t fileSize);

	/// @param[in] samSlotNo
	/// @param[in] applicationLevelFlags
	/// @param[in] fileNo
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] fileSize
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xCB] Create BackupDataFile, realized with Reader command [0xC3][0xCB].<br>
	/// This method is an application level related command.<br>
	int createBackupDataFile(uint8_t samSlotNo,
				uint8_t applicationLevelFlags,
				uint8_t fileNo,
				uint16_t isoFileId,
				uint8_t fileCommSettings,
				uint8_t fileReadWriteAccessRights,
				uint8_t fileChangeAccessRights,
				uint8_t fileReadAccessRights,
				uint8_t fileWriteAccessRights,
				size_t fileSize);

	/// @param[in] samSlotNo
	/// @param[in] applicationLevelFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] lowerLimit
	/// @param[in] upperLimit
	/// @param[in] value
	/// @param[in] limitedCreditEnabled
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xCC] Create ValueFile, realized with Reader command [0xC3][0xCC].<br>
	/// This method is an application level related command.<br>
	int createValueFile(uint8_t samSlotNo,
			uint8_t applicationLevelFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint8_t fileReadWriteAccessRights,
			uint8_t fileChangeAccessRights,
			uint8_t fileReadAccessRights,
			uint8_t fileWriteAccessRights,
			int32_t lowerLimit,
			int32_t upperLimit,
			int32_t value,
			uint8_t limitedCreditEnabled);

	/// @param[in] samSlotNo
	/// @param[in] applicationLevelFlags
	/// @param[in] fileNo
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] recordSize
	/// @param[in] maxNoOfRecords
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC1] Create LinearRecordFile, realized with Reader command [0xC3][0xC1].<br>
	/// This method is an application level related command.<br>
	int createLinearRecordFile( uint8_t samSlotNo,
				uint8_t applicationLevelFlags,
				uint8_t fileNo,
				uint16_t isoFileId,
				uint8_t fileCommSettings,
				uint8_t fileReadWriteAccessRights,
				uint8_t fileChangeAccessRights,
				uint8_t fileReadAccessRights,
				uint8_t fileWriteAccessRights,
				size_t recordSize,
				size_t maxNoOfRecords);

	/// @param[in] samSlotNo
	/// @param[in] applicationLevelFlags
	/// @param[in] fileNo
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] recordSize
	/// @param[in] maxNoOfRecords
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC0] Create CyclicRecordFile, realized with Reader command [0xC3][0xC0].<br>
	/// This method is an application level related command.<br>
	int createCyclicRecordFile(uint8_t samSlotNo,
				uint8_t applicationLevelFlags,
				uint8_t fileNo,
				uint16_t isoFileId,
				uint8_t fileCommSettings,
				uint8_t fileReadWriteAccessRights,
				uint8_t fileChangeAccessRights,
				uint8_t fileReadAccessRights,
				uint8_t fileWriteAccessRights,
				size_t recordSize,
				size_t maxNoOfRecords);

	/// @param[in] fileNo
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xDF] DeleteFile, realized with Reader command [0xC3][0xDF].<br>
	/// This method is an application level related command.<br>
	int deleteFile(uint8_t samSlotNo,
				uint8_t applicationLevelFlags,
				uint8_t fileNo);

	/// @param[out] responseData			
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x61] Get ISOFile IDs, realized with Reader command [0xC3][0x61].<br>
	/// This method is an application level related command.<br>
	int getIsoFileIds(uint8_t samSlotNo,
				uint8_t applicationLevelFlags,
				std::vector<uint8_t> & responseData);

	//####################################################################
	// 11 data manipulation commands
	
	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] fileOffset
	/// @param[in] fileLen
	/// @param[out] fileData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xBD] Read Standard Data, realized with Reader command [0xC1][0xBD].<br>
	/// This method is a data manipulation related command.<br>
	int readStandardData(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			 size_t fileOffset,
			 size_t fileLen,
			std::vector<uint8_t> & fileData);
	
	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] fileOffset,
	/// @param[in] fileData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x3D] Write Standard Data, realized with Reader command [0xC1][0x3D].<br>
	/// This method is a data manipulation related command.<br>
	int writeStandardData(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			size_t fileOffset,
			const std::vector<uint8_t> & fileData);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[out] value
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6C] Get Value, realized with Reader command [0xC3][0x6C].<br>
	/// This method is a data manipulation related command.<br>
	int getValue(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint32_t & value);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] creditValue
	///r @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x0C] Credit, realized with Reader command [0xC1][0x0C].<br>
	/// This method is a data manipulation related command.<br>
	int credit(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint32_t creditValue);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] debitValue
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xDC] Debit, realized with Reader command [0xC1][0xDC].<br>
	/// This method is a data manipulation related command.<br>
	int debit(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint32_t debitValue);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] creditValue
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x1C] Limited Credit, realized with Reader command [0xC1][0x1C].<br>
	/// This method is a data manipulation related command.<br>
	int limitedCredit(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint32_t creditValue);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] fileOffset
	/// @param[in] recordData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x3B] Write Record, realized with Reader command [0xC3][0x3B].<br>
	/// This method is a data manipulation related command.<br>
	int writeRecord(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			size_t fileOffset,
			const std::vector<uint8_t> & recordData);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] recordOffset
	/// @param[in] noOfRecords
	/// @param[in] recordSize
	/// @param[out] recordData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xBB] Read Records, realized with Reader command [0xC3][0xBB].<br>
	/// This method is a data manipulation related command.<br>
	int readRecords(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			size_t recordOffset,
			size_t noOfRecords,
			size_t recordSize,
			std::vector<uint8_t> & recordData);


	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xEB] Clear Record File, realized with Reader command [0xC3][0xEB].<br>
	/// This method is a data manipulation related command.<br>
	int clearRecordFile(uint8_t samSlotNo,
			uint8_t dataManipulationFlags,
			uint8_t fileNo,
			uint8_t fileCommSettings);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC7] Commit Transaction, realized with Reader command [0xC3][0xC7].<br>
	/// This method is a data manipulation related command.<br>
	int commitTransaction(uint8_t samSlotNo, uint8_t ucDataManipulationFlags);

	/// @param[in] samSlotNo
	/// @param[in] dataManipulationFlags
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xA7] Abort Transaction, realized with Reader command [0xC3][0xA7].<br>
	/// This method is a data manipulation related command.<br>
	int abortTransaction(uint8_t samSlotNo, uint8_t ucDataManipulationFlags);

	virtual ~ThIso14443_4_NXP_MifareDesfire_SamCrypto();

private:
	ThIso14443_4_NXP_MifareDesfire_SamCrypto(ThIso14443_4_NXP_MifareDesfire_ImplC3 **mifareDesfireImplC3, Internal::ReaderBase *readerBase);

	uint8_t getSamTimeout();
	int calculateHostReceiveTimeout();

	ThIso14443_4_NXP_MifareDesfire_ImplC3 **m_mifareDesfireImplC3;
	Internal::ReaderBase *m_readerBase;
	unsigned int m_timeoutMs = 4000;

	// virtual ~ThIso14443_4_NXP_MifareDesfire_SamCrypto();
}; // end of class ThIso14443_4_NXP_MifareDesfire_SamCrypto

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_SAMCRYPTO_H

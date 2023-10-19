/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_SOFTCRYPTO_H
#define FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_SOFTCRYPTO_H

#include "TagHandler/Th14443_4_NXP_MifareDesfire.h"

namespace FEDM {
namespace TagHandler {

class FEDM_CLASS_DEF ThIso14443_4_NXP_MifareDesfire_SoftCrypto
{
public:
	friend class ThIso14443_4_NXP_MifareDesfire;

	//####################################################################
	// 5 security related commands

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x0A] Authenticate or [0x1A] AuthenticateISO or [0xAA] AuthenticateAES, realized with Reader command [0xC1][0xFA] Authent.<br>
	/// The explicite Authenticate method is defined by the Key, previously stored in the Reader with the Reader command [0xA3] Write DES/AES Reader Keys.<br>
	/// This method is a security related command.<br>
	int authenticate(uint32_t applicationId, uint8_t readerKeyIndex, uint8_t desFireKeyNo);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] newKeySettings
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x54] Change Key Settings, realized with Reader command [0xC3][0x54].<br>
	/// This method is a security related command.<br>
	int changeKeySettings(uint32_t applicationId, uint8_t readerKeyIndex, uint8_t newKeySettings);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x45] Get Key Settings, realized with Reader command [0xC3][0x45]-<br>
	/// This method is a security related command.<br>
	int getKeySettings(std::vector<uint8_t> & responseData);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] keyNoToBeChanged
	/// @param[in] aesNewKeyVersion
	/// @param[in] oldKey
	/// @param[in] newKey
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC4] Change Key, realized with Reader command [0xC3][0xC4]
	/// This method is a security related command.<br>
	int changeKey(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t keyNoToBeChanged,
			uint8_t aesNewKeyVersion,
			const std::vector<uint8_t> & oldKey,
			const std::vector<uint8_t> & newKey);

	/// @param[in] desFireKeyNo
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// DESFire command [0x64] Get Key Version, realized with Reader command [0xC3][0x64].<br>
	/// This method is a security related command.
	int getKeyVersion(uint8_t desFireKeyNo,
			std::vector<uint8_t> & responseData);

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
	int createApplication(uint32_t applicationId,
			uint8_t keySetting1, uint8_t keySetting2,
			uint16_t isoFileId,
			const std::string & dfName,
			std::vector<uint8_t> & responseData);
	
	/// @param[in] applicationId
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xDA] Delete Application, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int deleteApplication(uint32_t applicationId, std::vector<uint8_t> & responseData);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6A] Get Application IDs, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int getApplicationIds(std::vector<uint8_t> & responseData);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6E] Free Memory, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int freeMemory(std::vector<uint8_t> & responseData);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6D] Get DF-Names, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int getDfNames(std::vector<uint8_t> & responseData);
	
	/// @param[in] applicationId
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x5A] Select Application, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int selectApplication(uint32_t applicationId, std::vector<uint8_t> & responseData);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xFC] Format PICC, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int formatPicc(std::vector<uint8_t> & responseData);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x60] Get Version, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int getVersion(std::vector<uint8_t> & responseData);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x51] Get Card-UID, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int getCardUid(std::vector<uint8_t> & responseData);

	/// @param[in] requestData
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x5C] Set Configuration, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a PICC level related command.<br>
	int setConfiguration(const std::vector<uint8_t> & requestData, std::vector<uint8_t> & responseData);

	//####################################################################
	// 10 application level commands

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] newFileCommSettings
	/// @param[in] newFileReadWriteAccessRights
	/// @param[in] newFileChangeAccessRights
	/// @param[in] newFileReadAccessRights
	/// @param[in] newFileWriteAccessRights
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x5F] Change File Settings, realized with Reader command [0xC1][0x5F].<br>
	/// This method is an application level related command.<br>
	int changeFileSettings(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,	uint8_t newFileCommSettings,
			uint8_t newFileReadWriteAccessRights,
			uint8_t newFileChangeAccessRights,
			uint8_t newFileReadAccessRights,
			uint8_t newFileWriteAccessRights);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6F] Get File IDs, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int getFileIds(std::vector<uint8_t> & responseData);

	/// @param[in] fileNo
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xF5] Get File Settings, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int getFileSettings(uint8_t fileNo, std::vector<uint8_t> & responseData );

	/// @param[in] fileNo
	/// @param[in] withIsoFileId
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] fileSize
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xCD] Create StdDataFile, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int createStdDataFile(uint8_t fileNo,
			bool withIsoFileId,
			uint16_t isoFileId,
			uint8_t fileCommSettings,
			uint8_t fileReadWriteAccessRights,
			uint8_t fileChangeAccessRights,
			uint8_t fileReadAccessRights,
			uint8_t fileWriteAccessRights,
			size_t fileSize,
			std::vector<uint8_t> & responseData);

	/// @param[in] fileNo
	/// @param[in] withIsoFileId
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] fileSize
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xCB] Create BackupDataFile, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int createBackupDataFile(uint8_t fileNo,
			bool withISOFileID,
			uint16_t isoFileID,
			uint8_t fileCommSettings,
			uint8_t fileReadWriteAccessRights,
			uint8_t fileChangeAccessRights,
			uint8_t fileReadAccessRights,
			uint8_t fileWriteAccessRights,
			size_t fileSize,
			std::vector<uint8_t> & responseData);

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
	/// @param[out] responseData	
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xCC] Create ValueFile, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int createValueFile(uint8_t fileNo,
			uint8_t fileCommSettings,
			uint8_t fileReadWriteAccessRights,
			uint8_t fileChangeAccessRights,	uint8_t fileReadAccessRights,
			uint8_t fileWriteAccessRights,
			int32_t lowerLimit,
			int32_t upperLimit,
			int32_t value,
			uint8_t limitedCreditEnabled,
			std::vector<uint8_t> & responseData);

	/// @param[in] fileNo
	/// @param[in] withIsoFileId
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] recordSize
	/// @param[in] maxNoOfRecords
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC1] Create LinearRecordFile, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int createLinearRecordFile(uint8_t fileNo,
			bool withIsoFileId,	uint16_t isoFileId,
			uint8_t fileCommSettings,
			uint8_t fileReadWriteAccessRights,
			uint8_t fileChangeAccessRights,
			uint8_t fileReadAccessRights,
			uint8_t fileWriteAccessRights,
			size_t recordSize,
			size_t maxNoOfRecords,
			std::vector<uint8_t> & responseData);

	/// @param[in] fileNo
	/// @param[in] withIsoFileId
	/// @param[in] isoFileId
	/// @param[in] fileCommSettings
	/// @param[in] fileReadWriteAccessRights
	/// @param[in] fileChangeAccessRights
	/// @param[in] fileReadAccessRights
	/// @param[in] fileWriteAccessRights
	/// @param[in] recordSize
	/// @param[in] maxNoOfRecords
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC0] Create CyclicRecordFile, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int createCyclicRecordFile(uint8_t fileNo,
			bool withIsoFileId,
			uint16_t isoFileId,
			uint8_t fileCommSettings,
			uint8_t fileReadWriteAccessRights,
			uint8_t fileChangeAccessRights,
			uint8_t fileReadAccessRights,
			uint8_t fileWriteAccessRights,
			size_t recordSize,
			size_t maxNoOfRecords,
			std::vector<uint8_t> & responseData);

	/// @param[in] fileNo
	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xDF] DeleteFile, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int deleteFile(uint8_t fileNo, std::vector<uint8_t> & responseData );

	/// @param[out] responseData			
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x61] Get ISOFile IDs, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is an application level related command.<br>
	int getIsoFileIds(std::vector<uint8_t> & responseData);

	//####################################################################
	// 11 data manipulation commands
	
	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[out] fileData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xBD] Read Standard Data, realized with Reader command [0xC1][0xBD].<br>
	/// This method is a data manipulation related command.<br>
	int readStandardData(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			size_t fileOffset,
			size_t fileLen,
			std::vector<uint8_t> & fileData);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] fileData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x3D] Write Standard Data, realized with Reader command [0xC1][0x3D].<br>
	/// This method is a data manipulation related command.<br>
	int writeStandardData(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			size_t fileOffset,
			const std::vector<uint8_t> & fileData);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[out] value
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x6C] Get Value, realized with Reader command [0xC1][0x6C].<br>
	/// This method is a data manipulation related command.<br>
	int getValue(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint32_t & value);


	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] creditValue
	///r @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x0C] Credit, realized with Reader command [0xC1][0x0C].<br>
	/// This method is a data manipulation related command.<br>
	int credit(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint32_t creditValue);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] debitValue
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xDC] Debit, realized with Reader command [0xC1][0xDC].<br>
	/// This method is a data manipulation related command.<br>
	int debit(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,	uint8_t fileCommSettings,
			uint32_t debitValue);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] creditValue
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x1C] Limited Credit, realized with Reader command [0xC1][0x1C].<br>
	/// This method is a data manipulation related command.<br>
	int limitedCredit(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			uint32_t creditValue);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[in] fileOffset
	/// @param[in] recordData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0x3B] Write Record, realized with Reader command [0xC1][0x3B].<br>
	/// This method is a data manipulation related command.<br>
	int writeRecord(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			size_t fileOffset,
			const std::vector<uint8_t> & recordData);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @param[out] recordData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xBB] Read Records, realized with Reader command [0xC1][0xBB].<br>
	/// This method is a data manipulation related command.<br>
	int readRecords(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings,
			size_t recordOffset,
			size_t noOfRecords,
			size_t recordSize,
			std::vector<uint8_t> & recordData);

	/// @param[in] applicationId
	/// @param[in] readerKeyIndex
	/// @param[in] desFireKeyNo
	/// @param[in] fileNo
	/// @param[in] fileCommSettings
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xEB] Clear Record File, realized with Reader command [0xC1][0xEB].<br>
	/// This method is a data manipulation related command.<br>
	int clearRecordFile(uint32_t applicationId,
			uint8_t readerKeyIndex,
			uint8_t desFireKeyNo,
			uint8_t fileNo,
			uint8_t fileCommSettings);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xC7] Commit Transaction, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a data manipulation related command.<br>
	int commitTransaction(std::vector<uint8_t> & responseData);

	/// @param[out] responseData
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// DESFire command [0xA7] Abort Transaction, realized with Reader command [0xB2][0xBE] T=CL %APDU for synchronous call.<br>
	/// This method is a data manipulation related command.<br>
	int abortTransaction(std::vector<uint8_t> & responseData);

	virtual ~ThIso14443_4_NXP_MifareDesfire_SoftCrypto();

private:
	ThIso14443_4_NXP_MifareDesfire_SoftCrypto(ThIso14443_4_NXP_MifareDesfire_ImplC1 **mifareDesfireImplC1);

	ThIso14443_4_NXP_MifareDesfire_ImplC1 **m_mifareDesfireImplC1;

}; // end of class ThIso14443_4_NXP_MifareDesfire_SoftCrypto

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_SOFTCRYPTO_H

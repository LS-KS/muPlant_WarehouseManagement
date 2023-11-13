/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TAG_ITEM_H
#define FEDM_TAG_ITEM_H

#include <string>
#include <vector>
#include <map>
#include <array>

#include "FedmConst.h"
#include "FedmRssiItem.h"



namespace FEDM {

/// @brief DATA class with fundamental transponder information
class FEDM_CLASS_DEF TagItem
{
	friend class Internal::ReaderBase;
	friend class Payload::PlBase;
//	friend class TagHandler::ThBase;
	friend class TagEventItem;
	friend class FedmFriend;

public:
/** @name Main
 */
///@{					
	TagItem();

	/// @brief Set all values to invalid (.i.e. all int-values to -1)
	void clear();

	/// @brief Check the validity of the TagItem
	/// @return True, if the TagItem values are valid
	bool isValid() const { return m_trType >= 0; }

	/// @brief Get the transponder type
	/// @return The transponder type (see class TransponderType)
	int  trType()  const { return m_trType; }
	
	bool isIcode1()        const { return m_trType == FEDM::TransponderType::Icode1; }
	bool isIso15693()      const { return m_trType == FEDM::TransponderType::Iso15693; }
	bool isIso14443A()     const { return m_trType == FEDM::TransponderType::Iso14443A; }
	bool isIso14443B()     const { return m_trType == FEDM::TransponderType::Iso14443B; }
	bool isJewel()         const { return m_trType == FEDM::TransponderType::Jewel; }
	bool isIso18000_3M3()  const { return m_trType == FEDM::TransponderType::Iso18000_3M3; }
	bool isStmSR176()      const { return m_trType == FEDM::TransponderType::StmSR176; }
	bool isStmSRIx()       const { return m_trType == FEDM::TransponderType::StmSRIxx; }
	bool isFelica()        const { return m_trType == FEDM::TransponderType::Felica; }
	bool isInnovatron()    const { return m_trType == FEDM::TransponderType::Innovatron; }
	bool isAskCtx()        const { return m_trType == FEDM::TransponderType::AskCTx; }
	bool isEM4222()        const { return m_trType == FEDM::TransponderType::Em4222; }
	bool isEpcClass1Gen2() const { return m_trType == FEDM::TransponderType::EpcClass1Gen2; }
	bool isBarcode()       const { return m_trType == FEDM::TransponderType::Barcode; }

	/// @brief Get IDD
	/// @return The raw byte data of the IDD
	const std::vector<uint8_t> & idd() const { return m_idd; }

	/// @brief Get IDD hex. string
	/// @return The hex coded string of the IDD
	std::string iddToHexString() const;

	/// @brief Get RSSI values
	/// @return A vector of RssiItem-values. There are items for those antennas, where the transponder could be detected.
	const std::vector<FEDM::RssiItem> & rssiValues() const { return m_rssiValues; }

	/// @brief Get the IEC7816 manufacturer code of ISO15693 and ISO14443 transponder
	/// @return The IEC7816 manufacturer code<br>
	/// If the transponder type is neither ISO15693 nor ISO14443 compliant -1 is returned
	int iec7816_MfrCode(void) const;

	/// @brief Get the manufacturer name of ISO15693 and ISO14443 transponder
	/// @return The manufacturer name of the transponder<br>
	/// If the transponder type is neither ISO15693 nor ISO14443 compliant an empty string is returned
	std::string manufacturerName(void) const;

///@}

/** @name For ISO15693, ICODE1
 */
///@{
	bool iso15693_IsValidAfi() const { return m_iso15693_Afi >= 0; }
	int  iso15693_Afi() const { return m_iso15693_Afi; }
	int  iso15693_DsfId() const { return m_iso15693_DsfId; }

	int iso15693_TagStatus() const { return m_iso15693_TagStatus; }
	int iso15693_NewAfi() const { return m_iso15693_NewAfi; }
///@}

/** @name For ISO18000_3M3, EpcClass1Gen2
 */
///@{					
	bool        epcC1G2_IsExtendedPC_W1(void) const;
	int         epcC1G2_TagModelNumber(void) const;   ///< The chip ID for a transponder of EPC Class 1 Gen 2 or ISO 18000-3M3 standard (only available if isEpcAndTid() returns true)
	int         epcC1G2_MaskDesignerID(void) const;   ///< The manufacturer ID of EPC Class 1 Gen 2 or ISO 18000-3M3 standard or the IEC7816 Manufactorer Code (only available if isEpcAndTid() returns true)
	std::string epcC1G2_MaskDesignerName(void) const;

	int      epcC1G2_IddType() const { return m_epcC1G2_IddType; }
	uint16_t epcC1G2_Pc() const { return m_epcC1G2_Pc; }
	uint16_t epcC1G2_XpcW1() const { return m_epcC1G2_XpcW1; }

	/// @return True if IDD contains EPC and TID
	bool epcC1G2_IsEpcAndTid() const { return m_epcC1G2_IddType == 0x02; }

	/// @return The hex coded string of the EPC
	std::string epcC1G2_EpcToHexString() const;

	/// @return The hex coded string of the TID
	std::string epcC1G2_TidToHexString() const;

	std::vector<uint8_t> epcC1G2_EpcFromIdd(void) const;
	std::vector<uint8_t> epcC1G2_TidFromIdd(void) const;
///@}

/** @name For ISO14443A
 */
///@{					
	int iso14443A_TrInfo() const { return m_iso14443A_TrInfo; }
	int iso14443A_OptInfo() const { return m_iso14443A_OptInfo; }
///@}

/** @name For ISO14443B
 */
///@{					
	int iso14443B_ProtocolInfo() const { return m_iso14443B_ProtocolInfo; }
///@}

/** @name For SR176, SRIx
 */
///@{					
	int sr_ChipId() const { return m_sr_ChipId; }
///@}

/** @name For Innovatron
 */
///@{					
	int innovatron_Verlog() const { return m_innovatron_Verlog; }
	int innovatron_Config() const { return m_innovatron_Config; }
	const std::vector<uint8_t> & innovatron_Atr() const { return m_innovatron_Atr; }
///@}

/** @name For ASK_CTx
 */
///@{					
	int askCtx_ProductCode() const { return m_askCtx_ProductCode; }
	int askCtx_FabCode() const { return m_askCtx_FabCode; }
	int askCtx_AppCode() const { return m_askCtx_AppCode; }
	int askCtx_EmbedderCode() const { return m_askCtx_EmbedderCode; }
///@}

private:
	std::vector<uint8_t> m_idd;    ///< The IDD of the transponder
	int                  m_trType; ///< The transponder type (see #{DOC_LINK_TO_CLASS(FEDM::TransponderType)})

	// for ISO15693, ICODE1
	int m_iso15693_Afi;   ///< The Application Family Identifier (negative value indicates invalid)
	int m_iso15693_DsfId; ///< The Data Storage Family Identifier (negative value indicates invalid)

	// for ISO15693
	int m_iso15693_TagStatus;  ///< Customer specific value (negative value indicates invalid)
	int m_iso15693_NewAfi;     ///< Customer specific value (negative value indicates invalid)
		
	// for ISO14443A
	int m_iso14443A_TrInfo;  ///< (negative value indicates invalid)
	int m_iso14443A_OptInfo; ///< (negative value indicates invalid)
		
	// for ISO14443B
	int m_iso14443B_ProtocolInfo; ///< (negative value indicates invalid)
		
	// for SR176, SRIx
	int m_sr_ChipId; ///< (negative value indicates invalid)
		
	// for Innovatron
	int m_innovatron_Verlog; ///< (negative value indicates invalid)
	int m_innovatron_Config; ///< (negative value indicates invalid)
	std::vector<uint8_t> m_innovatron_Atr;
		
	// for ASK_CTx
	int m_askCtx_ProductCode;  ///< (negative value indicates invalid)
	int m_askCtx_FabCode;      ///< (negative value indicates invalid)
	int m_askCtx_AppCode;      ///< (negative value indicates invalid)
	int m_askCtx_EmbedderCode; ///< (negative value indicates invalid)
		
	// for ISO18000_3M3, EpcClass1Gen2
	int           m_epcC1G2_IddType;          ///< The Identifier Data Type (IDDT)
	uint16_t      m_epcC1G2_Pc;               ///< The Protocol-Control (PC) of EPC Class 1 Gen 2 or ISO 18000-3M- compliant Transponder
	uint16_t      m_epcC1G2_XpcW1;            ///< The Extended Protocol-Control (XPC W1) of EPC Class 1 Gen 2 or ISO 18000-3M- compliant Transponder

	// RSSI values of all antennas (max 8 elements)
	std::vector<FEDM::RssiItem> m_rssiValues;

	size_t _tidIndex(void) const;

	static int _epcC1G2_TagModelNumberFromTid(const uint8_t *tid);
	static int _epcC1G2_MaskDesignerIDFromTid(const uint8_t *tid);
	static int _epcC1G2_Iec7816_MfrCode(const uint8_t *tid);

}; // end of class TagItem

}; // end of namespace FEDM

#endif // FEDM_TAG_ITEM_H

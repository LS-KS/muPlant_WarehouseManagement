/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_4_H
#define FEDM_TH_ISO14443_4_H

#include "TagHandler/Th14443_3.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing basic commands for all ISO 14443-4 compliant Transponders
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_4 : public ThIso14443_3
{
	friend class Internal::ReaderBase;

public:

	class FEDM_CLASS_DEF Iso14443_4_TransponderInfo
	{
		friend class ThIso14443_4;
		friend class FedmFriend;
	public:
		Iso14443_4_TransponderInfo();

		void clear();

		uint8_t fsci() const {
			return m_fsci;
		}

		uint8_t fwi() const {
			return m_fwi;
		}

		uint8_t dsi() const {
			return m_dsi;
		}

		uint8_t dri() const {
			return m_dri;
		}

		uint8_t nadSupport() const {
			return m_nadSupport;
		}

		uint8_t cidSupport() const {
			return m_cidSupport;
		}

	private:
		uint8_t m_fsci; // FSC or FSCI?
		uint8_t m_fwi;
		uint8_t m_dsi;
		uint8_t m_dri;
		uint8_t m_nadSupport;
		uint8_t m_cidSupport;
	};

	virtual std::string transponderName() const override;

	/// @param[in] cid CID
	///
	/// Set cid for next use, if enabled
	void setCid(uint8_t cid);

	/// @param[in] enable If CID should be enabled
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Enable CID usage
	int enableCid(bool enable);

	/// @return CID
	///
	/// Get CID, actually in use
	uint8_t cid();

	/// @return true, if CID is enabled
	///
	/// Query, if CID usage is enabled
	bool isCidEnabled();

	/// @param[in] nad NAD
	///
	/// Set NAD for next use, if enabled
	void setNad(uint8_t nad);

	/// @param[in] enable If NAD should be enabled
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Enable NAD usage
	int enableNad(bool enable);

	/// @return NAD
	///
	/// Get NAD, actually in use
	uint8_t nad();

	/// @return true, if NAD is enabled
	///
	/// Query, if NAD usage is enabled
	bool isNadEnabled();

	/// @param[in] requestData Request data with %APDU
	/// @param[out] responseData Response data with %APDU
	/// @param[in] responseBufferLen Buffer size for responded %APDU
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Command [0xB2][0xBE] : T=CL %APDU for synchronous call
	/// The structure of an APDU is defined by ISO/IEC 7816-4.<br>
	///
	/// @note An %APDU exchange can be a long term function call. The necessary timeout for the communication port is adapted internally and set to the previous value 
	/// when the method returns. If an application cannot wait such a long time, use the overloaded APDU(unsigned char*,unsigned int,void*,void (*)(void*,int,int,int)) 
	/// method for asynchronous execution.
	int apdu(const std::vector<uint8_t> & requestData, std::vector<uint8_t> & responseData);

	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Command [0xB2][0xBE] : T=CL Ping command
	int ping();

	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Command [0xB2][0xBE] : T=CL Deselect command
	int deselect();

	/// @param[out] fsci
	/// @param[out] fwi
	/// @param[out] dsi
	/// @param[out] dri
	/// @param[out] nadSupport
	/// @param[out] cidSupport
	/// @return #{DOC_LIB_RETURN_VALUE}	
	///
	/// Command [0xB2][0x2B] : Get Transponder Info command
	int getTransponderInfo(Iso14443_4_TransponderInfo & transponderInfo);

	virtual ~ThIso14443_4();

protected:
	ThIso14443_4(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

private:
	bool m_useNad = false;
	uint8_t m_nad = 0;
	bool m_useCid = false;
	uint8_t m_cid = 0;

	int transceiveApdu(std::vector<uint8_t> & responseData);
	int transceiveChainedApduRequest();

}; // end of class ThIso14443_4

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_4_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_CARD_INFO_14443_H
#define FEDM_CARD_INFO_14443_H

#include <vector>

#include "FedmBasic.h"



namespace FEDM {

/// @brief DATA class with card information of ISO14443 transponder
/// 
/// See manual of CPR74 for details of the formats
class FEDM_CLASS_DEF CardInfo14443
{
	friend class Internal::ReaderBase;
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	static const uint8_t CardInfoNone = 0x00;
	static const uint8_t CardInfoISO14443_4A    = 0x01;
	static const uint8_t CardInfoISO14443_4B    = 0x02;
	static const uint8_t CardInfoISO14443_3A    = 0x03;
	static const uint8_t CardInfoInnovatron     = 0x04;
	static const uint8_t CardInfoISO14443_4A_F5 = 0x05;
	static const uint8_t CardInfoISO14443_3A_F6 = 0x06;

/** @name Main
 */
///@{					
	CardInfo14443();

	void clear(void);

	bool isValid(void) const { return m_format != CardInfoNone; }

	uint8_t format() const { return m_format; }
	const std::vector<uint8_t> & info()    const { return m_info; }
	const std::vector<uint8_t> & version() const { return m_version; }

	std::string toString(void) const;
///@}

/** @name Format 01 CardInfoISO14443_4A
 */
///@{
	uint16_t f01_Atqa(void) const;
	uint8_t  f01_Sak(void) const;
	uint8_t  f01_Tl(void) const;
	size_t   f01_AtsIndex(void) const;
	bool     f01_IsMifarePlusSL3(void) const;
///@}
		
/** @name Format 02 CardInfoISO14443_4B
 */
///@{
	uint32_t f02_Atqb(void) const;
	uint8_t  f02_ProtocolType(void) const;
///@}
		
/** @name Format 03 CardInfoISO14443_3A
 */
///@{
	uint16_t f03_Atqa(void) const;
	uint8_t  f03_Sak(void) const;
///@}
		
/** @name Format 04 CardInfoInnovatron
 */
///@{
	uint8_t f04_TagAddr(void) const;
	uint8_t f04_ValAddr(void) const;
///@}

/** @name Format 01 CardInfoISO14443_4A_F5
 */
///@{
	uint8_t  f05_Sak(void) const;
	uint8_t  f05_HwType(void) const;
	uint8_t  f05_HwVersion(void) const;
	uint8_t  f05_MemSize(void) const;
///@}
		
/** @name Format 03 CardInfoISO14443_3A
 */
///@{
	uint8_t  f06_Sak(void) const;
	uint8_t  f06_HwType(void) const;
///@}

private:
	uint8_t              m_format;
	std::vector<uint8_t> m_info;
	std::vector<uint8_t> m_version;
};

}; // end of namespace FEDM

#endif // FEDM_CARD_INFO_14443_H

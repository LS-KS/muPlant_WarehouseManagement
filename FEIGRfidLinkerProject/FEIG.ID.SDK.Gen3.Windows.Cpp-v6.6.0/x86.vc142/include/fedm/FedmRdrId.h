/**
*
* Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
*
* This software is the confidential and proprietary information of
* FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
* disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered
* into with FEIG ELECTRONIC GmbH.
*/

#ifndef FEDM_READER_ID_H
#define FEDM_READER_ID_H

#include <string>
#include <array>

#include <FedmConst.h>
#include <FedmHide.h>
#include <FedmDateTime.h>
#include <FedmCfgId.h>



namespace FEDM {



/// @brief DATA class with reader identification informations send by EventType::IdentificationEvent (command [0x2A])
class FEDM_CLASS_DEF ReaderIdentification
{
	friend class Payload::PlBase;
	friend class Internal::ReaderBase;
	friend class FedmFriend;

public:
	ReaderIdentification();

	void clear(void);
	bool isValid(void) const;

	/// Returns Date and Time of identification event
	const DateTime & dateTime(void) const { return m_dateTime; }

	/// Returns the reader type of the connected reader
	uint32_t readerType(void) const {
		return (static_cast<uint32_t>(m_readerAssembly) << 8) |
			    static_cast<uint32_t>(m_swType);
	}

	/// Returns the reader type as string
	std::string readerTypeToString(void) const { return ReaderType::toString(readerType()); }

	/// Returns the device ID
	uint32_t    deviceId(void) const { return m_deviceId; }

	/// Returns the device ID as hex. string
	std::string deviceIdToHexString(void) const;

	/// Returns the readers firmware major version
	uint8_t     majVer(void) const { return m_majVer; }

	/// Returns the readers firmware minor version
	uint8_t     minVer(void) const { return m_minVer; }

	/// Returns the readers firmware devel version
	uint8_t     devVer(void) const { return m_devVer; }

	/// Returns the readers firmware version as string
	std::string versionToString(void) const;

	uint8_t     hwType(void) const { return m_hwType; }
	uint8_t     swType(void) const { return m_swType; }
	uint16_t    trType(void) const { return m_trType; }

	/// Returns the readers receive protocol buffer size
	size_t      rxBufferSize(void) const { return m_rxBufferSize; }

	/// Returns the readers transmit protocol buffer size
	size_t      txBufferSize(void) const { return m_txBufferSize; }

	uint8_t     readerRevision(void) const { return m_readerRevision; }
	uint8_t     readerAssembly(void) const { return m_readerAssembly; }
	bool        isFrameSupportUnknown   (void) const { return m_frameSupport == 0x00; }
	bool        isAdvancedFrameSupported(void) const { return (m_frameSupport & 0x02) != 0; }
	bool        isEnhancedFrameSupported(void) const { return (m_frameSupport & 0x04) != 0; }
	FEDM::ConfigId configId(void) const { return m_configId; }

	const std::string & customerReaderId(void) const { return m_customerReaderId; }
	const std::string & customerLocation(void) const { return m_customerLocation; }
	const std::string & customerField1  (void) const { return m_customerField1; }
	const std::string & customerField2  (void) const { return m_customerField2; }

private:
	DateTime    m_dateTime;				///< Date and Time of identification event
	uint32_t    m_deviceId;				///< Device-ID (serial number)
	uint8_t     m_majVer;				///< major version number of RFC
	uint8_t     m_minVer;				///< minor version number of RFC
	uint8_t     m_devVer;				///< developer version number of RFC
	uint8_t     m_hwType;				///< flag field with hardware options of RFC
	uint8_t		m_swType;				///< reader type, low byte
	uint16_t	m_trType;				///< flag field with supported Transponder types
	size_t		m_rxBufferSize;			///< size of Reader's receive buffer
	size_t		m_txBufferSize;			///< size of Reader's transmit buffer
	uint8_t     m_readerRevision;		///< additional reader information
	uint8_t		m_readerAssembly;		///< reader type, high byte
	uint8_t     m_frameSupport;			///< 0x02: Advanced, 0x04: Enhanced
	FEDM::ConfigId m_configId;
	std::string m_customerReaderId;
	std::string m_customerLocation;
	std::string m_customerField1;
	std::string m_customerField2;

}; // end of class ReaderIdentification

}; // end of namespace FEDM

#endif // FEDM_READER_ID_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_BRM_ITEM_H
#define FEDM_BRM_ITEM_H

#include <string>
#include <vector>
#include <map>

#include "FedmConst.h"
#include "FedmDateTime.h"
#include "FedmTagItem.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief DATA class with requested Buffered Read Mode data or send Notification Mode data by EventType::BrmEvent (command [0x22]).
///
/// This class contains all record members, which are potentially part of the readers response of the command [0x22] Read Buffer.<br>
/// An item can be obtained via the data queue in group Brm.
class FEDM_CLASS_DEF BrmItem
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:

	class FEDM_CLASS_DEF SectorDataBlocks
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorDataBlocks();
		~SectorDataBlocks();

		void clear();

		/// @return True, if the SectorDataBlocks contains valid data blocks
		bool isValid() const { return !m_blocks.empty(); }

		const std::vector<uint8_t> & blocks() const { return m_blocks; }
		size_t blockSize() const { return m_blockSize; }
		size_t blockCount() const { return m_blockCount; }

	private:
		std::vector<uint8_t> m_blocks; ///< Container of data blocks. Size is blockSize * blockCount
		size_t m_blockSize;  ///< Size of one data block in byte
		size_t m_blockCount; ///< Number of data blocks
	};

	class FEDM_CLASS_DEF SectorAntennas
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorAntennas();
		~SectorAntennas();

		void clear();

		/// @return True, if the SectorAntennas values are valid
		bool isValid() const { return m_antennas != 0; }

		/// @return True, if the RSSI statistic values are valid
		bool isTagStatistic() const { return isValid() && (m_tagCount > 0); }

		uint32_t antennas() const { return m_antennas; }
		size_t tagCount() const { return m_tagCount; }
		int rssiMax() const { return m_rssiMax; }
		int rssiAvg() const { return m_rssiAvg; }

	private:
		uint32_t  m_antennas; ///< Is a bit field (see reader manual)
		size_t    m_tagCount; ///< Number of transponders
		int       m_rssiMax;  ///< The maximum RSSI value
		int       m_rssiAvg;  ///< The average RSSI value
	};

	class FEDM_CLASS_DEF SectorInput
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorInput();
		~SectorInput();

		void clear();

		/// @return True, if the SectorInput values are valid
		bool isValid() const { return m_state >= 0; }

		uint32_t input() const { return m_input; }
		int state() const { return m_state; }

	private:
		uint32_t m_input;
		int      m_state;
	};

	class FEDM_CLASS_DEF SectorMac
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorMac();
		~SectorMac();

		void clear();

		/// @return True, if the SectorMac contains a valid MAC address
		bool isValid() const;

		bool isFeigMacAddress() const;
		const std::array<uint8_t, 6> & macAddress() const { return m_macAddress; }
		std::string toString() const;

	private:
		std::array<uint8_t, 6> m_macAddress;
	};

	class FEDM_CLASS_DEF SectorScannerId
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		static const int TypeScannerId = 0x00;
		static const int TypeDeviceId  = 0x01;

		SectorScannerId();

		void clear();

		/// @return True, if SectorScannerId contains valid data for Scanner-ID
		bool isValid() const { return m_type >= 0; }

		int type() const { return m_type; }
		const std::string & scannerId() const { return m_scannerId; }

	private:
		int         m_type; ///< 0x00: ScannerId; 0x01: DeviceID
		std::string m_scannerId; ///< Scanner-ID (only for Notification-Mode)
	};

	class FEDM_CLASS_DEF SectorDirection
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		static const int DetectionDisabled = 0;
		static const int Direction1 = 1;
		static const int Direction2 = 2;

		SectorDirection();

		void clear();

		/// @return True, if SectorDirection contains valid data
		bool isValid() const { return m_direction >= 0; }

		bool isDetectionDisabled() const { return m_direction == DetectionDisabled; }
		bool isDirection1()        const { return m_direction == Direction1; }
		bool isDirection2()        const { return m_direction == Direction2; }

		int direction() const { return m_direction; }; ///< The UHF gate direction information

	private:
		int m_direction;
	};


public:
	BrmItem();

	void clear();

	const TagItem          & tag       (void) const { return m_tag; }
	const DateTime         & dateTime  (void) const { return m_dateTime; }
	const SectorDataBlocks & dataBlocks(void) const { return m_dataBlocks; }
	const SectorAntennas   & antennas  (void) const { return m_antennas; }
	const SectorInput      & input     (void) const { return m_input; }
	const SectorMac        & mac       (void) const { return m_mac; }
	const SectorScannerId  & scannerId (void) const { return m_scannerId; }
	const SectorDirection  & direction (void) const { return m_direction; }
	const std::vector<FEDM::RssiItem> & rssiValues(void) const { return m_tag.rssiValues(); }

protected:
	TagItem          m_tag;
	DateTime         m_dateTime;
	SectorDataBlocks m_dataBlocks;
	SectorAntennas   m_antennas;
	SectorInput      m_input;
	SectorMac        m_mac;
	SectorScannerId  m_scannerId;
	SectorDirection  m_direction;

	TagItem          & tag       (void) { return m_tag; }
	DateTime         & dateTime  (void) { return m_dateTime; }
	SectorDataBlocks & dataBlocks(void) { return m_dataBlocks; }
	SectorAntennas   & antennas  (void) { return m_antennas; }
	SectorInput      & input     (void) { return m_input; }
	SectorMac        & mac       (void) { return m_mac; }
	SectorScannerId  & scannerId (void) { return m_scannerId; }
	SectorDirection  & direction (void) { return m_direction; }

}; // end of class BrmTableItem

}; // end of namespace FEDM

#endif // FEDM_BRM_ITEM_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TAG_EVENT_ITEM_H
#define FEDM_TAG_EVENT_ITEM_H

#include <string>
#include <vector>
#include <map>

#include <FedmConst.h>
#include <FedmDateTime.h>
#include <FedmTagItem.h>
#include <FedmTagEventSignals.h>
#include <FedmHide.h>


namespace FEDM {

/// @brief DATA class with requested Buffered Read Mode data or send Notification Mode data by EventType::TagEvent (command [0x2B]).
///
/// This class contains all record members, which are potentially part of the readers response of the command [0x2B] Read Buffer.<br>
/// An item can be obtained via the data queue in group TagEvent.
class FEDM_CLASS_DEF TagEventItem
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

		void clear(void);
		bool isValid() const { return !m_blocks.empty(); }

		const std::vector<uint8_t> & blocks() const { return m_blocks; }
		size_t blockAddress() const { return m_blockAddress; }
		size_t blockSize() const { return m_blockSize; }
		size_t blockCount() const { return m_blockCount; }

	private:
		std::vector<uint8_t> m_blocks; ///< Container of data blocks. Size is blockSize * blockCount
		size_t m_blockAddress; ///< Start address of the first block
		size_t m_blockSize;    ///< Size of one data block in byte
		size_t m_blockCount;   ///< Number of data blocks
	};


	class FEDM_CLASS_DEF SectorInput
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorInput();

		void clear();

		/// @return True, if the SectorInput values are valid
		bool isValid() const { return m_state >= 0; }

		/// @return The current input states of the reader
		uint32_t input() const { return m_input; }

		/// @return The trigger state (see reader manual). This value is only valid if TagItem is invalid.
		int state() const { return m_state; }

	private:
		uint32_t m_input;
		int      m_state;
	};


	class FEDM_CLASS_DEF SectorDirection
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorDirection();

		void clear();

		/// @return True, if the SectorDirection value is valid
		bool isValid() const { return m_direction >= 0; }

		int direction(void) const { return m_direction; }

	private:
		int m_direction;
	};


public:
	TagEventItem();

	void clear();

	const TagItem          & tag       (void) const { return m_tag; }
	const DateTime         & dateTime  (void) const { return m_dateTime; }
	const SectorDataBlocks & dbUser    (void) const { return m_dbUser; }
	const SectorDataBlocks & dbEpc     (void) const { return m_dbEpc; }
	const SectorDataBlocks & dbTid     (void) const { return m_dbTid; }
	const RssiItem         & antenna   (void) const { return m_tag.m_rssiValues.at(0); }
	const SectorInput      & input     (void) const { return m_input; }
	const SectorDirection  & direction (void) const { return m_direction; }
	const TagEventSignals  & evtSignals(void) const { return m_evtSignals; }

protected:
	TagItem          m_tag;
	DateTime         m_dateTime;
	SectorDataBlocks m_dbUser;
	SectorDataBlocks m_dbEpc;
	SectorDataBlocks m_dbTid;
	SectorInput      m_input;
	SectorDirection  m_direction;
	TagEventSignals  m_evtSignals;

	TagItem          & tag       (void) { return m_tag; }
	DateTime         & dateTime  (void) { return m_dateTime; }
	SectorDataBlocks & dbUser    (void) { return m_dbUser; }
	SectorDataBlocks & dbEpc     (void) { return m_dbEpc; }
	SectorDataBlocks & dbTid     (void) { return m_dbTid; }
	RssiItem         & antenna   (void) { return m_tag.m_rssiValues.at(0); }
	SectorInput      & input     (void) { return m_input; }
	SectorDirection  & direction (void) { return m_direction; }
	TagEventSignals  & evtSignals(void) { return m_evtSignals; }

}; // end of class TagEventItem

}; // end of namespace FEDM

#endif // FEDM_TAG_EVENT_ITEM_H

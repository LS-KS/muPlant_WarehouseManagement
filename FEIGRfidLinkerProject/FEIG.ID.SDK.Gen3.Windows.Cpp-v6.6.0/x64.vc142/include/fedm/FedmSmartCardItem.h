/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_SMART_CARD_ITEM_H
#define FEDM_SMART_CARD_ITEM_H

#include "FedmBase.h"

namespace FEDM {

/// @brief DATA class with information of a smard card slot
class FEDM_CLASS_DEF SmartCardItem {
	friend class FedmFriend;

public:
	enum class SmartCardSlotType : uint8_t{
		Empty = 0,
		Inserted = 1
	};

private:
	int m_slotNumber;
	SmartCardSlotType m_slotType;
	int m_nad;

public:
	SmartCardItem() : SmartCardItem(-1, SmartCardSlotType::Empty) {
	}
	SmartCardItem(int slotNumber, SmartCardSlotType type) {
		m_slotNumber = slotNumber;
		m_slotType = type;
		m_nad = -1;
	}

	void setNoNad() {
		m_nad = -1;
	}
	void setNad(uint8_t nad) {
		m_nad = nad;
	}

	bool isNadEnabled() const {
		return m_nad >= 0;
	}

	int slotNumber() const {
		return m_slotNumber;
	}

	int nad() const {
		return m_nad;
	}

	SmartCardSlotType slotType() const {
		return m_slotType;
	}

	bool isValid() const {
		return m_slotNumber > 0 && m_slotType != SmartCardSlotType::Empty;
	}
};

} // namespace FEDM

#endif // FEDM_SMART_CARD_ITEM_H

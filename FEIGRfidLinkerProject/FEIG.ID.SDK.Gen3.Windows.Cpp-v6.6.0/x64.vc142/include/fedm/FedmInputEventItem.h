/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_INPUT_EVENT_ITEM_H
#define FEDM_INPUT_EVENT_ITEM_H

#include "FedmConst.h"
#include "FedmDateTime.h"
#include "FedmHide.h"


namespace FEDM {

/// @brief DATA class with send notification input data by EventType::InputEvent (command [0x2C] or [0x74]).
///
/// This class contains all data, which are potentially part of the readers input event request of the command [0x2C] Input Event.<br>
/// An input event request of the command [0x74] does not contain date and time.<br>
/// An item can be obtained via the data queue in group IO.
class FEDM_CLASS_DEF InputEventItem
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	InputEventItem();

	void clear();

    bool isValid(void) const;

	const DateTime & dateTime  (void) const { return m_dateTime; }

    /// @return The digital input states before event. Use a XOR with currentInput() to find out the changed input states.
    uint32_t previousInput(void) const { return m_previousInput; }

    /// @return The digital input states after event. Use a XOR with previousInput() to find out the changed input states.
    uint32_t currentInput(void)  const { return m_currentInput; }

protected:
	DateTime m_dateTime;
    uint32_t m_previousInput;
    uint32_t m_currentInput;

	DateTime & dateTime(void) { return m_dateTime; }

}; // end of class InputEventItem

}; // end of namespace FEDM

#endif // FEDM_INPUT_EVENT_ITEM_H

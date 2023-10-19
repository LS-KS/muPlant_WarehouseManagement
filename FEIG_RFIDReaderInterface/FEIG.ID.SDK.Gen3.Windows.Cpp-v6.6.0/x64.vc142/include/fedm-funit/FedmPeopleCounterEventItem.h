/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_PEOPLE_COUNTER_EVENT_ITEM_H
#define FEDM_PEOPLE_COUNTER_EVENT_ITEM_H

#include <FedmFunitBase.h>
#include <FedmFunitHide.h>
#include <FedmDateTime.h>
#include <PdeviceData.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief DATA class with people counter notification data by EventType::PeopleCounterEvent (command [0x77])
class FEDM_FUNIT_CLASS_DEF PeopleCounterEventItem
{
	friend class Payload::PlFunit;

public:
    void clear(void) { *this = PeopleCounterEventItem(); }

	bool isValid(void) const { return m_address.isValid(); }
	const PdeviceAddress & address(void) const { return m_address; }

	const DateTime & dateTime(void) const { return m_dateTime; }

	uint32_t detector1Counter1(void) const { return m_detector1Counter1; }
	uint32_t detector1Counter2(void) const { return m_detector1Counter2; }
	uint32_t detector2Counter1(void) const { return m_detector2Counter1; }
	uint32_t detector2Counter2(void) const { return m_detector2Counter2; }

private:
	PdeviceAddress m_address;
    DateTime       m_dateTime;

	uint32_t m_detector1Counter1 = 0;
	uint32_t m_detector1Counter2 = 0;
	uint32_t m_detector2Counter1 = 0;
	uint32_t m_detector2Counter2 = 0;

	DateTime & dateTime(void) { return m_dateTime; }

}; // end of class PeopleCounterEventItem

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_PEOPLE_COUNTER_EVENT_ITEM_H

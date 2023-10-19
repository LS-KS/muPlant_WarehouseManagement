/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TAG_EVENT_LAYOUT_H
#define FEDM_TAG_EVENT_LAYOUT_H

#include <FedmBase.h>



namespace FEDM {

/// @brief DATA class with layout settings for TagEventItem
class FEDM_CLASS_DEF TagEventLayout
{
public:
	TagEventLayout() { clear(); }

	void clear(void) { m_layoutConfiguration = 0; }
	bool isEmpty(void) const { return m_layoutConfiguration == 0; }

	bool isDate        (void) const { return isBit(m_layoutConfiguration, 0); }
	bool isTime        (void) const { return isBit(m_layoutConfiguration, 1); }
	bool isIdd         (void) const { return isBit(m_layoutConfiguration, 2); }
	bool isDbTid       (void) const { return isBit(m_layoutConfiguration, 4); }
	bool isDbEpc       (void) const { return isBit(m_layoutConfiguration, 5); }
	bool isDbUser      (void) const { return isBit(m_layoutConfiguration, 6); }
	bool isAfiDsfid    (void) const { return isBit(m_layoutConfiguration, 7); }
	bool isAntenna     (void) const { return isBit(m_layoutConfiguration, 9); }
	bool isInput       (void) const { return isBit(m_layoutConfiguration, 12); }
	bool isDirection   (void) const { return isBit(m_layoutConfiguration, 13); }
	bool isSignals     (void) const { return isBit(m_layoutConfiguration, 14); }

	void useDate        (bool on) { setBit(m_layoutConfiguration, 0, on); }
	void useTime        (bool on) { setBit(m_layoutConfiguration, 1, on); }
	void useIdd         (bool on) { setBit(m_layoutConfiguration, 2, on); }
	void useDbTid       (bool on) { setBit(m_layoutConfiguration, 4, on); }
	void useDbEpc       (bool on) { setBit(m_layoutConfiguration, 5, on); }
	void useDbUser      (bool on) { setBit(m_layoutConfiguration, 6, on); }
	void useAfiDsfid    (bool on) { setBit(m_layoutConfiguration, 7, on); }
	void useAntenna     (bool on) { setBit(m_layoutConfiguration, 9, on); }
	void useInput       (bool on) { setBit(m_layoutConfiguration, 12, on); }
	void useDirection   (bool on) { setBit(m_layoutConfiguration, 13, on); }
	void useSignals     (bool on) { setBit(m_layoutConfiguration, 14, on); }

	// Functions for group config
	uint32_t layoutConfiguration(void) const { return m_layoutConfiguration; }
	void setLayoutConfiguration(uint32_t layout) { m_layoutConfiguration = layout; }

private:
    uint32_t   m_layoutConfiguration;

	static bool isBit(uint32_t layout, int bit)
	{
		uint32_t mask = 0x00000001;
		mask <<= bit;
		return (layout & mask) != 0;
	}

	static void setBit(uint32_t & layout, int bit, bool on)
	{
		uint32_t mask = 0x00000001;
		mask <<= bit;
		if (on)
			layout |= mask;
		else
			layout &= ~mask;
	}

}; // end of class TagEventLayout

}; // end of namespace FEDM

#endif // FEDM_TAG_EVENT_LAYOUT_H

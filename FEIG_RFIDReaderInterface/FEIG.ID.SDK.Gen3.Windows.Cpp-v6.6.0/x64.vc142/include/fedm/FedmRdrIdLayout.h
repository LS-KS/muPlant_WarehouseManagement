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

#ifndef FEDM_READER_ID_LAYOUT_H
#define FEDM_READER_ID_LAYOUT_H

#include <FedmBase.h>



namespace FEDM {



/// @brief DATA class with layout settings for ReaderIdentification
class FEDM_CLASS_DEF ReaderIdentificationLayout
{
	friend class FedmFriend;
public:
	ReaderIdentificationLayout() { clear(); }

	void clear(void) { m_layoutConfiguration = 0; }
	bool isEmpty(void) const { return m_layoutConfiguration == 0; }

	bool isDate            (void) const { return isBit(m_layoutConfiguration, 0); }
	bool isTime            (void) const { return isBit(m_layoutConfiguration, 1); }
	bool isReaderInfo      (void) const { return isBit(m_layoutConfiguration, 25); }
	bool isCustomerReaderId(void) const { return isBit(m_layoutConfiguration, 27); }
	bool isCustomerLocation(void) const { return isBit(m_layoutConfiguration, 28); }
	bool isCustomerField1  (void) const { return isBit(m_layoutConfiguration, 29); }
	bool isCustomerField2  (void) const { return isBit(m_layoutConfiguration, 30); }

	void useDate            (bool on) { setBit(m_layoutConfiguration, 0, on); }
	void useTime            (bool on) { setBit(m_layoutConfiguration, 1, on); }
	void useReaderInfo      (bool on) { setBit(m_layoutConfiguration, 25, on); }
	void useCustomerReaderId(bool on) { setBit(m_layoutConfiguration, 27, on); }
	void useCustomerLocation(bool on) { setBit(m_layoutConfiguration, 28, on); }
	void useCustomerField1  (bool on) { setBit(m_layoutConfiguration, 29, on); }
	void useCustomerField2  (bool on) { setBit(m_layoutConfiguration, 30, on); }

	// Functions for group config
	uint32_t layoutConfiguration(void) const { return m_layoutConfiguration; }
	void setLayoutConfiguration(uint32_t layout) { m_layoutConfiguration = layout; }

private:
    uint32_t   m_layoutConfiguration;

	static bool isBit(uint32_t layout, int bit)
	{
		uint32_t mask = 0x01;
		mask <<= bit;
		return (layout & mask) != 0;
	}

	static void setBit(uint32_t & layout, int bit, bool on)
	{
		uint32_t mask = 0x01;
		mask <<= bit;
		if (on)
			layout |= mask;
		else
			layout &= ~mask;
	}

}; // end of class ReaderIdentificationLayout

}; // end of namespace FEDM

#endif // FEDM_READER_ID_LAYOUT_H

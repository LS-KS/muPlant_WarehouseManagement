/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_BRM_LAYOUT_H
#define FEDM_BRM_LAYOUT_H

#include <FedmBase.h>



namespace FEDM {

/// @brief DATA class with layout settings for BrmItem
class FEDM_CLASS_DEF BrmLayout
{
public:
/** @name Main
 */
///@{					
	BrmLayout() { clear(); }

	void clear(void) { m_trData1 = m_trData2 = m_trData3 = 0; }

	uint8_t trData1(void) const { return m_trData1; }
	uint8_t trData2(void) const { return m_trData2; }
	uint8_t trData3(void) const { return m_trData3; }
	uint32_t trData(void) const
	{
		uint32_t data = 0;
		data |= static_cast<uint32_t>(m_trData1);
		data <<= 8;
		data |= static_cast<uint32_t>(m_trData2);
		data <<= 8;
		data |= static_cast<uint32_t>(m_trData3);
		return data;
	}

	void setTrData1(uint8_t value) { m_trData1 = value; }
	void setTrData2(uint8_t value) { m_trData2 = value; }
	void setTrData3(uint8_t value) { m_trData3 = value; }
///@}

/** @name trData1
 */
///@{					
	bool isIdd       (void) const { return isBit(m_trData1, 0); }
	bool isDb        (void) const { return isBit(m_trData1, 1); }
	bool isEas       (void) const { return isBit(m_trData1, 2); }
	bool isDbMsbFirst(void) const { return isBit(m_trData1, 3); }
	bool isAntenna   (void) const { return isBit(m_trData1, 4); }
	bool isTime      (void) const { return isBit(m_trData1, 5); }
	bool isDate      (void) const { return isBit(m_trData1, 6); }
	bool isTrData2   (void) const { return isBit(m_trData1, 7); }

	void useIdd       (bool on) { setBit(m_trData1, 0, on); }
	void useDb        (bool on) { setBit(m_trData1, 1, on); }
	void useEas       (bool on) { setBit(m_trData1, 2, on); }
	void useDbMsbFirst(bool on) { setBit(m_trData1, 3, on); }
	void useAntenna   (bool on) { setBit(m_trData1, 4, on); }
	void useTime      (bool on) { setBit(m_trData1, 5, on); }
	void useDate      (bool on) { setBit(m_trData1, 6, on); }
	void useTrData2   (bool on) { setBit(m_trData1, 7, on); }
///@}

/** @name trData2
 */
///@{					
	bool isInput    (void) const { return isBit(m_trData2, 0); }
	bool isMac      (void) const { return isBit(m_trData2, 1); }
	bool isAfiDsfid (void) const { return isBit(m_trData2, 2); } // double function bit
	bool isScannerId(void) const { return isBit(m_trData2, 2); } // double function bit
	bool isTagStat  (void) const { return isBit(m_trData2, 3); }
	bool isAntExt   (void) const { return isBit(m_trData2, 4); }
	bool isDirection(void) const { return isBit(m_trData2, 5); }
	// Bit 6 is unused
	bool isTrData3  (void) const { return isBit(m_trData2, 7); }

	void useInput    (bool on) { setBit(m_trData2, 0, on); }
	void useMac      (bool on) { setBit(m_trData2, 1, on); }
	void useAfiDsfid (bool on) { setBit(m_trData2, 2, on); } // double function bit
	void useScannerId(bool on) { setBit(m_trData2, 2, on); } // double function bit
	void useTagStat  (bool on) { setBit(m_trData2, 3, on); }
	void useAntExt   (bool on) { setBit(m_trData2, 4, on); }
	void useDirection(bool on) { setBit(m_trData2, 5, on); }
	// Bit 6 is unused
	void useTrData3  (bool on) { setBit(m_trData2, 7, on); }
///@}

/** @name trData3
 */
///@{					
	bool isComPrefix (void) const { return isBit(m_trData3, 0); }
	bool isAntStore  (void) const { return isBit(m_trData3, 1); }
	bool isDistance  (void) const { return isBit(m_trData3, 2); }
	bool isRdComplete(void) const { return isBit(m_trData3, 3); }
	bool isChangeAfi (void) const { return isBit(m_trData3, 4); }
	bool isSeek      (void) const { return isBit(m_trData3, 5); }
	bool isActOnEpc  (void) const { return isBit(m_trData3, 6); } // double function bit
	bool isChangeEas (void) const { return isBit(m_trData3, 6); } // double function bit

	void useComPrefix (bool on) { setBit(m_trData3, 0, on); }
	void useAntStore  (bool on) { setBit(m_trData3, 1, on); }
	void useDistance  (bool on) { setBit(m_trData3, 2, on); }
	void useRdComplete(bool on) { setBit(m_trData3, 3, on); }
	void useChangeAfi (bool on) { setBit(m_trData3, 4, on); }
	void useSeek      (bool on) { setBit(m_trData3, 5, on); }
	void useActOnEpc  (bool on) { setBit(m_trData3, 6, on); } // double function bit
	void useChangeEas (bool on) { setBit(m_trData3, 6, on); } // double function bit
///@}

private:
	uint8_t m_trData1;
	uint8_t m_trData2;
	uint8_t m_trData3;

	static bool isBit(uint8_t byte, int bit)
	{
		uint8_t mask = 0x01;
		mask <<= bit;
		return (byte & mask) != 0;
	}

	static void setBit(uint8_t & byte, int bit, bool on)
	{
		uint8_t mask = 0x01;
		mask <<= bit;
		if (on)
			byte |= mask;
		else
			byte &= ~mask;
	}

}; // end of class BrmEventLayout

}; // end of namespace FEDM

#endif // FEDM_BRM_LAYOUT_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_RSSI_ITEM_H
#define FEDM_RSSI_ITEM_H

#include "FedmConst.h"
#include "FedmHide.h"


namespace FEDM {

/// @brief DATA class with RSSI values of a transponder
class FEDM_CLASS_DEF RssiItem
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	RssiItem();

	void clear();

	/// @brief Check the validity of the RssiItem
	/// @return True, if the item values are valid
	bool isValid(void) const { return (m_antennaNumber >= 1) && (m_rssi >= 0); }

	/// @return Antenna number (first antenna is 1)
	int antennaNumber(void) const { return m_antennaNumber; }

	/// @return RSSI value<br>
	/// Dependent of the reader type this value is either a raw value or in dBm
	int rssi(void) const { return m_rssi; }

	/// @return State value
	int state(void) const { return m_state; }

	/// @return The phase angle value as raw value obtained by the reader
	int rawPhaseAngle(void) const { return m_rawPhaseAngle; }

	/// @return The phase angle value in degree
	float phaseAngle(void) const;

	int reserved(void) const { return m_reserved; }

private:
	int m_antennaNumber;
	int m_rssi;
	int m_state;
	int m_rawPhaseAngle;
	int m_reserved;

}; // end of class RssiItem

}; // end of namespace FEDM

#endif // FEDM_RSSI_ITEM_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_INVENTORY_PARAM_H
#define FEDM_INVENTORY_PARAM_H

#include <string>
#include <vector>

#include "FedmBase.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief DATA class with parameter for an inventory command
///
/// See the reader manuals, command inventory [0xB0][0x01] for details
class FEDM_CLASS_DEF InventoryParam
{
	friend class Internal::ReaderBase;
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	static const uint8_t ModeAntenna = 0x10;
	static const uint8_t ModeResponseTime = 0x40;
	static const uint8_t ModeTrList = 0x08;
	static const uint8_t ModeMore = 0x80;

	/// @brief Create a default inventory parameter set
	///
	/// All modes are off and More flag is controlled by SDK
	InventoryParam();

	/// @brief Create a special inventory parameter set
	///
	/// More flag must be controlled by application
	InventoryParam(uint8_t mode);

	~InventoryParam();

	/// @brief Set to default inventory parameter set
	///
	/// Set all modes off and More flag control by SDK
	void clear(void);

	/// @brief Define the antennas that will be scanned for an inventory
	/// @param[in] antennas A flag field to define the antennas for inventory scan
	///
	/// A call to this function activates ModeAntenna and deactivates ModeResponseTime.<br>
	/// If this mode is off all antennas will be scanned.
	void setAntennas(uint8_t antennas);

	/// @brief Set the maximum inventory response time
	/// @param[in] msec The maximum inventory response time in milliseconds
	///
	/// A call to this function activates ModeResponseTime and deactivates ModeAntenna.<br>
	/// This mode is supported by CPRxxx reader only.
	void setResponseTime(int msec);

	/// @brief Add transponder types to the TrList
	/// @param[in] trType Use a constant defined in class TransponderType
	///
	/// A call to this function activates ModeTrList.<br>
	/// This mode is not supported by all reader. See reader documentation of command inventory [0xB0][0x01] for details.
	bool addTransponderType(int trType);

	bool    isModeAntenna(void)      const { return (m_mode & ModeAntenna) != 0; }
	bool    isModeResponseTime(void) const { return (m_mode & ModeResponseTime) != 0; }
	bool    isModeTrList(void)       const { return (m_mode & ModeTrList) != 0; }
	bool    isModeMore(void)         const { return (m_mode & ModeMore) != 0; }

	uint8_t mode(void)         const { return m_mode; }
	uint8_t antennas(void)     const { return m_antennas; }
	int     responseTime(void) const { return m_responseTime; }

	const std::vector<int> & trList(void) const { return m_trList; }

private:
	bool             m_auto;         // default: true (is set to false with the special inventory constructor)
	uint8_t          m_mode;         // default: 0x00
	uint8_t          m_antennas;     // default: 0x00
	int              m_responseTime; // default: -1 (none)
	std::vector<int> m_trList;       // default: empty

	void setMode(uint8_t mode, bool on);

}; // end of class InventoryParam

}; // end of namespace FEDM

#endif // FEDM_INVENTORY_PARAM_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_DATA_H
#define FEDM_FUNIT_DATA_H

#include <string>
#include <vector>
#include <map>

#include <FedmFunitBase.h>
#include <FedmFunitHide.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief DATA class with firmware version information of a function unit
class FEDM_FUNIT_CLASS_DEF FunitFirmwareVersion
{
	friend class Payload::PlFunit;
	friend class FedmFriend;

public:
	static const int SwTypeHfMux = 10; ///< Firmware ID of a HF multiplexer 'ID ISC.ANT.MUX.M8' or 'ID ISC.ANT.MUX.M4'
	static const int SwTypeHfMuxM5 = 16; ///< Firmware ID of a HF multiplexer 'ID ISC.ANT.MUX.M5'
	static const int SwTypeHfAntTuner = 11; ///< Firmware ID of a HF antenna tuner 'ID ISC.DAT'
	static const int SwTypeUhfMux = 12; ///< Firmware ID of a UHF multiplexer 'ID ISC.ANT.UMUX-A'

	void clear(void) { *this = FunitFirmwareVersion(); }

	bool isValid(void) const { return m_swType >= 0; }

	/// @return The firmware ID of the function unit
	int swType(void) const { return m_swType; }

	int fwMajorRevision(void) const { return m_fwMajorRevision; }
	int fwMinorRevision(void) const { return m_fwMinorRevision; }
	int hwRevision(void) const { return m_hwRevision; }
	int dipSwitches(void) const { return m_dipSwitches; }

	std::string swTypeToString(void) const;
	std::string toString(void) const;
	
private:
	int m_swType = -1;
	int m_fwMajorRevision = -1;
	int m_fwMinorRevision = -1;
	int m_hwRevision = -1;
	int m_dipSwitches = -1;
};



/// @brief DATA class for a function unit address path
///
/// Objects of this class contain the path information to a function unit element.<br>
/// Beginning with the readers RF output channel it holds a list of all channel outputs to reach the element.
class FEDM_FUNIT_CLASS_DEF FunitAddress
{
	friend class Internal::FunitWorker;
	friend class FedmFriend;

public:
	static const size_t UnknownChannel = -1;
	
	void clear(void);

	bool isValid(void) const { return !m_channels.empty(); }

	/// @brief Query the readers RF output of a function unit element
	/// @return The readers RF output channel or UnknownChannel if isValid() returns false
	size_t readerOutput(void);

	/// @brief Query all parent output channels in the cascade to a function unit element
	/// @return After an initial call to readerOutput() every consecutive call to this function returns the output channel of the next function unit element in the cascade.
	/// UnknownChannel is returned if there is no next function unit element.
	size_t nextFunitOutput(void);

	/// @brief Query the address string through the cascade to a function unit element
	/// @return The address string of a function unit element. The structure is:<br>
	/// <ReaderChannel>[:<ChildChannel>[:<ChildChannel>[:...]]]<br>
	/// Example: 1:3:2
	std::string toString(void) const;

	/// @brief Query the path description to a function unit element
	/// @return The path description to a function unit element. Example:<br>
	/// Reader[1]->HF-Mux-Single-1to8[4]->HF-Mux-Single-1to8[8]->HF-Ant-Static
	std::string description(void) const { return m_description; }

private:
	size_t m_idx = -1;
	std::vector<size_t> m_channels;
	std::string         m_description;
};



/// @brief DATA class with antenna values of a HF dynamic antenna (DAT tuner)
///
/// For details see the documentation of the HF antenna tuner
class FEDM_FUNIT_CLASS_DEF FunitHfAntValues
{
	friend class Payload::PlFunit;

public:
	static const int StateCxOk = 0;
	static const int StateCxWarn = 1;
	static const int StateCxNeedTune = 2;

	void clear(void) { *this = FunitHfAntValues(); }

	bool isValid(void) const { return m_tuningState >= 0; }

	uint32_t c1(void)  const { return m_c1; }
	uint32_t c2(void)  const { return m_c2; }
	uint32_t r(void)   const { return m_r; }
	uint32_t phi(void) const { return m_phi; }
	int tuningState(void) const { return m_tuningState; }

	bool isAntSwitch    (void) const { return (m_tuningState & 0x80) == 0; }
	bool areCapacitiesOk(void) const { return (m_tuningState & 0x30) == 0; }

	int c1TuningState(void) const { return m_tuningState & 0x03; }
	int c2TuningState(void) const { return (m_tuningState >> 2) & 0x03; }

	std::string toString(void) const;
	
private:
	uint32_t m_c1 = -1;
	uint32_t m_c2 = -1;
	uint32_t m_r = -1;
	uint32_t m_phi = -1;
	int m_tuningState = -1;

	static std::string tuningStateToString(int cxTuningState);
	static void strPadding(std::string & str, int paddLen);
};



/// @brief DATA class with UHF power information of a UHF multiplexer
///
/// For details see the documentation of the UHF multiplexer
class FEDM_FUNIT_CLASS_DEF FunitUhfPower
{
	friend class Payload::PlFunit;

public:
	void clear(void) { *this = FunitUhfPower(); }

	bool isValid(void) const { return m_errorFlags >= 0; }

	uint32_t powerForward(void) const { return m_powerForward; }
	uint32_t powerReflected(void) const { return m_powerReflected; }

	int errorFlags(void) const { return m_errorFlags; }
	
private:
	uint32_t m_powerForward = 0;
	uint32_t m_powerReflected = 0;
	int m_errorFlags = -1;
};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_DATA_H

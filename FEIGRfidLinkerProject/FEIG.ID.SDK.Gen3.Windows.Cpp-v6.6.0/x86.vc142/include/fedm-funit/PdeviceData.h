/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_PDEVICE_DATA_H
#define FEDM_PDEVICE_DATA_H

#include <string>

#include <FedmFunitBase.h>
#include <FedmFunitHide.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief DATA class with address information of a peripheral device
class FEDM_FUNIT_CLASS_DEF PdeviceAddress
{
	friend class Payload::PlFunit;
	friend class Internal::FunitWorker;
	friend class FedmFriend;

public:
	// These values are identical to ReaderInfo::PeriphAddr::PortType...
	static const int PortTypeNone = 0;
	static const int PortTypeRs232 = 1;
	static const int PortTypeRs4xx = 2;

	void clear(void) { *this = PdeviceAddress(); }

	bool isValid(void) const { return m_portType != PortTypeNone; }
	int  portType(void) const { return m_portType; }
	int  busAddress(void) const { return m_busAddress; }

	std::string toString(void) const;

	/// @brief Create an address object for a RS232 connected peripheral device
	static PdeviceAddress createRs232Address(void);

	/// @brief Create an address object for a RS485 connected peripheral device
	static PdeviceAddress createRs485Address(int busAddress);

private:
    int m_portType = PortTypeNone;
    int m_busAddress = -1;
};



/// @brief DATA class with peripheral device informations
///
/// For details see the documentation of the peripheral device
class FEDM_FUNIT_CLASS_DEF PdeviceInfo
{
	friend class Payload::PlFunit;
	friend class FedmFriend;

public:
	static const int SwTypeHfPeopleCounter = 13;
	static const int SwTypeLed = 14;

	void clear(void) { *this = PdeviceInfo(); }

	bool isValid(void) const { return m_address.isValid(); }
	const PdeviceAddress & address(void) const { return m_address; }

	// mode 0x00
	int swType(void) const { return m_swType; }
	int hwType(void) const { return m_hwType; }
	int swMajorRevision(void) const { return m_swMajorRevision; }
	int swMinorRevision(void) const { return m_swMinorRevision; }
	int swDevelRevision(void) const { return m_swDevelRevision; }
	int rxBuffer(void) const { return m_rxBuffer; }
	int txBuffer(void) const { return m_txBuffer; }

	// mode 0x10
	int hwInfo(void) const { return m_hwInfo; }
	int dHw(void) const { return m_dHw; }
	int aHw(void) const { return m_aHw; }
	int portType(void) const { return m_portType; }

	std::string swTypeToString(void) const;
	std::string versionToString(void) const;
	std::string toString(void) const;

private:
	PdeviceAddress m_address;

	// mode 0x00
	int m_swType = -1;
	int m_hwType = -1;
	int m_swMajorRevision = -1;
	int m_swMinorRevision = -1;
	int m_swDevelRevision = -1;
	int m_rxBuffer = -1;
	int m_txBuffer = -1;

	// mode 0x10
	int m_hwInfo = -1;
	int m_dHw = -1;
	int m_aHw = -1;
	int m_portType = -1;
};



/// @brief DATA class with diagnostic information of a HF people counter device
///
/// For details see the documentation of the peripheral device
class FEDM_FUNIT_CLASS_DEF PdeviceHfPcDiag
{
	friend class Payload::PlFunit;
	friend class FedmFriend;

public:
	void clear(void) { *this = PdeviceHfPcDiag(); }

	bool isValid(void) const { return m_address.isValid(); }
	const PdeviceAddress & address(void) const { return m_address; }

	int intError(void) const { return m_intError; }
	int rfDetect(void) const { return m_rfDetect; }

	std::string toString(void) const;

private:
	PdeviceAddress m_address;

	int m_intError = -1;
	int m_rfDetect = -1;
};



/// @brief DATA class with diagnostic information of a LED device
///
/// For details see the documentation of the peripheral device
class FEDM_FUNIT_CLASS_DEF PdeviceLedDiag
{
	friend class Payload::PlFunit;
	friend class FedmFriend;

public:
	void clear(void) { *this = PdeviceLedDiag(); }

	bool isValid(void) const { return m_address.isValid(); }
	const PdeviceAddress & address(void) const { return m_address; }

	int intError(void) const { return m_intError; }
	int ledState(void) const { return m_ledState; }
	int temperature(void) const { return m_temperature; }
	int rfDetect(void) const { return m_rfDetect; }

	std::string toString(void) const;

private:
	PdeviceAddress m_address;

	int m_intError = -1;
	int m_ledState = -1;
	int m_temperature = -1;
	int m_rfDetect = -1;
};



/// @brief DATA class with people counter values
class FEDM_FUNIT_CLASS_DEF PdevicePeopleCounterValues
{
	friend class Payload::PlFunit;
	friend class FedmFriend;

public:
	void clear(void) { *this = PdevicePeopleCounterValues(); }

	bool isValid(void) const { return m_address.isValid(); }
	const PdeviceAddress & address(void) const { return m_address; }

	uint32_t detector1Counter1(void) const { return m_detector1Counter1; }
	uint32_t detector1Counter2(void) const { return m_detector1Counter2; }
	uint32_t detector2Counter1(void) const { return m_detector2Counter1; }
	uint32_t detector2Counter2(void) const { return m_detector2Counter2; }

	void setDetector1Counter1(uint32_t value) { m_detector1Counter1 = value; }
	void setDetector1Counter2(uint32_t value) { m_detector1Counter2 = value; }
	void setDetector2Counter1(uint32_t value) { m_detector2Counter1 = value; }
	void setDetector2Counter2(uint32_t value) { m_detector2Counter2 = value; }

private:
	PdeviceAddress m_address;

	uint32_t m_detector1Counter1 = 0;
	uint32_t m_detector1Counter2 = 0;
	uint32_t m_detector2Counter1 = 0;
	uint32_t m_detector2Counter2 = 0;
};



/// @brief DATA class with LED output settings
class FEDM_FUNIT_CLASS_DEF PdeviceLedOutput
{
	friend class FedmFriend;

public:
    static const int ModeOff = 0;
    static const int Mode1Hz = 1;
    static const int Mode2Hz = 2;
    static const int Mode4Hz = 4;
    static const int Mode8Hz = 8;
    static const int ModeOn = 0xFF;

	static const int ColorRed = 1;
	static const int ColorCyan = 2;
	static const int ColorMagenta = 3;
	static const int ColorBlue = 4;
	static const int ColorGreen = 5;
	static const int ColorYellow = 6;
	static const int ColorWhite = 7;

	/// @brief Constructor for an invalid output setting
	PdeviceLedOutput();

	/// @brief Constructor for a valid output setting
	/// @param[in] mode The output mode of the LED
	/// @param[in] color The color value for the LED
	/// @param[in] holdTime The hold time [msec] for the setting. Use 0 for infinite hold time.
	PdeviceLedOutput(int mode, int color, uint32_t holdTime = 0);

	void clear(void);

	bool isValid(void) const { return m_mode >= 0; }

	int      mode(void) const { return m_mode; }
	int      color(void) const { return m_color; }
	uint32_t holdTime(void) const { return m_holdTime; } // in msec (0 is infinite)

private:
	int m_mode = -1;
	int m_color = -1;
	uint32_t m_holdTime = 0;
};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_PDEVICE_DATA_H

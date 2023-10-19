/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_DIAG_EVENT_ITEM_H
#define FEDM_DIAG_EVENT_ITEM_H

#include <string>
#include <vector>

#include <FedmDateTime.h>
#include <FedmRdrDiag.h>
#include <FedmHide.h>



namespace FEDM {

/// @brief DATA class with requested Diagnostic Event data by EventType::TagEvent (command [0x2D]).
///
/// This class contains all record members, which are potentially part of the readers response of the command [0x2D].<br>
/// An item can be obtained via the data queue in group Diagnostic.
///
/// Example to use:
/// if (diagEventItem.error().rfDecoder().isOn()) {
///   // do something
/// }
class FEDM_CLASS_DEF DiagEventItem
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:

	class FEDM_CLASS_DEF FlagState
	{
		friend class FedmFriend;
	public:
		FlagState();          // Unsupported constructor
		FlagState(bool isOn); // Supported constructor

		/// @return True if flag is supported by reader.
		bool isSupportedByReader(void) const;

		/// @return True if flag is not supported by reader.
		bool isNotSupportedByReader(void) const;

		/// @return True if flag is supported by reader and flag is on.
		bool isOn(void) const;

		/// @return True if flag is not supported by reader or flag is off.
		bool isOff(void) const;

	private:
		bool m_isSupportedByReader;
		bool m_isOn;
	};


	class FEDM_CLASS_DEF SectorError
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorError();

		void clear(void);
		bool isValid(void) const;
		bool isAnyError(void) const;

		FlagState eeprom1(void) const;
		FlagState eeprom2(void) const;
		FlagState hardwareMismatch(void) const;
		FlagState filter(void) const;
		FlagState rfDecoder(void) const;
		FlagState adc(void) const;
		FlagState dac(void) const;
		FlagState rtc(void) const;
		FlagState ledC(void) const;
		FlagState pcC(void) const;
		FlagState ioExp(void) const;
		FlagState dcOut(void) const;
		FlagState usbIMax(void) const;
		FlagState init(void) const;
		FlagState hardware(void) const;

		std::string toReport(void) const;

	private:
		std::vector<uint8_t> m_errors;
		std::vector<uint8_t> m_supports;

		void reset(size_t maxBytes = 0); // set valid and reset all flags
	};


	class FEDM_CLASS_DEF SectorAlert
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorAlert();

		void clear(void);
		bool isValid(void) const;
		bool isAnyAlert(void) const;

		FlagState temperature(void) const;
		FlagState batteryEmpty(void) const;
		FlagState batteryVeryLow(void) const;
		FlagState batteryLow(void) const;

		std::string toReport(void) const;

	private:
		std::vector<uint8_t> m_alerts;
		std::vector<uint8_t> m_supports;

		void reset(size_t maxBytes = 0); // set valid and reset all flags
	};


	class FEDM_CLASS_DEF SectorWarning
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SectorWarning();

		void clear(void);
		bool isValid(void) const;
		bool isAnyWarning(void) const;

		FlagState hfHardware(void) const;
		FlagState hfNoise(void) const;
		FlagState hfImpedance(void) const;
		FlagState hfPower(void) const;
		FlagState temperature(void) const;
		FlagState hfSync(void) const;
		FlagState hfMux(void) const;
		FlagState hfDat(void) const;

		std::string toReport(void) const;

	private:
		std::vector<uint8_t> m_warnings;
		std::vector<uint8_t> m_supports;

		void reset(size_t maxBytes = 0); // set valid and reset all flags
	};


	class FEDM_CLASS_DEF AntennaState
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		static const int StateOk = 0;
		static const int StateGeneralError = 1;
		static const int StateImpLow = 10;   ///< for HF
		static const int StateImpHigh = 11;  ///< for HF
		static const int StateImpError = 12; ///< for UHF
		static const int StatePhaseError = 13;
		static const int StatePowerError = 14;

		AntennaState();

		void clear(void);
		bool isValid() const;

		uint32_t address(void) const { return m_address; }
		int      state(void) const { return m_state; }

		std::string toReport(void) const;

	private:
		uint32_t m_address;
		int      m_state;
	};


public:
	DiagEventItem();

	void clear();

	const DateTime                  & dateTime (void) const { return m_dateTime; }
	const SectorError               & error    (void) const { return m_error; }
	const SectorAlert               & alert    (void) const { return m_alert; }
	const SectorWarning             & warning  (void) const { return m_warning; }
	const std::vector<AntennaState> & hfState  (void) const { return m_hfState; }

	std::string toReport(void) const;

protected:
	DateTime                  m_dateTime;
	SectorError               m_error;
	SectorAlert               m_alert;
	SectorWarning             m_warning;
	std::vector<AntennaState> m_hfState;

	DateTime                  & dateTime (void) { return m_dateTime; }
	SectorError               & error    (void) { return m_error; }
	SectorAlert               & alert    (void) { return m_alert; }
	SectorWarning             & warning  (void) { return m_warning; }
	std::vector<AntennaState> & hfState  (void) { return m_hfState; }

}; // end of class DiagEventItem

}; // end of namespace FEDM

#endif // FEDM_DIAG_EVENT_ITEM_H

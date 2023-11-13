/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef READER_DIAG_H
#define READER_DIAG_H

#include <string>
#include <cstring>
#include <vector>

#include "FedmConst.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief DATA class with reader diagnostics
class FEDM_CLASS_DEF ReaderDiag
{
	friend class Internal::ReaderBase;
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	/// Reader and Antenna Status requested with command [0x6E] and Mode=0x01
	class FEDM_CLASS_DEF DiagStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		DiagStatus() {
			m_isValid = false;
			m_flagsA = m_flagsB = 0;
		}

		void clear() { *this = DiagStatus(); }

		bool isFlagsA_RfHardware	  (void) const { return m_flagsA & 0x01; }	///< Flags byte A, bit 0: RF-Hardware error
		bool isFlagsA_RfNoise         (void) const { return m_flagsA & 0x02; }	///< Flags byte A, bit 1: RF-Noise problem
		bool isFlagsA_RfPhaseErrorLess(void) const { return m_flagsA & 0x04; }	///< Flags byte A, bit 2: only HF Reader
		bool isFlagsA_RfPhaseErrorMore(void) const { return m_flagsA & 0x08; }	///< Flags byte A, bit 3: only HF Reader
		bool isFlagsA_RfPowerAmp      (void) const { return m_flagsA & 0x10; }	///< Flags byte A, bit 4:
		bool isFlagsA_TempWarning     (void) const { return m_flagsA & 0x20; }	///< Flags byte A, bit 5: Temperature Warning (only HF Reader)
		bool isFlagsA_SyncTimeout     (void) const { return m_flagsA & 0x40; }	///< Flags byte A, bit 6:
		bool isFlagsA_TempAlarm       (void) const { return m_flagsA & 0x80; }	///< Flags byte A, bit 7: Temperature Alarm

		bool isFlagsB_Uhf_RfPhaseErrorAnt1(void) const { return m_flagsB & 0x01; }	///< Flags byte B, bit 0: Phase Error at internal Antenna Output 1 (only UHF Reader)
		bool isFlagsB_Uhf_RfPhaseErrorAnt2(void) const { return m_flagsB & 0x02; }	///< Flags byte B, bit 1: Phase Error at internal Antenna Output 2 (only UHF Reader)
		bool isFlagsB_Uhf_RfPhaseErrorAnt3(void) const { return m_flagsB & 0x04; }	///< Flags byte B, bit 2: Phase Error at internal Antenna Output 3 (only UHF Reader)
		bool isFlagsB_Uhf_RfPhaseErrorAnt4(void) const { return m_flagsB & 0x08; }	///< Flags byte B, bit 3: Phase Error at internal Antenna Output 4 (only UHF Reader)
																					///< Flags byte B, bits 4-7: unused bits for UHF reader
		bool isFlagsB_Hf_MuxStatus (void) const { return m_flagsB & 0x01; }	///< Flags byte B, bit 0: Multiplexer status (only HF Reader)
		bool isFlagsB_Hf_DatStatus (void) const { return m_flagsB & 0x02; }	///< Flags byte B, bit 1: Dynamic Antenna Tuner status (only HF Reader)
		bool isFlagsB_Hf_DCAntError(void) const { return m_flagsB & 0x04; }	///< Flags byte B, bit 2: DC-Power error at Antenna Output (only HF Reader)

		bool isValid() const { return m_isValid; }
		uint8_t flagsA() const { return m_flagsA; }
		uint8_t flagsB() const { return m_flagsB; }

		///< Flags byte B, bits 3-7: unused bits for HF reader
		std::string toReport(uint32_t readerType) const;

	private:
		bool		m_isValid;			///< indicates valid data members
		uint8_t		m_flagsA;				///< Flags byte A
		uint8_t		m_flagsB;				///< Flags byte B

		std::string toLrUHFReport(uint32_t readerType) const;
		std::string toHfReport(uint32_t readerType) const;
		std::string toPrhReport(void) const;
	};

	/// Multiplexer Status requested with command [0x6E] and Mode=0x03
	class FEDM_CLASS_DEF ExtMuxStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		ExtMuxStatus()
		{
			m_isValid = false;
			m_data.clear();
		}

		void clear() { *this = ExtMuxStatus(); }

		bool isValid() const { return m_isValid; }
		const std::vector<uint8_t> & data() const { return m_data; }

		std::string toReport(void) const;

	private:
		bool m_isValid;			///< indicates valid data members
		std::vector<uint8_t> m_data;
	};

	/// EEPROM and FPGA Status requested with command [0x6E] and Mode=0x04
	class FEDM_CLASS_DEF ErrorAndDecoderStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		ErrorAndDecoderStatus()
		{
			m_isValid = false;
			m_intErrorA = m_intErrorB = 0;
		}

		void clear() { *this = ErrorAndDecoderStatus(); }

		bool    isValid()   const { return m_isValid; }
		uint8_t intErrorA() const { return m_intErrorA; }
		uint8_t intErrorB() const { return m_intErrorB; }

		bool isIntErrorA_IoExpander(void) const { return m_intErrorA & 0x01; }	///< Internal Error flag field A, bit 0: IO Expander error
		bool isIntErrorA_DcOut     (void) const { return m_intErrorA & 0x02; }	///< Internal Error flag field A, bit 1: DC Out error
		bool isIntErrorA_UsbImax   (void) const { return m_intErrorA & 0x04; }	///< Internal Error flag field A, bit 2: USB error
		bool isIntErrorA_Led	   (void) const { return m_intErrorA & 0x10; }	///< Internal Error flag field A, bit 2: LED LP error
		bool isIntErrorA_Tag	   (void) const { return m_intErrorA & 0x20; }	///< Internal Error flag field A, bit 2: Too much tags
		bool isIntErrorA_List	   (void) const { return m_intErrorA & 0x40; }	///< Internal Error flag field A, bit 2: List error

		bool isIntErrorB_EepromDevice1(void) const { return m_intErrorB & 0x01; }	///< Internal Error flag field B, bit 0: EEPROM error in Device 1
		bool isIntErrorB_EepromDevice2(void) const { return m_intErrorB & 0x02; }	///< Internal Error flag field B, bit 1: EEPROM error in Device 2
		bool isIntErrorB_HwFilter     (void) const { return m_intErrorB & 0x04; }	///< Internal Error flag field B, bit 2: Hardware Filter problem
		bool isIntErrorB_RfDecoder    (void) const { return m_intErrorB & 0x08; }	///< Internal Error flag field B, bit 3: RF-Decoder problem
		bool isIntErrorB_ParaMismatch (void) const { return m_intErrorB & 0x10; }	///< Internal Error flag field B, bit 4: Parameter mismatch
		bool isIntErrorB_PeopleCounter(void) const { return m_intErrorB & 0x20; }	///< Internal Error flag field B, bit 5: People Counter error
		bool isIntErrorB_RealTimeClock(void) const { return m_intErrorB & 0x40; }	///< Internal Error flag field B, bit 6: Real-Time Clock error
		bool isIntErrorB_Adc          (void) const { return m_intErrorB & 0x80; }	///< Internal Error flag field B, bit 7: ADC error

		bool isIntErrorA_HyWEARcompact_TriggerLockStatus (void) const { return m_intErrorA & 0x02; }	///< Internal Error flag field A, bit 1: Trigger lock status
		bool isIntErrorA_HyWEARcompact_Barcode           (void) const { return m_intErrorA & 0x04; }	///< Internal Error flag field A, bit 2: Barcode
		bool isIntErrorA_HyWEARcompact_WiFiBluetooth     (void) const { return m_intErrorA & 0x08; }	///< Internal Error flag field A, bit 3: WiFi / Bluetooth
		bool isIntErrorA_HyWEARcompact_AccelerationSensor(void) const { return m_intErrorA & 0x10; }	///< Internal Error flag field A, bit 4: Acceleration Sensor
		bool isIntErrorA_HyWEARcompact_Battery           (void) const { return m_intErrorA & 0x20; }	///< Internal Error flag field A, bit 5: Battery

		bool isIntErrorB_HyWEARcompact_Eeprom   (void) const { return m_intErrorB & 0x01; }	///< Internal Error flag field B, bit 0: EEPROM
		bool isIntErrorB_HyWEARcompact_RfDecoder(void) const { return m_intErrorB & 0x04; }	///< Internal Error flag field B, bit 3: RF-Decoder

		std::string toReport(uint32_t) const;

	private:
		bool	m_isValid;			///< indicates m_isValid data members
		uint8_t	m_intErrorA;		///< Internal Error flag field A
		uint8_t	m_intErrorB;		///< Internal Error flag field B

		std::string toIscanReport(uint32_t readerType) const;
		std::string toHywearReport(void) const;
	};

	/// Multiplexer Impedance Status requested with command [0x6E] and Mode=0x05 (only HF/UHF LR-Reader): Status of external Multiplexer, connected at internal Antenna Outputs
	class FEDM_CLASS_DEF ExtMuxOutStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		ExtMuxOutStatus()
		{
			m_isValid = false;
			m_data.clear();
		}

		void clear() { *this = ExtMuxOutStatus(); }
		bool isValid() const { return m_isValid; }
		const std::vector<uint8_t> & data() const { return m_data; }

		std::string toReport(uint32_t readerType) const;

	private:
		bool	m_isValid;		///< Indicates valid data members
		std::vector<uint8_t> m_data;

	};

	/// MAX Status requested with command [0x6E] and Mode=0x06
	class FEDM_CLASS_DEF MaxStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		MaxStatus() 
		{
			m_isValid = false;
			m_error = 0;
			m_eventTableCapacity = m_eventCount = 0;
		}

		void clear() { *this = MaxStatus(); }

		bool isValid() const { return m_isValid; }
		uint16_t error() const { return m_error; }
		size_t eventTableCapacity() const { return m_eventTableCapacity; }
		size_t eventCount() const { return m_eventCount; }

		bool isError_Rtc          (void) const { return m_error & 0x0001; }	///< Error flag field, bit 0: real-time clock error
		bool isError_Metadata     (void) const { return m_error & 0x0002; }	///< Error flag field, bit 1: metadata error
		bool isError_TimezoneTable(void) const { return m_error & 0x0004; }	///< Error flag field, bit 2: timezone table error
		bool isError_HolidayTable (void) const { return m_error & 0x0008; }	///< Error flag field, bit 3: holiday table error
		bool isError_AccessTable  (void) const { return m_error & 0x0010; }	///< Error flag field, bit 4: access table error
		bool isError_ReaderConfig (void) const { return m_error & 0x0040; }	///< Error flag field, bit 6: Reader configuration problem
		bool isError_TableUpdate  (void) const { return m_error & 0x0080; }	///< Error flag field, bit 7: table update problem
		bool isError_TableOverflow(void) const { return m_error & 0x0100; }	///< Error flag field, bit 8: table overflow

		std::string toReport(uint32_t readerType) const;

	private:
		bool		m_isValid;			///< indicates valid data members
		uint16_t	m_error;				///< 2 byte Error flag field
		size_t		m_eventTableCapacity;	///< Maximum number of events
		size_t		m_eventCount;			///< Number of events in table
	};

	/// ID ISC.PRH200: LED Status requested with command [0x6E] and Mode=0x07
	class FEDM_CLASS_DEF PRH200_Status
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		PRH200_Status() 
		{
			m_isValid = false;
			m_ledStateHf = m_ledStateCust = m_ledStateWlan = m_ledStateBat = m_ledStateMode = 0;
		}

		void clear() { *this = PRH200_Status(); }

		bool isValid() const { return m_isValid; }
		uint8_t ledStateHf() const { return m_ledStateHf; }
		uint8_t ledStateCust() const { return m_ledStateCust; }
		uint8_t ledStateWlan() const { return m_ledStateWlan; }
		uint8_t ledStateBat() const { return m_ledStateBat; }
		uint8_t ledStateMode() const { return m_ledStateMode; }

		std::string toReport(void) const;

	private:
		bool m_isValid;			///< indicates m_isValid data members
		uint8_t  m_ledStateHf;
		uint8_t m_ledStateCust;
		uint8_t m_ledStateWlan;
		uint8_t m_ledStateBat;
		uint8_t m_ledStateMode;

	};

	/// ID ISC.LR2500-B: Antenna Tuning Status requested with command [0x6E] and Mode=0x08
	class FEDM_CLASS_DEF LR2500B_AntTuningStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		LR2500B_AntTuningStatus() 
		{
			m_isValid = false;
			m_voltage = m_current = m_phase_mV = 0;
			m_phase_deg = 0;
		}
		void clear() { *this = LR2500B_AntTuningStatus(); }

		bool isValid() const { return m_isValid; }
		uint16_t voltage() const { return m_voltage; }
		uint16_t current() const { return m_current; }
		uint16_t phase_mV() const { return m_phase_mV; }
		int16_t phase_deg() const { return m_phase_deg; }

	private:
		bool		m_isValid;			///< indicates m_isValid data members
		uint16_t	m_voltage;			///< Antenna m_voltage in mV
		uint16_t	m_current;			///< Amplifier m_current in mA
		uint16_t	m_phase_mV;			///< Phase in mV
		int16_t		m_phase_deg;		///< Phase in degree - FIXME: really signed??? see parsing of read buffer 0x22

	};

	/// ID ISC.LRU500i Hardware Switches [0x6E] and Mode=0x09
	class FEDM_CLASS_DEF LRU500i_HardwareSwitches
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		LRU500i_HardwareSwitches()
		{
			m_isValid = false;
			m_dip = 0;
			m_settings = 0;
		}

		void clear() { *this = LRU500i_HardwareSwitches(); }

		bool isValid() const { return m_isValid; }
		uint8_t dip() const { return m_dip; }
		uint8_t settings() const { return m_settings; }

		std::string toReport(uint32_t readerType) const;

	private:
		bool	m_isValid;	///< indicates m_isValid data members
		uint8_t	m_dip;		///< 8 Bit flag field for the DIP switches
		uint8_t	m_settings;	///< 8 Bit flag field
	};

	/// Battery Status requested with command [0x6E] and Mode=0x10
	class FEDM_CLASS_DEF BatteryStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		BatteryStatus()
		{
			m_isValid = false;
			m_voltage = 0;
		}

		void clear() { *this = BatteryStatus(); }

		bool isValid() const { return m_isValid; }
		uint16_t voltage() const { return m_voltage; }

		std::string toReport(uint32_t readerType) const;

	private:
		bool		m_isValid;			///< indicates m_isValid data members
		uint16_t	m_voltage;			///< Battery Voltage in mV
	};

	/// Firmware Status requested with command [0x6E] and Mode=0x20
	class FEDM_CLASS_DEF FwStatus
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		FwStatus() 
		{
			m_isValid = false;
			m_statusText.clear();
		}

		void clear() { *this = FwStatus(); }

		bool isValid() const { return m_isValid; }
		std::string statusText() const { return m_statusText; }

		std::string toReport() const;

	private:
		bool		m_isValid;			///< indicates m_isValid data members
		std::string	m_statusText;		///< Firmware status text
	};

	/// Config-Para Change requested with command [0x6E] and Mode=0x21
	class FEDM_CLASS_DEF CfgChange
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		CfgChange() 
		{
			m_isValid = false;
			m_status = 0;
		}

		void clear() { *this = CfgChange(); }

		bool isValid() const { return m_isValid; }
		uint8_t status() const { return m_status; }

		std::string toReport() const;

	private:
		bool		m_isValid;			///< indicates valid data members
		uint8_t		m_status;				///< Status of reader's configuration after last firmware update
	};

	ReaderDiag();
	ReaderDiag(uint32_t readerType);
	~ReaderDiag();

	void clear();

	/// @return A report with complete reader diagnostic
	std::string getReport() const;

	/// @return A partial report of the given reader diagnostic mode
	std::string getPartialReport(int mode) const;

	uint32_t readerType() const { return m_readerType; }

	const DiagStatus & diagStatus() const { return m_diagStatus; }
	const ExtMuxStatus & extMuxStatus() const { return m_extMuxStatus; }
	const ErrorAndDecoderStatus & errorAndDecoderStatus() const { return m_errorAndDecoderStatus; }
	const ExtMuxOutStatus & extMuxOutStatus() const { return m_extMuxOutStatus; }
	const MaxStatus & maxStatus() const { return m_maxStatus; }
	const PRH200_Status & prh200_Status() const { return m_prh200_Status; }
	const LR2500B_AntTuningStatus & lr2500b_AntTuningStatus() const { return m_lr2500b_AntTuningStatus; }
	const LRU500i_HardwareSwitches & lru500i_HardwareSwitches() const { return m_lru500i_HardwareSwitches; }
	const BatteryStatus & batteryStatus() const { return m_batteryStatus; }
	const FwStatus & fwStatus() const { return m_fwStatus; }
	const CfgChange & cfgChange() const { return m_cfgChange; }

	DiagStatus & diagStatus() { return m_diagStatus; }
	ExtMuxStatus & extMuxStatus() { return m_extMuxStatus; }
	ErrorAndDecoderStatus & errorAndDecoderStatus() { return m_errorAndDecoderStatus; }
	ExtMuxOutStatus & extMuxOutStatus() { return m_extMuxOutStatus; }
	MaxStatus & maxStatus() { return m_maxStatus; }
	PRH200_Status & prh200_Status() { return m_prh200_Status; }
	LR2500B_AntTuningStatus & lr2500b_AntTuningStatus() { return m_lr2500b_AntTuningStatus; }
	LRU500i_HardwareSwitches & lru500i_HardwareSwitches() { return m_lru500i_HardwareSwitches; }
	BatteryStatus & batteryStatus() { return m_batteryStatus; }
	FwStatus & fwStatus() { return m_fwStatus; }
	CfgChange & cfgChange() { return m_cfgChange; }

private:
	uint32_t m_readerType;

	DiagStatus m_diagStatus;
	ExtMuxStatus m_extMuxStatus;
	ErrorAndDecoderStatus m_errorAndDecoderStatus;
	ExtMuxOutStatus m_extMuxOutStatus;
	MaxStatus m_maxStatus;
	PRH200_Status m_prh200_Status;
	LR2500B_AntTuningStatus m_lr2500b_AntTuningStatus;
	LRU500i_HardwareSwitches m_lru500i_HardwareSwitches;
	BatteryStatus m_batteryStatus;
	FwStatus m_fwStatus;
	CfgChange m_cfgChange;

}; // end of class ReaderDiagnostic
}; // end of namespace FEDM

#endif // READER_DIAG_H

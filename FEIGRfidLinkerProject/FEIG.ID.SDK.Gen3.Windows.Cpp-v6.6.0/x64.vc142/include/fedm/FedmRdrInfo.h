/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef READER_INFO_H
#define READER_INFO_H

#include <string>
#include <vector>
#include <array>

#include "FedmConst.h"
#include "FedmHide.h"
#include <FedmNetAddr.h>
#include <FedmCfgId.h>



namespace FEDM {

/// @brief DATA class with reader informations
class FEDM_CLASS_DEF ReaderInfo
{
	friend class Payload::PlBase;
	friend class Internal::ReaderBase;
	friend class FedmFriend;

public:
	 ReaderInfo();
	 ~ReaderInfo();

	void clear();

	uint32_t    readerType(void) const { return rfcFw().readerType(); }
	std::string readerTypeToString(void) const { return ReaderType::toString(readerType()); }

	uint32_t	deviceId(void) const;
	std::string deviceIdToHexString(void) const;

	/// Returns a report with complete reader information
	std::string getReport() const;

	/// Returns a partial report of the given reader information mode
	std::string getPartialReport(int mode) const;

	/// Information from RF-Controller requested with command [0x66] and Mode=0x00
	class FEDM_CLASS_DEF RfcFw
	{
		friend class Payload::PlBase;
		friend class Internal::ReaderBase;
		friend class FedmFriend;

	public:
		RfcFw() {
			m_isValid = false;
			m_majVer = 0;
			m_minVer = 0;
			m_devVer = 0;
			m_hwType = 0;
			m_swType = 0;
			m_trType = 0;
			m_rxBufferSize = 0;
			m_txBufferSize = 0;
			m_uhfTrType = 0;
			m_readerRevision = 0;
			m_readerAssembly = 0;
			m_frameSupport = 0;
			m_configId = FEDM::ConfigId();
		}
		void clear() {*this = RfcFw(); }

		uint32_t readerType(void) const {
			return (static_cast<uint32_t>(m_readerAssembly) << 8) |
			        static_cast<uint32_t>(m_swType);
		}

		/// @return True, if Reader is part of IDENTIFICATION HF family (ISO 14443, ISO 15693 and ISO 18000-3M3)
		bool isHfReader() const { return ReaderType::isHfReader(readerType()); }
		/// @return True, if Reader is part of IDENTIFICATION UHF family (EPC Class1 Gen2)
		bool isUhfReader() const { return ReaderType::isUhfReader(readerType()); }

		/// @return True, if Reader can handle ISO 14443 transponder
		bool isISO14443Reader() const { return ReaderType::isISO14443Reader(readerType()); }
		/// @return True, if Reader can handle ISO 15693 transponder
		bool isISO15693Reader() const { return ReaderType::isISO15693Reader(readerType()); }
		/// @return True, if Reader can handle ISO 18000-3M3 transponder
		bool isISO180003m3Reader() const { return ReaderType::isISO180003m3Reader(readerType()); }
		/// @return True, if Reader can handle EPC Class1 Gen2 transponder
		bool isEPCC1G2Reader() const { return ReaderType::isEPCC1G2Reader(readerType()); }

		std::string versionToString(void) const;
		std::string toReport(uint32_t readerType) const;

		bool isValid() const { return m_isValid; }					///< indicates valid data members
		uint8_t majVer() const { return m_majVer; }					///< major version number of RFC
		uint8_t minVer() const { return m_minVer; }					///< minor version number of RFC
		uint8_t devVer() const { return m_devVer; }					///< developer version number of RFC
		uint8_t hwType() const { return m_hwType; }					///< flag field with hardware options of RFC
		uint8_t swType() const { return m_swType; }					///< reader type, low byte
		uint16_t trType() const { return m_trType; }				///< flag field with supported Transponder types
		size_t rxBufferSize() const { return m_rxBufferSize; }		///< size of Reader's receive buffer
		size_t txBufferSize() const { return m_txBufferSize; }		///< size of Reader's transmit buffer
		uint16_t uhfTrType() const { return m_uhfTrType; }			///< additional flag field with supported UHF Transponder types
		uint8_t readerRevision() const { return m_readerRevision; }	///< additional reader information
		uint8_t readerAssembly() const { return m_readerAssembly; }	///< reader type, high byte
		bool isFrameSupportUnknown   (void) const { return m_frameSupport == 0x00; }		///< invalid protocol frame support information
		bool isAdvancedFrameSupported(void) const { return (m_frameSupport & 0x02) != 0; }	///< reader supports advanced protocol frame
		bool isEnhancedFrameSupported(void) const { return (m_frameSupport & 0x04) != 0; }	///< reader supports enhanced protocol frame
		FEDM::ConfigId configId(void) const { return m_configId; }	///< configuration version information

	private:
		bool		m_isValid;
		uint8_t		m_majVer;
		uint8_t		m_minVer;
		uint8_t		m_devVer;
		uint8_t		m_hwType;
		uint8_t		m_swType;
		uint16_t	m_trType;
		size_t		m_rxBufferSize;
		size_t		m_txBufferSize;
		uint16_t	m_uhfTrType;
		uint8_t		m_readerRevision;
		uint8_t		m_readerAssembly;
		uint8_t     m_frameSupport;
		FEDM::ConfigId m_configId;
	};

	/// Information from AC-Controller requested with command [0x66] and Mode=0x01
	class FEDM_CLASS_DEF AccFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		AccFw() {
			m_isValid = false;
			m_majVer = 0;
			m_minVer = 0;
			m_devVer = 0;
			m_hwType = 0;
			m_embAppMajVer = 0;
			m_embAppMinVer = 0;
			m_embAppDevVer = 0;
		}
		void clear() { *this = AccFw(); }

		bool isValid() const { return m_isValid; }				///< indicates valid data members
		uint8_t majVer() const { return m_majVer; }				///< major version number of ACC
		uint8_t minVer() const { return m_minVer; }				///< minor version number of ACC
		uint8_t devVer() const { return m_devVer; }				///< developer version number of ACC
		uint8_t hwType() const { return m_hwType; }				///< flag field with hardware options of ACC
		uint8_t embAppMajVer() const { return m_embAppMajVer; }	///< major version number of 2nd embedded application inside ACC
		uint8_t embAppMinVer() const { return m_embAppMinVer; }	///< minor version number of 2nd embedded application inside ACC
		uint8_t embAppDevVer() const { return m_embAppDevVer; }	///< developer version number of 2nd embedded application inside ACC

		std::string versionToString(bool embApp) const;
		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_majVer;
		uint8_t     m_minVer;
		uint8_t		m_devVer;
		uint8_t		m_hwType;
		uint8_t		m_embAppMajVer;
		uint8_t		m_embAppMinVer;
		uint8_t		m_embAppDevVer;
	};

	/// Information from USB-Controller requested with command [0x66] and Mode=0x02
	class FEDM_CLASS_DEF UsbFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		UsbFw() {
			m_isValid = false;
			m_majVer = 0;
			m_minVer = 0;
			m_devVer = 0;
			m_hwType = 0;
		}
		void clear() { *this = UsbFw(); }

		bool isValid() const { return m_isValid; }	///< indicates valid data members
		uint8_t majVer() const { return m_majVer; }	///< major version number of USB controller
		uint8_t minVer() const { return m_minVer; }	///< minor version number of USB controller
		uint8_t devVer() const { return m_devVer; }	///< developer version number of USB controller
		uint8_t hwType() const { return m_hwType; }	///< flag field with hardware options of USB controller

		std::string versionToString(void) const;
		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_majVer;
		uint8_t		m_minVer;
		uint8_t		m_devVer;
		uint8_t		m_hwType;
	};

	/// HF-Decoder / FPGA information requested with command [0x66] and Mode=0x03
	class FEDM_CLASS_DEF RfDecoder
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		RfDecoder() {
			m_isValid = false;
		}
		void clear() { *this = RfDecoder(); }

		bool isValid() const { return m_isValid; }			///< indicates valid data members
		const std::vector<uint8_t> & data() const { return m_data; }

		std::string toReport(uint32_t readerType) const;

	private:
		bool m_isValid;
		std::vector<uint8_t> m_data;

		std::string fpga_decoder(uint32_t readerType) const;
		std::string impinj_decoder(void) const;
		std::string nxp_old_decoder(void) const;
		std::string nxp_asic_decoder(void) const;
	};

	/// Additional firmware functionality requested with command [0x66] and Mode=0x04
	class FEDM_CLASS_DEF FwFunction
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		FwFunction() {
			m_isValid = false;
		}
		void clear() { *this = FwFunction(); }

		std::string toReport(uint32_t readerType) const;

		bool isValid() const { return m_isValid; }	///< indicates valid data members
		const std::vector<uint8_t> & data() const { return m_data; }

	private:
		bool m_isValid;			///< indicates valid data members
		std::vector<uint8_t> m_data;

		std::string mu02FwFunctions(void) const;
		std::string lru300FwFunctions(void) const;
		std::string templateFwFunctions(void) const;
		std::string cprFwFunctions(void) const;
		std::string defFwFunctions(void) const;
	};

	/// Information from bootloader requested with command [0x66] and Mode=0x05
	class FEDM_CLASS_DEF BootFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		BootFw() {
			m_isValid = false;
			m_majVer = 0;
			m_minVer = 0;
			m_devVer = 0;
		}
		void clear() { *this = BootFw(); }

		bool isValid() const { return m_isValid; }	///< indicates valid data members
		uint8_t majVer() const { return m_majVer; }	///< major version number of Bootloader
		uint8_t minVer() const { return m_minVer; }	///< minor version number of Bootloader
		uint8_t devVer() const { return m_devVer; }	///< developer version number of Bootloader

		std::string versionToString(void) const;
		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_majVer;
		uint8_t		m_minVer;
		uint8_t		m_devVer;
	};

	/// Information from keyboard unit requested with command [0x66] and Mode=0x06
	class FEDM_CLASS_DEF KeyboardFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		KeyboardFw() {
			m_isValid = false;
			m_status = 0;
			m_majVer = 0;
			m_minVer = 0;
			m_hwVer = 0;
		}
		void clear() { *this = KeyboardFw(); }

		bool isValid() const { return m_isValid; }		///< indicates valid data members
		uint16_t status() const { return m_status; }	///< 2 byte with status flags of Keyboard
		uint8_t majVer() const { return m_majVer; }		///< major version number of Keyboard
		uint8_t minVer() const { return m_minVer; }		///< minor version number of Keyboard
		uint32_t hwVer() const { return m_hwVer; }		///< hardware version of Keyboard

		std::string toReport(void) const;
		std::string versionToString(void) const;

	private:
		bool		m_isValid;
		uint16_t	m_status;
		uint8_t		m_majVer;
		uint8_t		m_minVer;
		uint32_t	m_hwVer;
	};

	/// Information from CPRIO unit requested with command [0x66] and Mode=0x07
	class FEDM_CLASS_DEF CprioFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		CprioFw() {
			m_isValid = false;
			m_majVer = 0;
			m_minVer = 0;
			m_hwVer = 0;
			m_noOfInputs = 0;
			m_noOfOutputs = 0;
			m_noOfRelays = 0;
			m_noOfSignalers = 0;
		}
		void clear() { *this = CprioFw(); }

		bool isValid() const { return m_isValid; }					///< indicates valid data members
		uint8_t majVer() const { return m_majVer; }					///< major version number of CPRIO
		uint8_t minVer() const { return m_minVer; }					///< minor version number of CPRIO
		uint8_t hwVer() const { return m_hwVer; }					///< hardware revison number of CPRIO
		uint8_t noOfInputs() const { return m_noOfInputs; }			///< number of inputs of CPRIO
		uint8_t noOfOutputs() const { return m_noOfOutputs; }		///< number of outputs of CPRIO
		uint8_t noOfRelays() const { return m_noOfRelays; }			///< number of relays of CPRIO
		uint8_t noOfSignalers() const { return m_noOfSignalers; }	///< number of signalers of CPRIO

		std::string versionToString(void) const;
		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_majVer;
		uint8_t		m_minVer;
		uint8_t		m_hwVer;
		uint8_t		m_noOfInputs;
		uint8_t		m_noOfOutputs;
		uint8_t		m_noOfRelays;
		uint8_t		m_noOfSignalers;

	};

	/// Information with supported tag drivers requested with command [0x66] and Mode=0x08
	class FEDM_CLASS_DEF CprTrDriver
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		CprTrDriver() {
			m_isValid = false;
		}
		void clear() { *this = CprTrDriver(); }

		bool isValid() const { return m_isValid; }													///< indicates valid data members
		const std::vector<uint8_t> & supportedTagDriver() const { return m_supportedTagDriver; }	///< with firmware supported tag drivers

		std::string toReport(void) const;

	private:
		bool m_isValid;
		std::vector<uint8_t> m_supportedTagDriver;
	};

	/// Command=[0x66] Mode=[0x09]: WLAN Info
	class FEDM_CLASS_DEF WifiFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;
	public:
		WifiFw() {
			m_isValid = false;
		}
		void clear() { *this = WifiFw(); }

		bool isValid() const { return m_isValid; }			///< indicates valid m_data members
		const std::vector<uint8_t> & data() const { return m_data; }

		std::string toReport(uint32_t readerType) const;

	private:
		bool m_isValid;
		std::vector<uint8_t> m_data;

		std::string wifiRs9116(void) const;
		std::string wifiBluegiga(void) const;

	};

	/// Command=[0x66] Mode=[0x0A]: Bluetooth Info
	class FEDM_CLASS_DEF Bluetooth
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		Bluetooth() {
			m_isValid = false;
		}
		void clear() { *this = Bluetooth(); }

		bool isValid() const { return m_isValid; }			///< indicates valid m_data members
		const std::vector<uint8_t> & data() const { return m_data; }

		std::string toReport(uint32_t readerType) const;

	private:
		bool m_isValid;
		std::vector<uint8_t> m_data;

		std::string btBluegiga(void) const;
	};

	/// Command=[0x66] Mode=[0x0B]: Barcode Info
	class FEDM_CLASS_DEF BarcodeFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		BarcodeFw() {
			m_isValid = false;
		}
		void clear() { *this = BarcodeFw(); }

		bool isValid() const { return m_isValid; }			///< indicates valid m_data members
		const std::vector<uint8_t> & data() const { return m_data; }

		std::string toReport (uint32_t readerType, uint8_t rfcFwMajVer, uint8_t rfcFwMinVer) const;

	private:
		bool m_isValid;
		std::vector<uint8_t> m_data;
		std::string bc2dNewland(void) const;
	};

	/// Hardware information of RF-Controller requested with command [0x66] and Mode=0x10
	class FEDM_CLASS_DEF HwInfo
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		HwInfo() {
			m_isValid = false;
			m_hwInfo = 0;
			m_dHw = 0;
			m_aHw = 0;
			m_frequency = 0;
			m_portTypes = 0;
			m_reserved.fill(0);
			m_mlcBattState = 0;
			m_rfcInfo = 0;
		}
		void clear() { *this = HwInfo(); }

		bool isValid() const { return m_isValid; }								///< indicates valid data members
		uint16_t hwInfo() const { return m_hwInfo; }							///< flag field with hardware info
		uint16_t dHw() const { return m_dHw; }									///< for internal use
		uint16_t aHw() const { return m_aHw; }									///< for internal use
		uint8_t frequency() const { return m_frequency; }						///< frequency information (HF, UHF, .., EU, FCC)
		uint8_t portTypes() const { return m_portTypes; }						///< flag field with supported port types
		const std::array<uint8_t, 3> reserved() const { return m_reserved; }	///< reserved bytes
		uint8_t rfcInfo() const { return m_rfcInfo; }							///< RFC info
		uint8_t mlcBattState() const { return m_mlcBattState; }					///< only for MLC BATT Status

		std::string toReport(uint32_t, bool) const;

	private:
		bool		m_isValid;
		uint16_t	m_hwInfo;
		uint16_t	m_dHw;
		uint16_t	m_aHw;
		uint8_t		m_frequency;
		uint8_t		m_portTypes;
		std::array<uint8_t, 3> m_reserved;
		uint8_t		m_rfcInfo;
		uint8_t		m_mlcBattState;
	};

	/// SAM information of RC-Controller requested with command [0x66] and Mode=0x11
	class FEDM_CLASS_DEF SamInfo
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		SamInfo() {
			m_isValid = false;
		}
		void clear() { *this = SamInfo(); }

		bool isValid() const { return m_isValid; }								///< indicates valid m_data members
		const std::vector<uint8_t> & slotInfo() const { return m_slotInfo; }	///< slot info for each SAM

		std::string toReport(void) const;

	private:
		bool m_isValid;
		std::vector<uint8_t> m_slotInfo;
	};

	/// General CPU information of RF-Controller requested with command [0x66] and Mode=0x12
	class FEDM_CLASS_DEF CpuInfo
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		CpuInfo() {
			m_isValid = false;
			m_manufacturerId = 0;
			m_cpuTypeId = 0;
			m_revision = 0;
			m_flashSize = 0;
		}
		void clear() { *this = CpuInfo(); }

		bool isValid() const { return m_isValid; }					///< indicates valid data members
		uint8_t manufacturerId() const { return m_manufacturerId; }	///< manufacturer id
		uint16_t cpuTypeId() const { return m_cpuTypeId; }			///< cpu type id
		uint8_t revision() const { return m_revision; }				///< cpu revision code
		size_t flashSize() const { return m_flashSize; }			///< size in KB of flash

		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_manufacturerId;
		uint16_t	m_cpuTypeId;
		uint8_t		m_revision;
		size_t		m_flashSize;
	};

	/// RF-Stack Firmware Version requested with command [0x66] and Mode=0x15
	class FEDM_CLASS_DEF RfStackFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		RfStackFw() {
			m_isValid = false;
			m_rfStackMajVer = 0;
			m_rfStackMinVer = 0;
			m_iso7816StackMajVer = 0;
			m_iso7816StackMinVer = 0;
		}
		void clear() { *this = RfStackFw(); }

		bool isValid() const { return m_isValid; }							///< indicates valid data members
		uint8_t rfStackMajVer()      const { return m_rfStackMajVer; }		///< major version number of RF-Stack
		uint8_t rfStackMinVer()      const { return m_rfStackMinVer; }		///< minor version number of RF-Stack
		uint8_t iso7816StackMajVer() const { return m_iso7816StackMajVer; }	///< major version number of ISO7816-Stack
		uint8_t iso7816StackMinVer() const { return m_iso7816StackMinVer; }	///< minor version number of ISO7816-Stack

		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_rfStackMajVer;
		uint8_t		m_rfStackMinVer;
		uint8_t		m_iso7816StackMajVer;
		uint8_t		m_iso7816StackMinVer;
	};

	/// IDT Firmware Version requested with command [0x66] and Mode=0x16
	class FEDM_CLASS_DEF IdtFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		IdtFw() {
			m_isValid = false;
			m_majVer = 0;
			m_minVer = 0;
		}
		void clear() { *this = IdtFw(); }

		bool isValid() const { return m_isValid; }	///< indicates valid data members
		uint8_t majVer() const { return m_majVer; }	///< major version number of IDT Firmware
		uint8_t minVer() const { return m_minVer; }	///< minor version number of IDT Firmware

		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_majVer;
		uint8_t		m_minVer;
	};

	/// Firmware operating system and firmware app bundle version requested with command [0x66] and Mode=0x20
	class FEDM_CLASS_DEF OsFw
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		OsFw() {
			m_isValid = false;
			m_majFwOsVer = m_minFwOsVer = m_devFwOsVer = 0;
			m_majFwAppVer = m_minFwAppVer = m_devFwAppVer = 0;
		}
		void clear() { *this = OsFw(); }

		bool isValid() const { return m_isValid; }				///< indicates valid data members
		uint8_t majFwOsVer()  const { return m_majFwOsVer; }	///< major version number of firmware OS
		uint8_t minFwOsVer()  const { return m_minFwOsVer; }	///< minor version number of firmware OS
		uint8_t devFwOsVer()  const { return m_devFwOsVer; }	///< devel version number of firmware OS
		uint8_t majFwAppVer() const { return m_majFwAppVer; }	///< major version number of firmware app bundle
		uint8_t minFwAppVer() const { return m_minFwAppVer; }	///< minor version number of firmware app bundle
		uint8_t devFwAppVer() const { return m_devFwAppVer; }	///< devel version number of firmware app bundle

		std::string toReport() const;

	private:
		bool		m_isValid;
		uint8_t		m_majFwOsVer;
		uint8_t		m_minFwOsVer;
		uint8_t		m_devFwOsVer;
		uint8_t		m_majFwAppVer;
		uint8_t		m_minFwAppVer;
		uint8_t		m_devFwAppVer;
	};

	/// CFG information with read and write permission requested with command [0x66] and Mode=0x40 and Mode=0x41
	class FEDM_CLASS_DEF CfgInfo
	{
		friend class Payload::PlBase;
		friend class Internal::ReaderBase;
		friend class FedmFriend;

	public:
		CfgInfo() {
			m_isValid = false;
			m_noOfCfgPages = 0;
		}
		void clear() { *this = CfgInfo(); }

		bool isValid() const { return m_isValid; }									///< indicates m_isValid data members
		size_t noOfCfgPages() const { return m_noOfCfgPages; }						///< number of configuration pages
		const std::vector<uint8_t> & permissions() const { return m_permissions; }	///< flag field with permitted CFG pages

		bool isPagePermitted(size_t cfgPage) const;
		std::string toReport(bool) const;

	private:
		bool m_isValid;
		size_t m_noOfCfgPages;
		std::vector<uint8_t> m_permissions;

		void setNoOfCfgPages(size_t pageCount);
		void setPagePermitted(size_t cfgPage, bool perm = true);
	};

	/// Class definition for LAN and WLAN information
	class FEDM_CLASS_DEF LanParam
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		LanParam() {
			m_ethFlags = 0;
			m_isWifi = false;
			m_isMacValid = false;
			m_ethInfo = 0;
			m_isIpAddressValid = false;
			m_isNetMaskValid = false;
			m_isGatewayValid = false;
		}

		void clear() { *this = LanParam(); }

		bool isIpV4Supported() const { return (m_ethFlags & 0x02) != 0; }
		bool isIpV4Disabled() const  { return (m_ethFlags & 0x08) != 0; }
		bool isIpV4Dhcp() const      { return (m_ethFlags & 0x20) != 0; }

		bool isIpV6Supported() const { return (m_ethFlags & 0x01) != 0; }
		bool isIpV6Disabled() const  { return (m_ethFlags & 0x04) != 0; }
		bool isIpV6Dhcp() const      { return (m_ethFlags & 0x10) != 0; }

		const uint8_t ethFlags() const { return m_ethFlags; }
		const bool isWifi() const { return m_isWifi; }
		const uint8_t ethInfo() const { return m_ethInfo; }	///< Speed and duplex mode of eth ( only valid if isMacValid() and not isWifi() )

		bool isMacValid() const { return m_isMacValid; }	///< indicates valid ethFlags and MAC address
		const MacAddress & mac() const { return m_mac; }	///< MAC address

		bool isAutoNegotiation() const { return (m_ethInfo & 0x01) == 0; }
		bool isFullDuplexMode() const  { return (m_ethInfo & 0x02) != 0; }
		bool isSpeed100Mbit() const    { return (m_ethInfo & 0x04) != 0; }

		bool isIpAddressValid() const { return m_isIpAddressValid; } ///< indicates valid IP address information
		const IpV4Address & ipAddressV4() const { return m_ipAddressV4; }
		const IpV6Address & ipAddressV6() const { return m_ipAddressV6; }

		bool isNetMaskValid() const { return m_isNetMaskValid; } ///< indicates valid NetMask information
		const IpV4Address & netMaskV4() const { return m_netMaskV4; }
		const IpV6Address & netMaskV6() const { return m_netMaskV6; }

		bool isGatewayValid() const { return m_isGatewayValid; } ///< indicates valid gateway information
		const IpV4Address & gatewayV4() const { return m_gatewayV4; }
		const IpV6Address & gatewayV6() const { return m_gatewayV6; }

		std::string toReport(void) const;

	private:
		uint8_t     m_ethFlags;
		bool        m_isWifi;

		bool        m_isMacValid;
		MacAddress  m_mac;
		uint8_t     m_ethInfo;

		bool        m_isIpAddressValid;
		IpV4Address m_ipAddressV4;
		IpV6Address m_ipAddressV6;

		bool        m_isNetMaskValid;
		IpV4Address m_netMaskV4;
		IpV6Address m_netMaskV6;

		bool        m_isGatewayValid;
		IpV4Address m_gatewayV4;
		IpV6Address m_gatewayV6;
	};

	/// Command=[0x66] Mode=[0x58]: Bluetooth Connection
	class FEDM_CLASS_DEF BluetoothConnection
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		BluetoothConnection() {
			m_isValid = false;
			m_flags = 0x00;
			m_mac.fill(0x00);
		}
		void clear() { *this = BluetoothConnection(); }

		bool isValid() const { return m_isValid; }						///< indicates valid data members

		uint8_t flags() const { return m_flags; }						///< flags
		const std::array<uint8_t, 6> & mac() const { return m_mac; }	///< MAC address

		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t     m_flags;
		std::array<uint8_t, 6> m_mac;
	};

	/// Input/output capabilities information requested with command [0x66] and Mode=0x60
	class FEDM_CLASS_DEF IOCap
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		IOCap() {
			m_isValid = false;
			m_noOfInputs = 0;
			m_noOfOutputs = 0;
			m_noOfRelays = 0;
		}
		void clear() { *this = IOCap(); }

		bool isValid() const { return m_isValid; }				///< indicates valid data members
		uint8_t noOfInputs() const { return m_noOfInputs; }		///< number of inputs
		uint8_t noOfOutputs() const { return m_noOfOutputs; }	///< number of outputs
		uint8_t noOfRelays() const { return m_noOfRelays; }		///< number of relays

		std::string toReport(void) const;

	private:
		bool		m_isValid;
		uint8_t		m_noOfInputs;
		uint8_t		m_noOfOutputs;
		uint8_t		m_noOfRelays;
	};

	/// External peripheral devices information requested with command [0x66] and Mode=0x61
	class FEDM_CLASS_DEF PeriphAddr
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		static const uint8_t TypeNone = 0;
		static const uint8_t TypeHfPeopleCounter = 1;
		static const uint8_t TypeExternalIO = 2;
		static const uint8_t TypeLed = 3;
		static const uint8_t TypeUhfPeopleCounter = 4;

		static const uint8_t PortTypeNone = 0;
		static const uint8_t PortTypeRs232 = 1;
		static const uint8_t PortTypeRs4xx = 2;

		uint8_t portType(void) const
		{
			switch (m_type) {
			case TypeHfPeopleCounter:
			case TypeExternalIO:
			case TypeLed:
				return PortTypeRs4xx;

			case TypeUhfPeopleCounter:
				return PortTypeRs232;

			default:
				return PortTypeNone;
			}
		}

		uint8_t type() const { return m_type; }
		uint8_t busAddr() const { return m_busAddr; }

	private:
		uint8_t m_type = TypeNone;
		uint8_t m_busAddr = PortTypeNone;
	};

	/// External peripheral devices information requested with command [0x66] and Mode=0x61
	class FEDM_CLASS_DEF PeriphDev
	{
		friend class Payload::PlBase;
		friend class FedmFriend;

	public:
		PeriphDev() { m_isValid = false; }
		void clear() { *this = PeriphDev(); }

		bool isValid() const { return m_isValid; }				///< indicates valid data members
		const std::vector<PeriphAddr> & addresses() const { return m_addresses; }

		std::string toReport(void) const;

	private:
		bool		m_isValid;
		std::vector<PeriphAddr> m_addresses;
	};

	/// Device information of RF-Controller requested with command [0x66] and Mode=0x80 and Mode=0x81
	class FEDM_CLASS_DEF DeviceInfo
	{
		friend class Payload::PlBase;
		friend class Internal::ReaderBase;
		friend class FedmFriend;

	public:
		DeviceInfo() {
			m_isValid = false;
			m_deviceId = 0;
			m_licenseCustom = 0;
			m_licenseFw = 0;
			m_licenseTrType = 0;
			m_licenseFct = 0;
			m_licenseUhfTrType = 0;
			m_licenseUhfFct = 0;
			m_scannerId.clear();
			m_isValidScannerId = false;
		}
		void clear() { *this = DeviceInfo();}

		bool isValid() const { return m_isValid; }							///< indicates valid data members
		uint32_t deviceId() const { return m_deviceId; }					///< Device-ID (serial number)
		uint32_t licenseCustom() const { return m_licenseCustom; }			///< licensed customer version
		uint16_t licenseFw() const { return m_licenseFw; }					///< licensed firmware version
		uint16_t licenseTrType() const { return m_licenseTrType; }			///< licensed transponder driver
		uint16_t licenseFct() const { return m_licenseFct; }				///< licensed functions
		uint16_t licenseUhfTrType() const { return m_licenseUhfTrType; }	///< licensed uhf transponder driver (for dual frequency reader)
		uint16_t licenseUhfFct() const { return m_licenseUhfFct; }			///< licensed uhf functions (for dual frequency reader)

		bool isValidScannerId() const { return m_isValidScannerId; }		///< indicates valid scanner ID
		std::string scannerId() const { return m_scannerId; }				///< user configurable scanner ID

		std::string toReport(uint32_t) const;

	private:
		bool		m_isValid;
		uint32_t	m_deviceId;
		uint32_t	m_licenseCustom;
		uint16_t	m_licenseFw;
		uint16_t	m_licenseTrType;
		uint16_t	m_licenseFct;
		uint16_t	m_licenseUhfTrType;
		uint16_t	m_licenseUhfFct;

		bool        m_isValidScannerId;
		std::string	m_scannerId;

	};

	const RfcFw & rfcFw() const { return m_rfcFw; }
	const AccFw & accFw() const { return m_accFw; }
	const UsbFw & usbFw() const { return m_usbFw; }
	const RfDecoder & rfDecoder() const { return m_rfDecoder; }
	const FwFunction & fwFunction() const { return m_fwFunction; }
	const BootFw & bootFw() const { return m_bootFw; }
	const KeyboardFw & keyboardFw() const { return m_keyboardFw; }
	const CprioFw & cprioFw() const { return m_cprioFw; }
	const CprTrDriver & cprTrDriver() const { return m_cprTrDriver; }
	const WifiFw & wifiFw() const { return m_wifiFw; }
	const Bluetooth & bluetooth() const { return m_bluetooth; }
	const BarcodeFw & barcodeFw() const { return m_barcodeFw; }
	const HwInfo & hwInfo() const { return m_hwInfo; }
	const SamInfo & samInfo() const { return m_samInfo; }
	const CpuInfo & cpuInfo() const { return m_cpuInfo; }
	const RfStackFw & rfStackFw() const { return m_rfStackFw; }
	const IdtFw & idtFw() const { return m_idtFw; }
	const OsFw & osFw() const { return m_osFw; }
	const CfgInfo & rdCfgInfo() const { return m_rdCfgInfo; }
	const CfgInfo & wrCfgInfo() const { return m_wrCfgInfo; }
	const LanParam & lanInfo() const { return m_lanInfo; }
	const LanParam & wlanInfo() const { return m_wlanInfo; }
	const BluetoothConnection & bluetoothConnection() const { return m_bluetoothConnection; }
	const IOCap & ioCap() const { return m_ioCap; }
	const PeriphDev & periphDev() const { return m_periphDev; }
	const DeviceInfo & deviceInfo() const { return m_deviceInfo; }

	RfcFw & rfcFw() { return m_rfcFw; }
	AccFw & accFw() { return m_accFw; }
	UsbFw & usbFw() { return m_usbFw; }
	RfDecoder & rfDecoder() { return m_rfDecoder; }
	FwFunction & fwFunction() { return m_fwFunction; }
	BootFw & bootFw() { return m_bootFw; }
	KeyboardFw & keyboardFw() { return m_keyboardFw; }
	CprioFw & cprioFw() { return m_cprioFw; }
	CprTrDriver & cprTrDriver() { return m_cprTrDriver; }
	WifiFw & wifiFw() { return m_wifiFw; }
	Bluetooth & bluetooth() { return m_bluetooth; }
	BarcodeFw & barcodeFw() { return m_barcodeFw; }
	HwInfo & hwInfo() { return m_hwInfo; }
	SamInfo & samInfo() { return m_samInfo; }
	CpuInfo & cpuInfo() { return m_cpuInfo; }
	RfStackFw & rfStackFw() { return m_rfStackFw; }
	IdtFw & idtFw() { return m_idtFw; }
	OsFw & osFw() { return m_osFw; }
	CfgInfo & rdCfgInfo() { return m_rdCfgInfo; }
	CfgInfo & wrCfgInfo() { return m_wrCfgInfo; }
	LanParam & lanInfo() { return m_lanInfo; }
	LanParam & wlanInfo() { return m_wlanInfo; }
	BluetoothConnection & bluetoothConnection() { return m_bluetoothConnection; }
	IOCap & ioCap() { return m_ioCap; }
	PeriphDev & periphDev() { return m_periphDev; }
	DeviceInfo & deviceInfo() { return m_deviceInfo; }

private:
	RfcFw m_rfcFw;				///< Mode=0x00
	AccFw m_accFw;				///< Mode=0x01
	UsbFw m_usbFw;				///< Mode=0x02
	RfDecoder m_rfDecoder;		///< Mode=0x03
	FwFunction m_fwFunction;	///< Mode=0x04
	BootFw m_bootFw;			///< Mode=0x05
	KeyboardFw m_keyboardFw;	///< Mode=0x06
	CprioFw m_cprioFw;			///< Mode=0x07
	CprTrDriver m_cprTrDriver;	///< Mode=0x08
	WifiFw m_wifiFw;			///< Mode=0x09:
	Bluetooth m_bluetooth;		///< Mode=0x0A:
	BarcodeFw m_barcodeFw;		///< Mode=0x0B
	HwInfo m_hwInfo;			///< Mode=0x10
	SamInfo m_samInfo;			///< Mode=0x11
	CpuInfo m_cpuInfo;			///< Mode=0x12
	RfStackFw m_rfStackFw;		///< Mode=0x15
	IdtFw m_idtFw;				///< Mode=0x16
	OsFw m_osFw;				///< Mode=0x20
	CfgInfo m_rdCfgInfo;		///< Mode=0x40
	CfgInfo m_wrCfgInfo;		///< Mode=0x41
	LanParam m_lanInfo;         ///< Information with LAN capabilities requested with command [0x66] and Modes=0x50 ... 0x53
	LanParam m_wlanInfo;        ///< Information with WLAN capabilities requested with command [0x66] and Modes=0x54 ... 0x57
	BluetoothConnection m_bluetoothConnection; ///< Mode 0x58
	IOCap m_ioCap;				///< Mode=0x60
	PeriphDev m_periphDev;      ///< Mode=0x61
	DeviceInfo m_deviceInfo;	///< Mode=0x80 and Mode=0x81

}; // end of class ReaderInfo

}; // end of namespace FEDM

#endif // READER_INFO_H

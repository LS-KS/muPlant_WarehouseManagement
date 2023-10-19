/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_CONST_H
#define FEDM_CONST_H

#include <string>

#include "FedmBase.h"
#include "FedmRdrType.h"
#include "FedmErrCode.h"
#include "FedmRdrStatus.h"



namespace FEDM {


enum class RequestMode {
	/// Request Mode Uni-Directional:<br>
	/// TCP communication is performed via separate sockets for application and reader requests.<br>
	/// All other communication ports can be used for application requests only.<br>
	/// The protocol frame Advanced is used.
	UniDirectional = 1,

	/// Request Mode Bi-Directional:<br>
	/// Application and reader requests are using the same TCP socket / communication port.<br>
	/// The protocol frame Enhanced is used.
	BiDirectional = 2
};



enum class EventType {
	Invalid = -1, ///< In case of an empty event queue
	Unknown = 0,  ///< In case of a unknown event type send by a reader (SDK / Reader-FW mismatch)

	IdentificationEvent = 1, ///< Event command 0x2A (universal for RequestMode::UniDirectional and RequestMode::BiDirectional)
//	HeartbeatEvent = 2,      ///< Event command 0x2D (universal for RequestMode::UniDirectional and RequestMode::BiDirectional)
	DiagEvent = 2,           ///< Event command 0x2D (universal for RequestMode::UniDirectional and RequestMode::BiDirectional)
	TagEvent = 3,            ///< Event command 0x2B (universal for RequestMode::UniDirectional and RequestMode::BiDirectional)

	BrmEvent = 4,            ///< Event command 0x22, response command 0x32 can be enabled/disabled (only for RequestMode::UniDirectional)

	/// Event command 0x2C (universal for RequestMode::UniDirectional and RequestMode::BiDirectional) or<br>
	/// Event command 0x74, no response (only for RequestMode::UniDirectional)
	InputEvent = 20,  

//	DiagStatusEvent = 21,    ///< Event command 0x6E mode 0x01: DiagStatus, no response (only for RequestMode::UniDirectional)

	/// Event command 0x2E (universal for RequestMode::UniDirectional and RequestMode::BiDirectional) or<br>
	/// Event command 0x77, no response (only for RequestMode::UniDirectional)
	PeopleCounterEvent = 30,
};


/*
enum class AuthentType : uint8_t {
	Aes128  = 0x00,
	Aes192  = 0x01,
	Aes256  = 0x02,
	Plain   = 0xFF
};
*/


enum class UhfRegion : uint8_t {
	/// constant for an invalid region value
	Invalid = 0x00,

	/// constant for EU Region Europe
	EuEurope = 0x06,
	/// constant for EU Region Asia or Oceania
	EuAsiaOceania = 0x16,
	/// constant for EU Region Russia
	EuRussia = 0x26,
	/// constant for EU Region Africa
	EuAfrica = 0x36,
	/// constant for EU Region India
	EuIndia = 0x46,
	/// constant for EU Region Morocco
	EuMorocco = 0x56,
	/// constant for all other EU Regions with manual frequency settings (see System Manual of Reader)
	EuManual = 0xFE,
		
	/// constant for FCC Region USA
	FccUsa = 0x04,
	/// constant for FCC Region China
	FccChina = 0x14,
	/// constant for FCC Region Australia or New Zealand
	FccAustraliaNewZealand = 0x24,
	/// constant for FCC Region Brazil
	FccBrazil = 0x34,
	/// constant for FCC Region Israel
	FccIsreal = 0x44,
	/// constant for FCC Region Japan
	FccJapan = 0x54,
	/// constant for FCC Region Malaysia
	FccMalaysia = 0x64,
	/// constant for FCC Region Korea
	FccKorea = 0x74,
	/// constant for all other FCC Regions with manual frequency settings (see System Manual of Reader)
	FccManual = 0xFF
};



enum class TagDriverForSelect {
	None = 0x00,
	Iso14443_4 = 0x01,
	Iso14443_3_MifareClassic = 0x02,
	NfcCardType2 = 0x03,
	Iso14443_3_MifarePlusSl1 = 0x04,
	Iso14443_4_MifarePlusSl1 = 0x05,
	Iso14443_3_MifarePlusSl2 = 0x06,
	Iso14443_4_MifarePlusSl2 = 0x07,
	Iso14443_4_MifarePlusSl3 = 0x08,
	Iso14443_4_MifareDesfire = 0x09,
	Iso14443_3_MydProximity = 0x0A,
	Iso14443_3_MydMove = 0x0B
};



/// @brief Policy of reading reader info after connect
///
/// IMPORTANT NOTE: In case ReaderInfoPolicy=Off the SDK libraries don't have any information about the connected reader, particularly the reader type.
/// However there are SDK functions they need some informations from the connected reader to work well.
/// In that case a call to readReaderInfo() of the ReaderModule will set these informations.
enum class ReaderInfoPolicy {
	BL = -1, ///< Use to reconnect to boot loader. For internal purpose.
	Off = 0, ///< Do not read reader info after connect.
	Min = 1, ///< Fast read of a minimum set of reader info (mode 0x00, 0x80) after connect.
	All = 2  ///< Read the entire reader info after connect.
};



/// @brief CONSTANT class for fundamental transponder types
///
/// We consider a barcode as a transponder type
class FEDM_CLASS_DEF TransponderType
{
public:
	static const int Icode1 = 0x00;
	static const int Iso15693 = 0x03;
	static const int Iso14443A = 0x04;
	static const int Iso14443B = 0x05;
	static const int Jewel = 0x08;
	static const int Iso18000_3M3 = 0x09;
	static const int StmSR176 = 0x0A;
	static const int StmSRIxx = 0x0B;
	static const int Felica = 0x0D;
	static const int Innovatron = 0x10;
	static const int AskCTx = 0x11;
	static const int Em4222 = 0x83;
	static const int EpcClass1Gen2 = 0x84;
	static const int Barcode = 0xC2;

	/// @param[in] The transponder type
	/// @return A string representation of the transponder type
	static std::string toString(int transponderType)
	{
		switch (transponderType) {
		case Icode1: return "NXP I-Code1";
		case Iso15693: return "ISO 15693";
		case Iso14443A: return "ISO 14443-A";
		case Iso14443B: return "ISO 14443-B";
		case Jewel: return "Jewel";
		case Iso18000_3M3: return "ISO 18000-3M3";
		case StmSR176: return "STMicroelectronics SR176";
		case StmSRIxx: return "STMicroelectronics SRIxx";
		case Felica: return "Sony FeliCa";
		case Innovatron: return "Innovatron (ISO 14443B')";
		case AskCTx: return "ASK CTx";
		case Em4222: return "EM4222";
		case EpcClass1Gen2: return "EPC Class 1 Gen 2";
		case Barcode: return "Barcode";
		// ...
		default: return "Unknown transponder type (" + std::to_string(transponderType) + ")";
		}
	}

}; // end of class TransponderType



/// @brief CONSTANT class for manufacturer codes and names
///
/// This informations refer to ISO14443 and ISO15693 transponder
class FEDM_CLASS_DEF Iec7816_MfrCode
{
public:
	static const int Motorola = 0x01;
	static const int Stm = 0x02;
	static const int Hitachi = 0x03;
	static const int Nxp = 0x04;
	static const int Infineon = 0x05;
	static const int Cylink = 0x06;
	static const int Ti = 0x07;
	static const int Fujitsu = 0x08;
	static const int Matushita = 0x09;
	static const int Nec = 0x0A;
	static const int Oki = 0x0B;
	static const int Toshiba = 0x0C;
	static const int Mitsubishi = 0x0D;
	static const int Samsung = 0x0E;
	static const int Hyundai = 0x0F;
	static const int Lg = 0x10;
	static const int Emosyn_em = 0x11;
	static const int Inside = 0x12;
	static const int Orga = 0x13;
	static const int Sharp = 0x14;
	static const int Microchip = 0x15;
	static const int Em = 0x16;
	static const int Zmd = 0x18;
	static const int Xicor = 0x19;
	static const int Sony = 0x1A;
	static const int Malaysia = 0x1B;
	static const int Emosyn = 0x1C;
	static const int Shanghai_fudan = 0x1D;
	static const int Magellan = 0x1E;
	static const int Melexis = 0x1F;
	static const int Renesas_tec = 0x20;
	static const int Tagsys = 0x21;
	static const int Transcore = 0x22;
	static const int Shanghai_belling = 0x23;
	static const int Masktech = 0x24;
	static const int Innovision = 0x25;
	static const int Hitachi_ulsi = 0x26;
	static const int Cypak = 0x27;
	static const int Ricoh = 0x28;
	static const int Ask = 0x29;
	static const int Unicore = 0x2A;
	static const int Impinj = 0x2C;
	static const int Rightplug = 0x2D;
	static const int Broadcom = 0x2E;
	static const int Mstar = 0x2F;
	static const int Eedar = 0x30;
	static const int Rfidsec = 0x31;
	static const int Schweizer = 0x32;
	static const int Amic = 0x33;
	static const int Mirkron_jsc = 0x34;
	static const int Fraunhofer_ipms = 0x35;
	static const int Kovio = 0x37;
	static const int Hmt = 0x38;
	static const int Silicon_craft = 0x39;
	static const int Adv_film_dev = 0x3A;
	static const int Nitecrest = 0x3B;
	static const int Verayo = 0x3C;
	static const int Hid = 0x3D;
	static const int Prod_eng = 0x3E;
	static const int Austria_micro = 0x3F;
	static const int Gemalto = 0x40;
	static const int Renesas_electr = 0x41;
	static const int Three_alogigcs = 0x42;
	static const int Top_troniq = 0x43;
	static const int Gentag = 0x44;
	static const int Invengo = 0x45;
	static const int Guangzhou_sysur = 0x46;
	static const int Ceitec = 0x47;
	static const int Shanghai_quanray = 0x48;
	static const int Media_tek = 0x49;
	static const int Angstrem_pjsc = 0x4A;
	static const int Celisic = 0x4B;
	static const int Legic = 0x4C;
	static const int Balluff = 0x4D;
	static const int Oberthur = 0x4E;
	static const int Silterra = 0x4F;
	static const int Delta = 0x50;
	static const int Giesecke_devrien = 0x51;
	static const int Shenzhen = 0x52;
	static const int Shanghai_feiju = 0x53;
	static const int Intel = 0x54;
	static const int Microsensys = 0x55;
	static const int Sonix = 0x56;
	static const int Qualcomm = 0x57;
	static const int Realtek = 0x58;
	static const int Freevision = 0x59;
	static const int Giantec = 0x5A;
	static const int Jsc_angstrem = 0x5B;
	static const int Starchip = 0x5C;
	static const int Spirtech = 0x5D;
	static const int Gantner = 0x5E;
	static const int Nordic = 0x5F;
	static const int Verisiti = 0x60;
	static const int Wearlinks = 0x61;
	static const int Userstar = 0x62;
	static const int Pragmatic = 0x63;
	static const int Lsi_tec = 0x64;
	static const int Tendyron = 0x65;
	static const int Muto_smart = 0x66;
	static const int On = 0x67;
	static const int Tuebitak_bilge = 0x68;
	static const int Huada = 0x69;
	static const int Seveney = 0x6A;
	static const int Issm = 0x6B;
	static const int Wisesec = 0x6C;
	static const int Holtek  = 0x7E;

	/// @param[in] The manufacturer code of a transponder
	/// @return A text description of the manufacturer
	static std::string toString(int mfrCode)
	{
		switch (mfrCode) {
		case Motorola: return "Motorola";
		case Stm: return "STMicroelectronics SA";
		case Hitachi: return "Hitachi, Ltd."; 
		case Nxp: return "NXP Semiconductors";
		case Infineon: return "Infineon Technologies AG";
		case Cylink: return "Cylink";
		case Ti: return "Texas Instruments";
		case Fujitsu: return "Fujitsu Limited";
		case Matushita: return "Matsushita Electronics Corporation";
		case Nec: return "NEC";
		case Oki: return "OKI Electric Industry Co. Ltd.";
		case Toshiba: return "Toshiba Corporation";
		case Mitsubishi: return "Mitsubishi Electric Corporation";
		case Samsung: return "Samsung Electronics Co. Ltd";
		case Hyundai: return "Hyundai Electronics Industries Co. Ltd.";
		case Lg: return "LG-Semiconductors Co. Ltd";
		case Emosyn_em: return "Emosyn-EM Microelectronics";
		case Inside: return "INSIDE Technology";
		case Orga: return "ORGA Kartensysteme GmbH";
		case Sharp: return "SHARP Corporation";
		case Microchip: return "Microchip Technology Inc";
		case Em: return "EM Microelectronic-Marin SA";
		case Zmd: return "ZMD AG";
		case Xicor: return "XICOR, Inc.";
		case Sony: return "Sony Corporation";
		case Malaysia: return "Malaysia Microelectronic Solutions Sdn. Bhd";
		case Emosyn: return "Emosyn";
		case Shanghai_fudan: return "Shanghai Fudan Microelectronics Co. Ltd.";
		case Magellan: return "Magellan Technology Pty Limited";
		case Melexis: return "Melexis NV BO";
		case Renesas_tec: return "Renesas Technology Corp.";
		case Tagsys: return "TAGSYS";
		case Transcore: return "Transcore";
		case Shanghai_belling: return "Shanghai belling corp., ltd.";
		case Masktech: return "Masktech Germany GmbH";
		case Innovision: return "Innovision Research and Technology Plc";
		case Hitachi_ulsi: return "Hitachi ULSI Systems Co. Ltd.";
		case Cypak: return "Cypak AB";
		case Ricoh: return "Ricoh";
		case Ask: return "ASK";
		case Unicore: return "Unicore Microsystems, LLC";
		case Impinj: return "Impinj, Inc.";
		case Rightplug: return "RightPlug Alliance";
		case Broadcom: return "Broadcom Corporation";
		case Mstar: return "MStar Semiconductor, Inc";
		case Eedar: return "eeDar Technology Inc.";
		case Rfidsec: return "RFIDsec";
		case Schweizer: return "Schweizer Electronic AG";
		case Mirkron_jsc: return "Mikron JSC";
		case Fraunhofer_ipms: return "Fraunhofer Institute of Photonic Microsystems";
		case Amic: return "AMIC Technology Corp";
		case Kovio: return "Kovio";
		case Hmt: return "HMT Microelectronic";
		case Silicon_craft: return "Silicon Craft Technology";
		case Adv_film_dev: return "Advanced Film Device Inc.";
		case Nitecrest: return "Nitecrest Ltd";
		case Verayo: return "Verayo Inc.";
		case Hid: return "HID Global";
		case Prod_eng: return "Productivity Engineering Gmbh";
		case Austria_micro: return "Austriamicrosystems AG";
		case Gemalto: return "Gemalto SA";
		case Renesas_electr: return "Renesas Electronics Corporation";
		case Three_alogigcs: return "3Alogics Inc";
		case Top_troniq: return "Top TroniQ Asia Limited";
		case Gentag: return "Gentag Inc";
		case Invengo: return "Invengo Information Technology Co. Ltd.";
		case Guangzhou_sysur: return "Guangzhou Sysur Microelectronics Inc";
		case Ceitec: return "CEITEC S.A.";
		case Shanghai_quanray: return "Shanghai Quanray Electronics Co. Ltd.";
		case Media_tek: return "MediaTek Inc";
		case Angstrem_pjsc: return "Angstrem PJSC";
		case Celisic: return "Celisic Semiconductor Limited";
		case Legic: return "LEGIC Identsystems AG";
		case Balluff: return "Balluff GmbH";
		case Oberthur: return "Oberthur Technologies";
		case Silterra: return "Silterra Malaysia Sdn. Bhd.";
		case Delta: return "DELTA Danish Electronics, Light & Acoustics";
		case Giesecke_devrien: return "Giesecke & Devrient GmbH";
		case Shenzhen: return "Shenzhen China Vision Microelectronics Co. Ltd.";
		case Shanghai_feiju: return "Shanghai Feiju Microelectronics Co. Ltd.";
		case Intel: return "Intel Corporation";
		case Microsensys: return "Microsensys GmbH";
		case Sonix: return "Sonix Technology Co. Ltd.";
		case Qualcomm: return "Qualcomm Technologies Inc";
		case Realtek: return "Realtek Semiconductor Corp";
		case Freevision: return "Freevision Technologies Co. Ltd.";
		case Giantec: return "Giantec Semiconductor Inc";
		case Jsc_angstrem: return "JSC Angstrem-T";
		case Starchip: return "STARCHIP";
		case Spirtech: return "SPIRTECH";
		case Gantner: return "GANTNER Electronic GmbH";
		case Nordic: return "Nordic Semiconductor";
		case Verisiti: return "Verisiti Inc";
		case Wearlinks: return "Wearlinks Technology Inc";
		case Userstar: return "Userstar Information Systems Co. Ltd.";
		case Pragmatic: return "Pragmatic Printing Ltd.";
		case Lsi_tec: return "Associacao do Laboratorio de Sistemas Integraveis Tecnologico - LSI-TEC";
		case Tendyron: return "Tendyron Corporation";
		case Muto_smart: return "MUTO Smart Co. Ltd.";
		case On: return "ON Semiconductor";
		case Tuebitak_bilge: return "TUEBITAK BILGE";
		case Huada: return "Huada Semiconductor Co. Ltd.";
		case Seveney: return "SEVENEY";
		case Issm: return "ISSM";
		case Wisesec: return "Wisesec Ltd.";
		case Holtek: return "Holtek";

		default: return "Unknown Manufacturer Code (" + std::to_string(mfrCode) + ")";
		}
	}

}; // end of class Iec7816_MfrCode



/// @brief CONSTANT class for EPC C1G2 Mask Designer ID's and Names
class FEDM_CLASS_DEF EpcC1G2_MaskDesignerId
{
public:
	static const int Impinj = 0x01;
	static const int Ti = 0x02;
	static const int Alien = 0x03;
	static const int Intelleflex = 0x04;
	static const int Microchip = 0x05;
	static const int Nxp = 0x06;
	static const int Stm = 0x07;
	static const int Ep_micro = 0x08;
	static const int Motorola = 0x09;
	static const int Em = 0x0B;
	static const int Renesas = 0x0C;
	static const int Mstar = 0x0D;
	static const int Tyco = 0x0E;
	static const int Quanray = 0x0F;
	static const int Fujitsu = 0x10;
	static const int Tego = 0x17;

	/// @param[in] The EPC Class1 Gen2 mask designer ID
	/// @return A text description of the mask designer ID
	static std::string toString(int mdId)
	{
		switch (mdId) {
		case Impinj: return "Impinj";
		case Ti: return "Texas Instruments";
		case Alien: return "Alien Technology";
		case Intelleflex: return "Intelleflex";
		case Microchip: return "Microchip Technology Inc";
		case Nxp: return "NXP Semiconductors";
		case Stm: return "STMicroelectronics SA";
		case Ep_micro: return "EP Microelectronics";
		case Motorola: return "Motorola";
		case Em: return "EM Microelectronic-Marin SA";
		case Renesas: return "Renesas Technology";
		case Mstar:	return "MStar";
		case Tyco: return "Tyco International";
		case Quanray: return "Quanray Electronics";
		case Fujitsu: return "Fujitsu Limited";
		case Tego: return "Tego";

		default: return "";
		}
	}

	// defined in FEDM_TabItem.h

}; // end of class EpcC1G2_MaskDesignerId

}; // end of namespace FEDM

#endif // FEDM_CONST_H

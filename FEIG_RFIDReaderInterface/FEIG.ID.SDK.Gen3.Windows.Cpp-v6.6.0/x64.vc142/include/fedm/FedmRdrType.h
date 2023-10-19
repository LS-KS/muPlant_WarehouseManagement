/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_READER_TYPE_H
#define FEDM_READER_TYPE_H

#include <string>

#include "FedmBase.h"



namespace FEDM {

/// @brief CONSTANT class for FEIG reader types
class FEDM_CLASS_DEF ReaderType {
public:
//	static const uint32_t ANT_HFMUX_M8 = 10;
//	static const uint32_t ANT_HFDAT = 11;
	static const uint32_t ANT_HFMUX_M5 = 16;
//	static const uint32_t ANT_UHFMUX_A = 12;
//	static const uint32_t ANT_GPC = 13;
//	static const uint32_t ANT_LED = 14;
//	static const uint32_t ANT_UPC = 15;
	// ...
//	static const uint32_t M02 = 31;
	static const uint32_t M02_M8 = 33;
	static const uint32_t LR2500_B = 43;
	static const uint32_t LR2500_A = 44;
	static const uint32_t LR1002 = 45;
//	static const uint32_t OEM1 = 46; // no FW-Upd
	// ...
	static const uint32_t LR5400_Family = 47;
	static const uint32_t LR5400 = (LR5400_Family | 0x0100);
	// ...
	static const uint32_t MU02 = 50;
	static const uint32_t MU95 = 51; // no FW-Upd
	static const uint32_t MU92 = 52; // no FW-Upd
    static const uint32_t MRU102 = 54;
	static const uint32_t PRH101 = 60;
	static const uint32_t PRH101_U = 61;
	static const uint32_t PRHD102 = 62;
	static const uint32_t PRH102 = 63;
	static const uint32_t PRH200 = 64;
	static const uint32_t MR101 = 76;
	static const uint32_t MR102 = 77;
	static const uint32_t MR101_U = 78;
//	static const uint32_t CPRM02 = 80;
//	static const uint32_t CPR02 = 81;
	static const uint32_t CPR40_XX_U = 82;
	static const uint32_t CPR40_XX = 83;
	static const uint32_t CPR50_XX = 84;
	static const uint32_t CPR44_XX = 85; // no FW-Upd
	static const uint32_t CPR30_XX = 86; // = CPR30+
	static const uint32_t CPR46_XX = 89;
	static const uint32_t LRU1002 = 91;
	static const uint32_t LRU3000 = 94;
	// ...
	static const uint32_t LRU500i_Family = 95;
	static const uint32_t LRU500i_BD   = (LRU500i_Family | 0x0100);
	static const uint32_t LRU500i_PoE  = (LRU500i_Family | 0x0200);
	static const uint32_t MAXU500i     = (LRU500i_Family | 0x0300);
	// ...
	static const uint32_t MAX50_XX = 100;
	static const uint32_t MAXU1002 = 101;
	static const uint32_t CPR47_XX = 111; // no FW-Upd
	static const uint32_t CPR60_XX = 113;
	static const uint32_t CPR74 = 114;
	static const uint32_t CPR71 = 115; // no FW-Upd
	static const uint32_t CPR30pro = 116;
	static const uint32_t CPR70 = 117;
//	static const uint32_t MLC_COM = 120;
//	static const uint32_t MLC_EMPS = 121;
	static const uint32_t ANTU_500_270_GA = 130; // no FW-Upd
	static const uint32_t ANTU_500_270_DM = 131; // no FW-Upd
	// ...
	static const uint32_t HyWEAR_Compact_Family = 140;
	static const uint32_t HyWEAR_Compact    = (HyWEAR_Compact_Family | 0x0000);
	static const uint32_t HyWEAR_Compact_xT = (HyWEAR_Compact_Family | 0x0100);
	static const uint32_t HyWEAR_Compact_sR = (HyWEAR_Compact_Family | 0x0200);
	// ...
	static const uint32_t ECCO_Plus = 141; // no FW-Upd
	// ...
	static const uint32_t ECCO_Smart_Family = 142;
	static const uint32_t ECCO_Smart_HF_BLE    = (ECCO_Smart_Family | 0x0100);
	static const uint32_t ECCO_Smart_2D_HF_BLE = (ECCO_Smart_Family | 0x0200);


	/// @param[in] The reader type ID
	/// @return The reader type as string
	static std::string toString(uint32_t readerType)
	{
		switch (readerType) {
//		case ANT_DAT: return "ID ISC.DAT";
//		case ANT_UMUX: return "ID ISC.UMUX";
//		case ANT_GPC: return "ID ISC.ANT.GPC";
//		case ANT_LED: return "ID ISC.ANT.LED";
//		case ANT_UPC: return "ID ISC.ANT.UPC";
		case ANT_HFMUX_M5: return "ID ISC.ANT.HFMUX-M5";
//		case M02: return "ID ISC.M02";
		case M02_M8: return "ID ISC.M02.M8";
		case LR2500_B: return "ID ISC.LR2500-B";
		case LR2500_A: return "ID ISC.LR2500-A";
		case LR1002: return "ID ISC.LR1002";
//		case OEM1: return "ID OEM1";
		// ...
//		case LR5400_A: return "ID LR5400-A";
		case LR5400: return "ID LR5400"; // renamed
		// ...
		case MU02: return "ID ISC.MU02";
		case MU95: return "ID ISC.MU95";
		case MU92: return "ID ISC.MU92";
		case MRU102: return "ID ISC.MRU102";
		case PRH101: return "ID ISC.PRH101";
		case PRH101_U: return "ID ISC.PRH101-U";
		case PRHD102: return "ID ISC.PRHD102";
		case PRH102: return "ID ISC.PRH102";
		case PRH200: return "ID ISC.PRH200";
		case MR101: return "ID ISC.MR101";
		case MR102: return "ID ISC.MR102";
		case MR101_U: return "ID ISC.MR101-U";
//		case CPRM02: return "ID CPR.M02";
//		case CPR02: return "ID CPR.02";
		case CPR40_XX_U: return "ID CPR40.xx-U";
		case CPR40_XX: return "ID CPR40.xx";
		case CPR50_XX: return "ID CPR50.xx";
		case CPR44_XX: return "ID CPR44.xx";
		case CPR30_XX: return "ID CPR30.xx";
		case CPR46_XX: return "ID CPR46.xx";
		case LRU1002: return "ID ISC.LRU1002";
		case LRU3000: return "ID ISC.LRU3000";
		// ...
		case LRU500i_BD: return "ID LRU500i-BD";
		case LRU500i_PoE: return "ID LRU500i-PoE";
		case MAXU500i: return "ID MAX.U500i";
		// ...
		case MAX50_XX: return "ID MAX50.xx";
		case MAXU1002: return "ID MAX.U1002";
		case CPR47_XX: return "ID CPR47.xx";
		case CPR60_XX: return "ID CPR60.xx";
		case CPR74: return "ID CPR74";
		case CPR71: return "ID CPR71";
		case CPR30pro: return "ID CPR30pro";
		case CPR70: return "ID CPR70";
//		case MLC_COM: return "ID MLC.COM";
//		case MLC_EMPS: return "ID MLC.EMPS";
		case ANTU_500_270_GA: return "ID ISC.ANT.U500/270-GA";
		case ANTU_500_270_DM: return "ID ISC.ANT.U500/270-DM";
		// ...
		case HyWEAR_Compact:    return "ID HyWEAR compact";
		case HyWEAR_Compact_xT: return "ID HyWEAR compact xT";
		case HyWEAR_Compact_sR: return "ID HyWEAR compact sR";
		// ...
		case ECCO_Plus: return "ID ECCO+";
		case ECCO_Smart_HF_BLE: return "ID ECCO Smart HF-BLE";
		case ECCO_Smart_2D_HF_BLE: return "ID ECCO Smart 2D-HF-BLE";

		default: return "";
		}
	}

	/// @param[in] The reader type name
	/// @return The reader type ID
	static uint32_t fromString(const std::string & readerType)
	{
/*		if (readerType == "ID ISC.DAT") { return ANT_DAT; }
		else if (readerType == "ID ISC.UMUX") { return ANT_UMUX; }
		else if (readerType == "ID ISC.ANT.GPC") { return ANT_GPC; }
		else if (readerType == "ID ISC.ANT.LED") { return ANT_LED; }
		else if (readerType == "ID ISC.ANT.UPC") { return ANT_UPC; }
		else*/
		if      (readerType == "ID ISC.ANT.HFMUX-M5") { return ANT_HFMUX_M5; }
//		else if (readerType == "ID ISC.M02") { return M02; }
		else if (readerType == "ID ISC.M02.M8") { return M02_M8; }
		else if (readerType == "ID ISC.LR2500-B") { return LR2500_B; }
		else if (readerType == "ID ISC.LR2500-A") { return LR2500_A; }
		else if (readerType == "ID ISC.LR1002") { return LR1002; }
//		else if (readerType == "ID OEM1") { return OEM1; }
		else if ((readerType == "ID LR5400-A") || (readerType == "ID LR5400")) { return LR5400; }
		else if (readerType == "ID ISC.MU02") { return MU02; }
		else if (readerType == "ID ISC.MU95") { return MU95; }
		else if (readerType == "ID ISC.MU92") { return MU92; }
		else if (readerType == "ID ISC.MRU102") { return MRU102; }
		else if (readerType == "ID ISC.PRH101") { return PRH101; }
		else if (readerType == "ID ISC.PRH101-U") { return PRH101_U; }
		else if (readerType == "ID ISC.PRHD102") { return PRHD102; }
		else if (readerType == "ID ISC.PRH102") { return PRH102; }
		else if (readerType == "ID ISC.PRH200") { return PRH200; }
		else if (readerType == "ID ISC.MR101") { return MR101; }
		else if (readerType == "ID ISC.MR102") { return MR102; }
		else if (readerType == "ID ISC.MR101-U") { return MR101_U; }
//		else if (readerType == "ID CPR.M02") { return CPRM02; }
//		else if (readerType == "ID CPR.02") { return CPR02; }
		else if (readerType == "ID CPR40.xx-U") { return CPR40_XX_U; }
		else if (readerType == "ID CPR40.xx") { return CPR40_XX; }
		else if (readerType == "ID CPR50.xx") { return CPR50_XX; }
		else if (readerType == "ID CPR44.xx") { return CPR44_XX; }
		else if (readerType == "ID CPR30.xx") { return CPR30_XX; }
		else if (readerType == "ID CPR46.xx") { return CPR46_XX; }
		else if (readerType == "ID ISC.LRU1002") { return LRU1002; }
		else if (readerType == "ID ISC.LRU3000") { return LRU3000; }
		// ...
		else if (readerType == "ID LRU500i-BD") { return LRU500i_BD; }
		else if (readerType == "ID LRU500i-PoE") { return LRU500i_PoE; }
		else if (readerType == "ID MAX.U500i") { return MAXU500i; }
		// ...
		else if (readerType == "ID MAX50.xx") { return MAX50_XX; }
		else if (readerType == "ID MAX.U1002") { return MAXU1002; }
		else if (readerType == "ID CPR47.xx") { return CPR47_XX; }
		else if (readerType == "ID CPR60.xx") { return CPR60_XX; }
		else if (readerType == "ID CPR74") { return CPR74; }
		else if (readerType == "ID CPR71") { return CPR71; }
		else if (readerType == "ID CPR30pro") { return CPR30pro; }
		else if (readerType == "ID CPR70") { return CPR70; }
//		else if (readerType == "ID MLC.COM") { return MLC_COM; }
//		else if (readerType == "ID MLC.EMPS") { return MLC_EMPS; }
		else if (readerType == "ID ISC.ANT.U500/270-GA") { return ANTU_500_270_GA; }
		else if (readerType == "ID ISC.ANT.U500/270-DM") { return ANTU_500_270_DM; }
		// ...
		else if (readerType == "ID HyWEAR compact") { return HyWEAR_Compact; }
		else if (readerType == "ID HyWEAR compact xT") { return HyWEAR_Compact_xT; }
		else if (readerType == "ID HyWEAR compact sR") { return HyWEAR_Compact_sR; }
		// ...
		else if (readerType == "ID ECCO+") { return ECCO_Plus; }
		else if (readerType == "ID ECCO Smart HF-BLE") { return ECCO_Smart_HF_BLE; }
		else if (readerType == "ID ECCO Smart 2D-HF-BLE") { return ECCO_Smart_2D_HF_BLE; }
		else { return 0; }
	}

	/// @return True, if reader is part of IDENTIFICATION HF family (ISO 14443, ISO 15693 and ISO 18000-3M3)
	static bool isHfReader(uint32_t readerType)
	{
		switch (readerType)
		{
//			case M02: return true;
			case M02_M8: return true;
			case LR2500_B: return true;
			case LR2500_A: return true;
			case LR1002: return true;
//			case OEM1: return true;
			case PRH101: return true;
			case PRH101_U: return true;
			case PRHD102: return true;
			case PRH102: return true;
			case MR101: return true;
			case MR102: return true;
			case MR101_U: return true;
//			case CPRM02: return true;
//			case CPR02: return true;
			case CPR40_XX_U: return true;
			case CPR40_XX: return true;
			case CPR50_XX: return true;
			case CPR44_XX: return true;
			case CPR30_XX: return true;
			case MAX50_XX: return true;
			case CPR46_XX: return true;
			case CPR47_XX: return true;
			case CPR60_XX: return true;
			case CPR74: return true;
			case CPR71: return true;
//			case MLC_COM: return true;
//			case MLC_EMPS: return true;
			case ECCO_Plus: return true;
			default: return false;
		}

	
	}
	/// @returns True, if reader is part of IDENTIFICATION UHF family (EPC Class1 Gen2)
	static bool isUhfReader(uint32_t readerType)
	{ 
		switch (readerType)
		{
			case MU02:
			case MU95:
			case MU92:
			case PRHD102:
			case MRU102:
			case LRU1002:
			case LRU3000:
			case LRU500i_BD:
			case LRU500i_PoE:
			case MAXU500i:
			case MAXU1002:
			case ANTU_500_270_GA:
			case ANTU_500_270_DM:
			case HyWEAR_Compact: 
				return true;

			default:
				return false;
		}

	}

	/// @return True, if reader can handle ISO 14443 transponder
	static bool isISO14443Reader(uint32_t readerType)
	{
		switch (readerType)
		{
//			case CPRM02: return true;
//			case CPR02: return true;
			case CPR40_XX_U: return true;
			case CPR40_XX: return true;
			case CPR50_XX: return true;
			case CPR44_XX: return true;
			case CPR30_XX: return true;
			case CPR46_XX: return true;
			case MAX50_XX: return true;
			case CPR47_XX: return true;
			case CPR60_XX: return true;
			case CPR74: return true;
			case CPR71: return true;
//			case MLC_COM: return true;
//			case MLC_EMPS: return true;
			default: return false;
		}
	}

	/// @return True, if reader can handle ISO 15693 transponder
	static bool isISO15693Reader(uint32_t readerType)
	{
		switch (readerType)
		{
//			case M02: return true;
			case M02_M8: return true;
			case LR2500_B: return true;
			case LR2500_A: return true;
			case LR1002: return true;
//			case OEM1: return true;
			case PRH101: return true;
			case PRH101_U: return true;
			case PRHD102: return true;
			case PRH200: return true;
			case MR101: return true;
			case MR102: return true;
			case MR101_U: return true;
//			case CPRM02: return true;
//			case CPR02: return true;
			case CPR50_XX: return true;
			case CPR30_XX: return true;
			case MAX50_XX: return true;
			case CPR60_XX: return true;
			case CPR74: return true;
			case ECCO_Plus: return true;
			default: return false;
		}
	}

	/// @return True, if reader can handle ISO 18000-3M3 transponder
	static bool isISO180003m3Reader(uint32_t readerType)
	{
		switch (readerType)
		{
//			case M02: return true;
			case LR1002: return true;
			case MR102: return true;
			case CPR74: return true;
			default: return false;
		}
	}

	/// @return True, if reader can handle EPC Class1 Gen2 transponder
	static bool isEPCC1G2Reader(uint32_t readerType)
	{
		switch (readerType)
		{
			case MU02:
			case MU95:
			case MU92:
			case PRHD102:
			case MRU102:
			case LRU1002:
			case LRU3000:
			case LRU500i_BD:
			case LRU500i_PoE:
			case MAXU500i:
			case MAXU1002:
			case ANTU_500_270_GA:
			case ANTU_500_270_DM:
			case HyWEAR_Compact: 
				return true;

			default:
				return false;
		}
	}

	static bool isCprReader(uint32_t readerType)
	{
		switch (readerType) {
//			case CPRM02:
//			case CPR02:
			case CPR40_XX_U:
			case CPR40_XX:
			case CPR50_XX:
			case CPR44_XX:
			case CPR30_XX:
			case CPR46_XX:
			case CPR47_XX:
			case CPR60_XX:
			case CPR74:
			case CPR71:
				return true;

			default:
				return false;
		}
	}

}; // end of class ReaderType

}; // end of namespace FEDM

#endif // FEDM_READER_TYPE_H

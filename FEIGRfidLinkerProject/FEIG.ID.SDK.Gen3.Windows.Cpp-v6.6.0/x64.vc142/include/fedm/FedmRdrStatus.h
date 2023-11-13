/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_READER_STATUS_H
#define FEDM_READER_STATUS_H


#ifdef FEISPDLL
#define FEDM_CLASS_DEF
#else
#include <FedmBase.h>
#endif


#include <string>
#include <sstream>



namespace FEDM {

/// @brief CONSTANT class for status values of reader commands
class FEDM_CLASS_DEF ReaderStatus
{
public:
	static const int Ok = 0x00;
	static const int NoTag = 0x01;
	static const int TagDataFalse = 0x02;
	static const int TagWriteError = 0x03;
	static const int TagAddrError = 0x04;
	static const int TagWrongTag = 0x05;
	static const int TagReadError = 0x06;
	static const int TagNoSelect = 0x07;
	static const int TagAuthentError = 0x08;
	static const int TagRangeError = 0x09;
	static const int TagChange = 0x0A;
	static const int TagCollision = 0x0B;
	static const int TagWeakCollision = 0x0C;
	static const int GeneralError = 0x0E;
	static const int Busy = 0x0F;
	static const int EepromError = 0x10;
	static const int EepromRangeError = 0x11;
	static const int EepromLoginRequest = 0x13;
	static const int EepromLoginError = 0x14;
	static const int EepromReadProtection = 0x15;
	static const int EepromWriteProtection = 0x16;
	static const int FirmwareActivationRequired = 0x17;
	static const int FirmwareWrong = 0x18;
	static const int CryptoProcessingErr = 0x19;
	static const int ExtDeviceErr = 0x20;
	static const int SamNo = 0x31;
	static const int SamNotActive = 0x32;
	static const int SamIsActive = 0x33;
	static const int SamProtNoSupport = 0x34;
	static const int SamComError = 0x35;
	static const int SamTimeout = 0x36;
	static const int DataFileNotOpen = 0x40;
	static const int DataFileIsOpen = 0x41;
	static const int DataFileLengthError = 0x42;
	static const int UnknownCmd = 0x80;
	static const int ProtLengthErr = 0x81;
	static const int CmdNotAvailable = 0x82;
	static const int RfCommErr = 0x83;
	static const int RfWarning = 0x84;
	static const int SynchError = 0x85;
	static const int UnsupportedCmdOption = 0x86;
	static const int DataTableOverrun = 0x90;
	static const int DataTableNoData = 0x92;
	static const int DataTableOverflow = 0x93;
	static const int MoreData = 0x94;
	static const int IsoError = 0x95;
	static const int IsoError14443 = 0x96;
	static const int CryptoProcessErr = 0x97;
	static const int HwWarning = 0xF1;
	static const int InitWarning = 0xF2;
	static const int InternalProcessCancelled = 0xF8;


	/// @param[in] The reader status returned by library communication functions
	/// @return A text description of the reader status
	static std::string toString(int readerStatus)
	{
		switch (readerStatus) {
			case Ok: return "Ok";
			case NoTag: return "No transponder in reader field";
			case TagDataFalse: return "False transponder data";
			case TagWriteError: return "Transponder write error";
			case TagAddrError: return "Transponder address error";
			case TagWrongTag: return "Wrong transponder type";
			case TagReadError: return "Transponder read error";
			case TagNoSelect: return "Select error";
			case TagAuthentError: return "Authent error";
			case TagRangeError: return "Invalid address";
			case TagChange: return "Transponder changed";
			case TagCollision: return "RF collision";
			case TagWeakCollision: return "RF weak collision";
			case GeneralError: return "General error";
			case Busy: return "Reader is busy";
			case EepromError: return "EEPROM Error";
			case EepromRangeError: return "Parameter range error";
			case EepromLoginRequest: return "Login request";
			case EepromLoginError: return "Login error";
			case EepromReadProtection: return "Read protection";
			case EepromWriteProtection: return "Write protection";
			case FirmwareActivationRequired: return "Firmware activation required";
			case FirmwareWrong: return "Wrong firmware";
			case CryptoProcessingErr: return "Crypto processing error";
			case ExtDeviceErr: return "External device communication error";
			case SamNo: return "No SAM detected";
			case SamNotActive: return "Requested SAM is not activated";
			case SamIsActive: return "SAM is already activated";
			case SamProtNoSupport: return "Requested protocol is not supported by the SAM";
			case SamComError: return "SAM communication error";
			case SamTimeout: return "SAM Timeout";
			case DataFileNotOpen: return "Data file is not opened";
			case DataFileIsOpen: return "Data file is open";
			case DataFileLengthError: return "Data file length error";
			case UnknownCmd: return "Unknown Command";
			case ProtLengthErr: return "Protocol length error";
			case CmdNotAvailable: return "Command not available";
			case RfCommErr: return "RF communication error";
			case RfWarning: return "RF warning";
			case SynchError: return "Synchronization error";
			case UnsupportedCmdOption: return "Unsupported command option";
			case DataTableOverrun: return "Data table overrun";
			case DataTableNoData: return "No valid data";
			case DataTableOverflow: return "Data table overflow";
			case MoreData: return "More data";
			case IsoError: return "Iso error";
			case IsoError14443: return "Iso14443 error";
			case CryptoProcessErr: return "Crypto processing error in RF communication";
			case HwWarning: return "Hardware warning";
			case InitWarning: return "Initialization warning";
			case InternalProcessCancelled: return "Internal process cancelled";
			// ...

			default:
				{
					std::ostringstream oss;
					oss.fill('0');
					oss.width(2);
					oss << "Reader status 0x" << std::hex << readerStatus;
					return oss.str();
				}
		}
	}

}; // end of class ReaderStatus

}; // end of namespace FEDM

#endif // FEDM_READER_STATUS_H

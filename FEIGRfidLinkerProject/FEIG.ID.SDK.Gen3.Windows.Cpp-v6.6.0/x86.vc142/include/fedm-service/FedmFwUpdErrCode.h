/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FWUPD_ERROR_CODE_H
#define FEDM_FWUPD_ERROR_CODE_H

#include "FedmServiceBase.h"
#include <string>

namespace FEDM {

/// @brief CONSTANT class for FEDM-SERVICE library error codes
class FEDM_SERVICE_CLASS_DEF FwUpdateErrorCode
{
public:
	static const int Ok = 0;

	// ...
	static const int CodeBase = -400;
	static const int CodeLast = -499;
	static const int NoReaderModule = CodeBase;
	static const int ThreadAlreadyRunning = CodeBase - 1;
	static const int CreateThread = CodeBase - 2;
	static const int NeverShouldHappenError = CodeBase - 3;
	static const int NullPointer = CodeBase - 4;
	static const int PayloadLength = CodeBase - 5;
	static const int PayloadBuilder = CodeBase - 6;
	static const int PayloadParser = CodeBase - 7;
	static const int CommandParameter = CodeBase - 8;

	// ...
	static const int EmptyUpdateFile = CodeBase - 10;
	static const int WrongReaderType = CodeBase - 11;
	static const int FirmwareRequirement = CodeBase - 12;
	static const int UnexpectedReaderInfo = CodeBase - 13;
	static const int MultipleBanksUnsupported = CodeBase - 14;
	static const int UnsupportedControllerType = CodeBase - 15;
	static const int UnsupportedReaderType = CodeBase - 16;
	static const int NoVerifyResultAvailable = CodeBase - 17;
	static const int GenericControllerTypes = CodeBase - 18;
	static const int UpdateToolVersionMismatch = CodeBase - 19;

	// ...
	static const int MissingControllerImage = CodeBase - 30;
	static const int UnexpectedReaderType = CodeBase - 31;
	static const int DecodeControllerImage = CodeBase - 32;
	static const int ReconnectTimeout = CodeBase - 33;
	static const int Upload = CodeBase - 34;
	static const int CorruptImageData = CodeBase - 35;
	static const int UnexpectedReaderRevision = CodeBase - 36;

	// ...
	static const int UpdateEepromError = CodeBase - 40;
	static const int UpdateFwActivationRequired = CodeBase - 41;
	static const int GetInputTimeout = CodeBase - 42;

	// ...
	static const int NoPeriphDeviceInfo = CodeBase - 50;
	static const int BootLoaderAlreadyRunning = CodeBase - 51;


	/// @brief Get the text of an error code
	/// @param[in] errorCode The error code returned by library functions
	/// @return A text description of the error code
	///
	/// To get a list of all error texts, see 'FedmFwUpdErrCode.h'
	static std::string toString(int errorCode)
	{
		switch (errorCode) {
		case Ok: return "Ok";
		case NoReaderModule: return "No reader module given";
		case ThreadAlreadyRunning: return "An operation thread is already running";
		case CreateThread: return "Cannot create thread";
		case NeverShouldHappenError: return "Never should happen error";
		case NullPointer: return "Invalid null pointer";
		case PayloadLength: return "Payload length error";
		case PayloadBuilder: return "Payload build error";
		case PayloadParser: return "Payload parser error";
		case CommandParameter: return "Command parameter error";

		case EmptyUpdateFile: return "There are no update images for controllers in the XML file";
		case WrongReaderType: return "The firmware file is not specified for the detected reader type";
		case FirmwareRequirement: return "The reader firmware does not match to the update requirements";
		case UnexpectedReaderInfo: return "Reader info does not match to the update requirements (missing parts)";
		case MultipleBanksUnsupported: return "Multiple firmware banks not supported";
		case UnsupportedControllerType: return "Unsupported controller type in XML file";
		case UnsupportedReaderType: return "Unsupported reader type";
		case NoVerifyResultAvailable: return "No verify result available";
		case GenericControllerTypes: return "Standard and generic controller types mixed";
		case UpdateToolVersionMismatch: return "Version of the update tool is too old";

		case MissingControllerImage: return "Missing controller update image";
		case UnexpectedReaderType: return "Unexpected reader type";
		case DecodeControllerImage: return "Decoding controller image error";
		case ReconnectTimeout: return "Reconnect timeout";
		case Upload: return "Error while upload of firmware file";
		case CorruptImageData: return "Corrupt image data";
		case UnexpectedReaderRevision: return "Unexpected reader revision";

		case UpdateEepromError: return "Update EEPROM error";
		case UpdateFwActivationRequired: return "Firmware activation required";
		case GetInputTimeout: return "Timout while waiting for key pressed";

		case NoPeriphDeviceInfo: return "No peripheral device information available";
		case BootLoaderAlreadyRunning: return "Boot loader already running";

		default: return "Error code (" + std::to_string(errorCode) + ")";
		}
	}

}; // end of class FwUpdErrorCode

}; // end of namespace FEDM

#endif // FEDM_FWUPD_ERROR_CODE_H

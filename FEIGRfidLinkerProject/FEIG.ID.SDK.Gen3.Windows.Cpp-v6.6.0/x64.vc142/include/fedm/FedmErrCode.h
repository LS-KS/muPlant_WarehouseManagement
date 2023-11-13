/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_ERROR_CODE_H
#define FEDM_ERROR_CODE_H

#include "FedmBase.h"
#include <string>

namespace FEDM {

/// @brief CONSTANT class for FEDM library error codes
class FEDM_CLASS_DEF ErrorCode
{
public:
	static const int Ok = 0;
	// ...
	static const int CodeBase = -100;
	static const int CodeLast = -299;
	static const int UnknownReaderType = CodeBase - 1;
	static const int PayloadLength = CodeBase - 2;
	static const int PayloadBuilder = CodeBase - 3;
	static const int PayloadParser = CodeBase - 4;
	static const int UnsupportedAddressMode = CodeBase - 5;
	static const int ConnectReaderBusy = CodeBase - 6;
	static const int ConfigSizeMismatch = CodeBase - 10;
	static const int ConfigRead = CodeBase - 11;
	static const int ConfigWrite = CodeBase - 12;
	static const int ConfigParameter = CodeBase - 13;
	static const int ConfigMemNotAvailable = CodeBase - 14;
	static const int CommandParameter = CodeBase - 20;
	static const int CommandParameterWrongReader = CodeBase - 21;
	static const int FunctionNotSupported =  CodeBase - 22;
	static const int OutOfMemory = CodeBase - 23;
	static const int NoData = CodeBase - 24;
	static const int ResponseProcessing = CodeBase - 25;
	static const int TagCommandFailed = CodeBase - 26;

	// ...
	static const int WrpCodeBase = -180;
	static const int WrpInsufficientBufferLength = WrpCodeBase - 1;
	static const int WrpInvalidReaderHandle = WrpCodeBase - 2;
	static const int WrpCannotCreateTagHandler = WrpCodeBase - 3;
	static const int WrpCorruptedData = WrpCodeBase - 4;
	static const int WrpInvalidHexStr = WrpCodeBase - 5;
	static const int WrpInvalidPointer = WrpCodeBase - 6;
	static const int WrpIndexOutOfRange = WrpCodeBase - 7;
	static const int WrpJavaNullParameter = WrpCodeBase - 8;
	static const int WrpJavaInternalError = WrpCodeBase - 9;

	/// @param[in] The error code returned by library functions
	/// @return A text description of the error code
	///
	/// To get a list of all error texts, see 'FedmErrCode.h'
	static std::string toString(int errorCode)
	{
		switch (errorCode) {
		case Ok: return "Ok";
		case UnknownReaderType: return "Unknown reader type";
		case PayloadLength: return "Payload length error";
		case PayloadBuilder: return "Payload build error";
		case PayloadParser: return "Payload parser error";
		case UnsupportedAddressMode: return "Unsupported address mode";
		case ConnectReaderBusy: return "Connect error (reader busy)";
		case ConfigSizeMismatch: return "Configuration size mismatch";
		case ConfigRead: return "Configuration read error";
		case ConfigWrite: return "Configuration write error";
		case ConfigParameter: return "Configuration parameter error";
		case ConfigMemNotAvailable: return "Configuration memory (RAM) not available";
		case CommandParameter: return "Command parameter error";
		case CommandParameterWrongReader: return "Wrong reader type for command parameter";
		case FunctionNotSupported: return "Function not supported";
		case OutOfMemory: return "Memory allocation failed";
		case NoData: return "No data available";
		case ResponseProcessing: return "Reader response processing failed";
		case TagCommandFailed: return "The command executed on a tag failed";
		// ...
		case WrpInsufficientBufferLength: return "Wrapper: Length of the data buffer is insufficient";
		case WrpInvalidReaderHandle: return "Wrapper: Invalid reader handle";
		case WrpCannotCreateTagHandler: return "Wrapper: FEDM library returned null pointer as tag handler";
		case WrpCorruptedData: return "Wrapper: Data of 'FEDM_ReaderInfo/FEDM_ReaderDiag' is corrupt";
		case WrpInvalidHexStr: return "Wrapper: Invalid HEX string";
		case WrpInvalidPointer: return "Wrapper: An invalid pointer has been passed to the FEDM wrapper";
		case WrpIndexOutOfRange: return "Wrapper: Access to an array failed because the index is out of range";
		case WrpJavaNullParameter: return "Wrapper: Invalid value 'null' for parameter of FEDM Java Wrapper";
		case WrpJavaInternalError: return "Wrapper: Internal Java Wrapper Error";

		default: return "Error code (" + std::to_string(errorCode) + ")";
		}
	}

}; // end of class ErrorCode

}; // end of namespace FEDM

#endif // FEDM_ERROR_CODE_H

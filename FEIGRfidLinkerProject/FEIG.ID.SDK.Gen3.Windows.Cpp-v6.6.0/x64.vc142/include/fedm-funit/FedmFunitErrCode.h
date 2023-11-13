/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_ERROR_CODE_H
#define FEDM_FUNIT_ERROR_CODE_H

#include "FedmFunitBase.h"
#include <string>

namespace FEDM {
namespace FunctionUnit {

/// @brief CONSTANT class for FEDM function unit library error codes
class FEDM_FUNIT_CLASS_DEF FunitErrorCode
{
public:
	static const int Ok = 0;
	// ...
	static const int CodeBase = -300;
	static const int CodeLast = -399;
	static const int CommandParameter = CodeBase - 1;
	static const int PayloadLength = CodeBase - 2;
	static const int PayloadBuilder = CodeBase - 3;
	static const int PayloadParser = CodeBase - 4;
	// ...
	static const int InvalidParentUnitType = CodeBase - 10;
	static const int InvalidParentUnitChannel = CodeBase - 11;
	static const int ParentUnitChannelOccupied = CodeBase - 12;
	static const int InvalidUnitAddress = CodeBase - 13;
	static const int UnexpectedUnitType = CodeBase - 14;
	static const int UnsupportedByFirmware = CodeBase - 15;
	// ...
	static const int AutoAddressTooLittle = CodeBase - 20;

	/// @param[in] The error code returned by library functions
	/// @return A text description of the error code
	///
	/// To get a list of all error texts, see 'FedmFunitErrCode.h'
	static std::string toString(int errorCode)
	{
		switch (errorCode) {
		case Ok: return "Ok";
		case CommandParameter: return "Command parameter error";
		case PayloadLength: return "Payload length error";
		case PayloadBuilder: return "Payload build error";
		case PayloadParser: return "Payload parser error";
		case InvalidParentUnitType: return "Invalid parent function unit type";
		case InvalidParentUnitChannel: return "Invalid parent function unit channel, i.e. out of range";
		case ParentUnitChannelOccupied: return "Parent function unit channel already occupied";
		case InvalidUnitAddress: return "Unit address contains out of range channel";
		case UnexpectedUnitType: return "Unexpected function unit type";
		case UnsupportedByFirmware: return "Function is not supported by FW";
		case AutoAddressTooLittle: return "Too little antennas detected while auto addressing";

		default: return "Error code (" + std::to_string(errorCode) + ")";
		}
	}

}; // end of class FunitErrorCode

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_ERROR_CODE_H

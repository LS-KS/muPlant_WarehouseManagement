/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_STM_H
#define FEDM_TH_ISO15693_STM_H

#include "TagHandler/Th15693.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders from manufacturer STMicroelectronics SA
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_STM : public ThIso15693
{
	friend class Internal::ReaderBase;

public:

	enum class PasswordNumber : uint8_t {
		Password_CFG = 0x00,
		Password1 = 0x01,
		Password2 = 0x02,
		Password3 = 0x03
	};

	virtual std::string transponderName() const override;

	virtual ~ThIso15693_STM();

protected:
	ThIso15693_STM(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

	int kill(const std::vector<uint8_t> & killCode);
	int writeKill(const std::vector<uint8_t> & killCode);
	int writePassword(PasswordNumber passwordNumber, const std::vector<uint8_t> & password);
	int lockKill(uint8_t protectStatus=0x00);
	int presentPassword(PasswordNumber passwordNumber, const std::vector<uint8_t> & password);

}; // end of class ThIso15693_STM

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_STM_H

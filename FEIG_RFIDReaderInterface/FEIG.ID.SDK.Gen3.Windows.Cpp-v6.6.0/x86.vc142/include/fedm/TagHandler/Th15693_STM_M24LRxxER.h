/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_STM_M24LRXXER_H
#define FEDM_TH_ISO15693_STM_M24LRXXER_H

#include "TagHandler/Th15693_STM.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type M24LRxxE-R series from manufacturer STMicroelectronics SA
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of M24LRxxE-R. Thus, you must refer to the Technical Datasheet of the M24LRxxE-R to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>STMicroelectronics Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_STM_M24LRxxER : public ThIso15693_STM_M24LR64R
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @param[out] data Configuration byte
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Command [0xB1][0xA0] Read Configuration Byte
	int readCfg(uint8_t & data);

	/// @param[in] data Configuration byte
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Command [0xB1][0xA1] Write Configuration Byte
	int writeEHCfg(uint8_t data);

	/// @param[in] enabled Set or the EH_ENABLE bit (enabled = true) or reset (enabled = false)
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Command [0xB1][0xA2] Set/Reset Control Register
	int setRstEHEn(bool enabled);

	/// @param[out] data Control register
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Command [0xB1][0xA3] Read Control Register
	int checkEHEn(uint8_t & data);

	/// @param[in] enableRfWipMode If true enable RF WIP mode else enable RF BUSY mode
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Command [0xB1][0xA4] Set/Reset RF WIP/BUSY bit in Control Register
	int writeDOCfg(bool enableRfWipMode);

	/// @return String with Manufacturer Name
	///
	/// The Manufacturer Name is specified with Manufcturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	virtual std::string manufacturerName(void) const override;


	virtual ~ThIso15693_STM_M24LRxxER();

protected:
	ThIso15693_STM_M24LRxxER(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_STM_M24LRxxER

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_STM_M24LRXXER_H

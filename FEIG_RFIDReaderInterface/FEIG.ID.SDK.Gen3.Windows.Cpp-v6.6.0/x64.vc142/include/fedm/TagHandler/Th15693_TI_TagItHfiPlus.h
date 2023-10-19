/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_TI_TAGITHFIPLUS_H
#define FEDM_TH_ISO15693_TI_TAGITHFIPLUS_H

#include "TagHandler/Th15693_TI.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type Tag-it HFI Plus from manufacturer Texas Instruments
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of Tag-it HF-I Plus. Thus, you must refer to the Technical Datasheet of the Tag-it HF-I Plus to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>TI Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_TI_TagItHfiPlus : public ThIso15693_TI
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA2] Write 2 Blocks
	/// @param[in] dbAddr First block number to be written
	/// @param[in] dbSize Number of bytes of one data block
	/// @param[in] evenDB Block data to be written to the transponder
	/// @param[in] oddDB Block data to be written to the transponder
	/// @return #{DOC_LIB_RETURN_VALUE}
	int write2Blocks(size_t dbAddr, size_t dbSize, const std::vector<uint8_t> & evenDb, const std::vector<uint8_t> & oddDb);

	/// @brief Command [0xB1][0xA3] Lock 2 Blocks
	/// @param[in] dbAddr First block number to be locked 
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lock2Blocks(size_t dbAddr);

	/// @brief The Manufacturer Name is specified with Manufcturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_TI_TagItHfiPlus();

protected:
	ThIso15693_TI_TagItHfiPlus(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_TI_TagitHFIPlus

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_TI_TAGITHFIPLUS_H

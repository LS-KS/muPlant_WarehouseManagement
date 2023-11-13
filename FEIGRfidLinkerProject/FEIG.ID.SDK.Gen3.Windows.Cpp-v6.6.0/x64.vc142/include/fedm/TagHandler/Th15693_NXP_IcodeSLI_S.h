/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_NXP_ICODESLI_S_H
#define FEDM_TH_ISO15693_NXP_ICODESLI_S_H

#include "TagHandler/Th15693_NXP_IcodeSLI_L.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type I-CODE SLI-S from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of I-CODE SLI-S. Thus, you must refer to the Technical Datasheet of the I-CODE SLI-S to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>NXP Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_NXP_IcodeSLI_S : public ThIso15693_NXP_IcodeSLI_L
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA8]
	/// @param[out] epc   
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readEpc(std::vector<uint8_t> & epc);

	/// @brief Command [0xB1][0xB6]
	/// @param[in] pageNumber Number of the page   
	/// @param[in] protectionStatus Protection status   
	/// @return #{DOC_LIB_RETURN_VALUE}
	int protectPage(size_t pageNumber, ProtectionStatus protectionStatus);

	/// @brief Command [0xB1][0xB7]
	/// @param[in] pageNumber Number of the page   
	/// @return #{DOC_LIB_RETURN_VALUE}
	int lockPageProtectionCondition(size_t pageNumber);

	/// @brief Command [0xB1][0xB8]
	/// @param[in] firstDataBlock First number of block
	/// @param[inout] noOfDataBlocks Number of blocks   
	/// @param[out] securityStatus Block proctection status
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getMultipleBlockProtectionStatus(size_t firstDataBlock, size_t noOfDataBlocks, std::vector<uint8_t> & securityStatus);

	/// @brief Command [0xB1][0xB9]
	/// @return #{DOC_LIB_RETURN_VALUE}
	int destroySLI_S();

	/// @brief Command [0xB1][0xBB]
	/// @param[in] passwordParameter  
	/// @return #{DOC_LIB_RETURN_VALUE}
	int passwordProtection(bool enable);

	/// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_NXP_IcodeSLI_S();

protected:
	ThIso15693_NXP_IcodeSLI_S(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_NXP_ICODESLI_S

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_NXP_ICODESLI_S_H

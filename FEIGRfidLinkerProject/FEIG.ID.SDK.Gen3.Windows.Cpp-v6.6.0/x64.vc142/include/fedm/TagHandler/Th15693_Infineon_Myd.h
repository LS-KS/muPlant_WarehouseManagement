/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_INFINEON_MYD_H
#define FEDM_TH_ISO15693_INFINEON_MYD_H

#include "TagHandler/Th15693_Infineon.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type my-d from manufacturer Infineon Technologies AG
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of Infineon Technologies AG. Thus, you must refer to the Technical Datasheets to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>Infineon Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_Infineon_Myd : public ThIso15693_Infineon
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

    /// @brief Command [0xB1][0xAB] : This command enables or disables the Advanced Quiet Mode
	/// @param[in] aqm  If advanced quiet mode should be enabled
	/// @return #{DOC_LIB_RETURN_VALUE}
    int setAdvancedQuietBit(bool enabled);

    /// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
    /// @return String with Manufacturer Name
    virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_Infineon_Myd();

protected:
	ThIso15693_Infineon_Myd(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_Infineon_myd

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_INFINEON_MYD_H

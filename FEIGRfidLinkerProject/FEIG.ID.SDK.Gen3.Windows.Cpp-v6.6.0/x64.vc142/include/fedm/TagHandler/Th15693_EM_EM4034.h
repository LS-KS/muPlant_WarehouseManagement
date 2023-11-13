/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_EM_EM4034_H
#define FEDM_TH_ISO15693_EM_EM4034_H

#include "TagHandler/Th15693_EM.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type 4034 from manufacturer EM Microelectronic-Marin SA
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to the specific commands of the EM4034. Thus, you must refer to the Technical Datasheet of the EM4034 to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>EM Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_EM_EM4034 : public ThIso15693_EM
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

    /// @brief Command [0xB1][0xA0] Toggle EAS
    ///
    /// This command is realized with the Reader command [0xB1] ISO Custom and Proprietary Commands.<br>
    /// Refer to the Application Note <i>EM Custom and Proprietary Commands.pdf</i>, where all parameters are described in detail.<br>
    /// This command is only applicable in non-addressed mode. See hm().createNonAddressedTagHandler()<br>
    /// on how to create a TagHandler instance for non-addressed communication.<br>
    ///
    /// @param[in] password Hex-coded password with even number of chars
	/// @return #{DOC_LIB_RETURN_VALUE}
    ///
    /// @note Hex-coded string means, that a hex value of 0xAB39F1D9 must be set as "AB39F1D9".
    int toggleEas(const std::vector<uint8_t> & password);

    /// @brief Command [0xB1][0xE4] Login
    ///
    /// This command is realized with the Reader command [0xB1] ISO Custom and Proprietary Commands.<br>
    /// Refer to the Application Note <i>EM Custom and Proprietary Commands.pdf</i>, where all parameters are described in detail.<br>
    ///
    /// @param[in] password Hex-coded password with even number of chars
	/// @return #{DOC_LIB_RETURN_VALUE}
    ///
    /// @note Hex-coded string means, that a hex value of 0xAB39F1D9 must be set as "AB39F1D9".
    int login(const std::vector<uint8_t> & password);

    /// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
    /// @return String with Manufacturer Name
    virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_EM_EM4034();

protected:
    ThIso15693_EM_EM4034(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_EM_4034

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_EM_EM4034_H

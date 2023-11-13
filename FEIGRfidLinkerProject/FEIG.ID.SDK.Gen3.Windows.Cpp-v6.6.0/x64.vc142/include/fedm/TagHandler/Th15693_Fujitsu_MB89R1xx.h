/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_EM_FUJISTU_MB89R1XX_H
#define FEDM_TH_ISO15693_EM_FUJISTU_MB89R1XX_H

#include "TagHandler/Th15693_Fujitsu.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders of type MB89R1xx series from manufacturer Fujitsu Limited
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to the specific commands of the MB89R1xx series. Thus, you must refer to the Technical Datasheet of the MB89R1xx to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>Fujitsu Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_Fujitsu_MB89R1xx : public ThIso15693_Fujitsu
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @brief Command [0xB1][0xA0] EAS
	/// @return #{DOC_LIB_RETURN_VALUE}
	int eas();

	/// @brief Command [0xB1][0xA1] write eas
	/// @param[in] setEasBit If true set the eas bit else clear the eas bit
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeEas(bool setEasBit);

	/// @brief Command [0xB1][0xA2] Refresh
	/// @return #{DOC_LIB_RETURN_VALUE}
	int refresh();

	/// @brief Command [0xB1][0xA6] Kill
	/// @return #{DOC_LIB_RETURN_VALUE}
	int kill();

	/// @brief The Manufacturer Name is specified with Manufacturer Code, which is located in byte 1 of the Identifier Data (IDD), resp. UID, resp. SNR of Transponder
	/// @return String with Manufacturer Name
	virtual std::string manufacturerName(void) const override;

	virtual ~ThIso15693_Fujitsu_MB89R1xx();

protected:
	ThIso15693_Fujitsu_MB89R1xx(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_Fujitsu_MB89R1xx

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_EM_FUJISTU_MB89R1XX_H

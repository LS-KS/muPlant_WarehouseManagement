/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_NXP_MIFAREPLUS_H
#define FEDM_TH_ISO14443_3_NXP_MIFAREPLUS_H

#include "TagHandler/Th14443_3_NXP_MifareClassic.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant Transponders of type MIFARE Plus from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_NXP_MifarePlus : public ThIso14443_3_NXP_MifareClassic
{
	friend class Internal::ReaderBase;

public:
	static const int ErrorSourceTransponder = 1;
	static const int ErrorSourceAlgorithm = 3;

	virtual std::string transponderName() const override;

	/// @brief Get the source of last error
	/// @return The last error source. Call lastIsoError() to obtain the error code
	int lastErrorSource(void) const;

	virtual ~ThIso14443_3_NXP_MifarePlus();

protected:
	ThIso14443_3_NXP_MifarePlus(Internal::ReaderBase * readerBase, const TagItem & tagItem = TagItem(), const CardInfo14443 & cardInfo = CardInfo14443());

	void setLastErrorSource(int source);
	virtual void resetErrors(void) override;
	virtual int  transceiveAndCheckIsoError(void) override;

	int m_lastErrorSource;

}; // end of class ThIso14443_3_NXP_MifarePlus

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_NXP_MIFAREPLUS_H

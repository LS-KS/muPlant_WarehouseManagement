/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_4_NXP_MIFAREPLUS_H
#define FEDM_TH_ISO14443_4_NXP_MIFAREPLUS_H

#include "TagHandler/Th14443_4.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-4 compliant Transponders of type MIFARE Plus from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// This class implements the communication with [0xC2] Reader commands.<br>
/// Detailed description about the command interface can be found in:
/// - Product Datasheet for MIFARE Plus from NXP Semiconductors
/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_4_NXP_MifarePlus : public ThIso14443_4
{
	friend class Internal::ReaderBase;

public:
	static const int ErrorSourceTransponder = 1;
	static const int ErrorSourceAlgorithm = 3;

	virtual std::string transponderName() const override;

	/// @brief Get the source of last error
	/// @return The last error source. Call lastIsoError() to obtain the error code
	int lastErrorSource(void) const;

	/// @brief MIFARE Plus Command [0x70], realized with Reader command [0xC2][0x70] First Authentication
	///
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is an Authentication command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int firstAuthent(size_t aesKeyBlockNumber, const std::vector<uint8_t> & pcdCap2, uint8_t readerKeyIndex);

	/// @brief MIFARE Plus Command [0x76], realized with Reader command [0xC2][0x76] Following Authentication
	///
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This method is an Authentication command.<br>
	/// Detailed description about the command and the parameters can be found in:<br>
	/// - Product Datasheet for MIFARE Plus from NXP Semiconductors<br>
	/// - System Manual <i>SoftCrypto Functions</i> from FEIG ELECTRONIC
	int followingAuthent(size_t aesKeyBlockNumber, uint8_t readerKeyIndex);

    virtual ~ThIso14443_4_NXP_MifarePlus();

protected:
	ThIso14443_4_NXP_MifarePlus(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

	void setLastErrorSource(int source);
	virtual void resetErrors(void) override;
	virtual int  transceiveAndCheckIsoError(void) override;

	int m_lastErrorSource;

}; // end of class ThIso14443_4_NXP_MifarePlus

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_4_NXP_MIFAREPLUS_H

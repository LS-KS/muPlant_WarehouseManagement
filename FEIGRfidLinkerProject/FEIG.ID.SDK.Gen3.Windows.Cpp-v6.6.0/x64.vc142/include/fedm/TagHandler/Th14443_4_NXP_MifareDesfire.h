/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_H
#define FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_H

#include "TagHandler/Th14443_4.h"
#include "TagHandler/Th14443_4_NXP_MifareDesfire_SoftCrypto.h"
#include "TagHandler/Th14443_4_NXP_MifareDesfire_FlexSoftCrypto.h"
#include "TagHandler/Th14443_4_NXP_MifareDesfire_SamCrypto.h"


namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-4 compliant Transponders of type MIFARE DESFire from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// The support for MIFARE DESFire is limited to some IDENTIFICATION Readers and realized with three different implementations:<br>
/// - Soft-Crypto, using [0xC1] High integrated commands for DESFire Communication
/// - Flexible Soft-Crypto, using [0xC3] Flexible commands for DESFire Communication
/// - SAM-Crypto, using [0xC3] Flexible commands for DESFire Communication with SAM
/// 
/// For more information about the pros and cons of the different commands get in contact with FEIG ELECTRONIC.<br>
/// Additionally, you have to order the Product Datasheet from NXP Semiconductors to become familiar with the features of the DESFire.<br>
/// <br>
/// The method interface of this class is very wide and complex. Due to the three different DESFire APIs in the Reader, this class maps this APIs with three different nested classes, 
/// each implementing the specialized method interface:
/// - [ISoftCrypto](@ref ISoftCrypto) for Soft-Crypto commands
/// - [IFlexSoftCrypto](@ref IFlexSoftCrypto) for Flexible Soft-Crypto commands
/// - [ISamCrypto](@ref ISamCrypto) for SAM-Crypto commands
///
/// @note Programmers should also be familiar with the ISO 14443 and ISO/IEC 7816 standards
class FEDM_CLASS_DEF ThIso14443_4_NXP_MifareDesfire : public ThIso14443_4
{
	friend class ThIso14443_4_NXP_MifareDesfire_ImplBase;
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	virtual ~ThIso14443_4_NXP_MifareDesfire();

	static const uint8_t CommSettingsPlainCommunication = 0x00;
	static const uint8_t CommSettingsPlainCommunicationSecuredByMAC = 0x01;
	static const uint8_t CommSettingsFullyEncipheredCommunication = 0x03;

	static const int ErrorSourceTransponder = 1;
	static const int ErrorSourceSam = 2;
	static const int ErrorSourceAlgorithm = 3;

	ThIso14443_4_NXP_MifareDesfire_SoftCrypto & softCrypto();
	ThIso14443_4_NXP_MifareDesfire_FlexSoftCrypto & flexSoftCrypto();
	ThIso14443_4_NXP_MifareDesfire_SamCrypto & samCrypto();

	int lastErrorSource();
	int lastErrorCode();

protected:
	ThIso14443_4_NXP_MifareDesfire(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

	ThIso14443_4_NXP_MifareDesfire_ImplC1 *m_implC1;
	ThIso14443_4_NXP_MifareDesfire_ImplC3 *m_implC3;

	/// Nested interface implementing the Soft-Crypto commands
	ThIso14443_4_NXP_MifareDesfire_SoftCrypto m_softCrypto;

	/// Nested interface implementing the flexible soft-crypto commands
	ThIso14443_4_NXP_MifareDesfire_FlexSoftCrypto m_flexSoftCrypto;

	/// Nested interface implementing the SAM-crypto commands
	ThIso14443_4_NXP_MifareDesfire_SamCrypto m_samCrypto;

	int m_lastErrorSource;
}; // end of class ThIso14443_4_NXP_MifareDesfire

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_4_NXP_MIFAREDESFIRE_H

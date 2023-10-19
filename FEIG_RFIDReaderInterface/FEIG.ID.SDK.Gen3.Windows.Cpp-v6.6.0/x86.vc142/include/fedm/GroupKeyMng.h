/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_KEY_MNG_H
#define FEDM_GROUP_KEY_MNG_H

#include "FedmBasic.h"
#include "FedmHide.h"

namespace FEDM {

/// @brief GROUP class for readers key management
class FEDM_CLASS_DEF KeyManagement
{
	friend class ReaderModule;

public:
	/// @brief Write keys for ISO14443 MIFARE transponder authentication (command [0xA2]), i.e. MIFARE classic, MIFARE mini, MIFARE 1K or 4K.
	/// @param mifareKey the key as as 'KeyMifare' object
	/// @param addr Address where the key is stored in the reader. Applicable values are 0..7.</param>
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// A key which is used by the Reader for authentication to an NXP MIFARE Transponder will be stored persistent in the Reader.
	/// Only if the key of the Reader and of the Transponder correspond, the data exchange between Reader and Transponder can be successful executed.
	int writeTagAuthentKeyMifare(const KeyMifareClassic & mifareClassicKey, uint8_t addr);


	/// @brief Write keys for ISO14443 DES or AES transponder authentication (command [0xA3]), i.e. MIFARE DESFire, MIFARE Plus and MIFARE Ultralight C.
	/// @param mifareDesfireKey The key as a 'KeyMifareDesfire' object
	/// @param index Address where the key is stored in the reader. Applicable values are 0..3
	/// @param persistent if false, the key is stored temporarily in the RAM. After the supply power was interrupted, the keys has to be loaded once again into the RAM.
	///                     This option is recommended, if the Reader is used on a public place and anybody can take the Reader away easily.
	///                   if true, the key is stored persistent in the Reader's internal non-volatile memory (EEPROM).
	///                     This option can be used, if the Reader is installed at a secured place.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// An AES or DES key which is used by the Reader for authentication to an NXP MIFARE Transponder will be stored in the Reader.
	/// Only if the key of the Reader and of the Transponder correspond, the data exchange between Reader and Transponder can be
	/// successful executed.
	int writeTagAuthentKeyIso14443(const KeyMifareDesfire & mifareDesfireKey, uint8_t index, bool persistent);


	/// @brief Write keys for AES transponder authentication (command [0xA3]), useable for NXP UCODE/ICODE DNA.
	/// @param key the UCODE DNA key
	/// @param index Address where the key is stored in the reader. Applicable values are 0 and 1
	/// @param persistent if false the key is stored temporarily in the RAM, otherwise the key is stored persistent in the Reader's internal non-volatile memory
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// An AES key which is used by the Reader for authentication to an NXP UCODE/ICODE DNA Transponder will be stored in the Reader.
	/// Only if the key of the Reader and of the Transponder correspond, the data exchange between Reader and Transponder can be successful executed.
	int writeTagAuthentKeyUcodeDna(const KeyAes & key, uint8_t index, bool persistent);


	/// @brief Write keys for EPC transponder authentication (command [0xAD]).
	/// @param epcKey The epc key as 'KeyEpc' object.
	/// @param persistent if false the key is stored temporarily in the RAM, otherwise the key is stored persistent in the Reader's internal non-volatile memory
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// A key which is used by the Reader for authentication to a EPC Transponder will be stored in the Reader
	/// Only if the key of the Reader and of the Transponder correspond, the data exchange between Reader and Transponder can be successful executed.
	int writeTagAuthentKeyEpc(const KeyEpc & epcKey, bool persistent);


	/// @brief Setup username and password via command [0xA4]
	/// @param[in] username Max. 16 ASCII signs allowed
	/// @param[in] password Max. 16 ASCII signs allowed
	/// @param[in] param Settings parameter
	/// @return #{DOC_LIB_RETURN_VALUE}
	int setupReaderPassword(const std::string & username, const std::string & password, const SetPasswordParam & param);


protected:
	KeyManagement();
	~KeyManagement();

	Internal::ReaderBase *m_rdrBase; // set by a friend

};

} // end of namespace FEDM

#endif // FEDM_GROUP_KEY_MNG_H

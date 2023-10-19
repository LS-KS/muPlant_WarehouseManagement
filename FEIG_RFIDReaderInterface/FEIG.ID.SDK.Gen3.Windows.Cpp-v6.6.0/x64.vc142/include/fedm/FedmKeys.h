/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_KEYS_H_
#define FEDM_KEYS_H_

#include <array>
#include "FedmConst.h"
#include "FedmHide.h"

namespace FEDM {


/// @brief DATA class for ISO14443 MIFARE transponder authentication, i.e. MIFARE classic, MIFARE mini, MIFARE 1K or 4K.
class FEDM_CLASS_DEF KeyMifareClassic
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	enum class KeyType {
		KeyA = 0,
		KeyB = 1
	};

	KeyMifareClassic();
	~KeyMifareClassic(); ///< Auto clear of memory

	void clear();

	KeyType type() const { return m_type; }
	void setType(KeyType type) { this->m_type = type; }

	void setKey(const std::array<uint8_t, 6> & key);

private:
	KeyType m_type;
	std::array<uint8_t, 6> m_key;
};



/// @brief DATA class for ISO14443 DES or AES transponder authentication, i.e. MIFARE DESFire, MIFARE Plus and MIFARE Ultralight C.
class FEDM_CLASS_DEF KeyMifareDesfire
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	enum class AuthenticationMode {
		DESFireNativeTDES = 0, ///< (16 byte) applicable for MIFARE DESFire
		StandardTDES = 1, ///< (16 byte) applicable for MIFARE DESFire and MIFARE Ultralight C
		DESFireNativeDES = 2, ///< (8 byte) applicable for MIFARE DESFire
		StandardDES = 3, ///< (8 byte) applicable for MIFARE DESFire
		_3KTDES = 4, ///< (24 byte) applicable for MIFARE DESFire
		AES = 5 ///< (16 byte) applicable for MIFARE DESFire and MIFARE Plus
	};

	KeyMifareDesfire();
	~KeyMifareDesfire(); ///< Auto clear of memory

	void clear();
	AuthenticationMode authMode() const { return m_authMode; }
	void setAuthMode(AuthenticationMode authMode) { this->m_authMode = authMode; }

	size_t keyLen() const { return m_keyLen; }
	void setKey(const uint8_t *key, size_t keyLen);

private:
	AuthenticationMode m_authMode;
	size_t m_keyLen;
	std::array<uint8_t, 24> m_key;
};



/// @brief DATA class for AES transponder authentication, useable for NXP UCODE/ICODE DNA.
class FEDM_CLASS_DEF KeyAes
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	enum class AesKeyType : uint8_t {
		Aes128Key = 0x00,
		Aes192Key = 0x01,
		Aes256Key = 0x02,
	};

	KeyAes();
	~KeyAes(); ///< Auto clear of memory

	void clear();

	AesKeyType type() const { return m_type; }
	void setType(AesKeyType type) { this->m_type = type; }

	size_t keyLen() const { return m_keyLen; }

	void setKey(const uint8_t *key, size_t keyLen);

private:
	AesKeyType m_type;
	size_t m_keyLen;
	std::array<uint8_t, 32> m_key;
};



/// @brief DATA class for EPC transponder authentication
class FEDM_CLASS_DEF KeyEpc
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	KeyEpc();
	~KeyEpc(); ///< Auto clear of memory

	void clear();

	void setKey(const std::array<uint8_t, 4> & key);

private:
	std::array<uint8_t, 4> m_key;
};



/// @brief DATA class with parameter for KeyManagement::setupReaderPassword()
///
/// See reader manual for details
class FEDM_CLASS_DEF SetPasswordParam
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	enum class Operation {
		Write = 0,
		Delete = 1
	};

	SetPasswordParam();

	void clear();

	Operation operation() const                 { return m_operation; }
	void      setOperation(Operation operation) { m_operation = operation; }

	int  privLevel() const           { return m_privLevel; }
	void setPrivLevel(int privLevel) { m_privLevel = privLevel; }

private:
	Operation m_operation;
	int       m_privLevel;
};

} // end of namespace FEDM

#endif // FEDM_KEYS_H_

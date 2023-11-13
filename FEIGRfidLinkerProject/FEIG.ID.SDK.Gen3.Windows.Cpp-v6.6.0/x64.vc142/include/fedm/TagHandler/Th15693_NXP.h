/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_NXP_H
#define FEDM_TH_ISO15693_NXP_H

#include "TagHandler/Th15693.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders from manufacturer NXP Semiconductors
///
/// High-level class for easy-to-use Transponder specific communication.<br>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_NXP : public ThIso15693
{
	friend class Internal::ReaderBase;

public:

	class FEDM_CLASS_DEF SystemInfo
	{
		friend class ThIso15693_NXP;
		friend class ThIso15693_NXP_IcodeSLI;

	public:
		/// @brief Returns  the protection pointer address
		size_t protectionPointerAddress() const { return m_protectionPointerAddress; }

		/// @brief Returns the protection settings
		uint8_t protectionPointerConditions() const { return m_protectionPointerConditions; }

		/// @brief Returns the lock settings
		uint8_t lockBits() const { return m_lockBits; }

		/// @brief Returns a list with flags of supported features
		const std::vector<size_t> & featureFlags() const { return m_featureFlags; }

	private:
		/// @brief protection pointer address
		size_t m_protectionPointerAddress;

		/// @brief protection settings
		uint8_t m_protectionPointerConditions;

		/// @brief lock settings
		uint8_t m_lockBits;

		/// @brief list with flags of supported features
		std::vector<size_t> m_featureFlags;
	}; // end of class SystemInfo

	/// The different passwords are addressed with the Password Identifier
	enum class PasswordIdentifier : uint8_t {
		Read = 0x01,
		Write = 0x02,
		Privacy = 0x04,
		Destroy = 0x08,
		EAS_AFI = 0x10
	};

	enum class ProtectionStatus : uint8_t {
		Public = 0x00,
		ReadWriteProtectedByReadPwd = 0x01,
		WriteProtected = 0x10,
		ReadWriteProtected = 0x11
	};

	virtual std::string transponderName() const override;

	virtual ~ThIso15693_NXP();

protected:
	ThIso15693_NXP(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_NXP

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_NXP_H

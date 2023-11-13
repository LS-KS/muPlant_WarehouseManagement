/**
*
* Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
*
* This software is the confidential and proprietary information of
* FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
* disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered
* into with FEIG ELECTRONIC GmbH.
*/

#ifndef FEDM_NET_ADDR_H
#define FEDM_NET_ADDR_H

#include "FedmBase.h"

#include <string>
#include <array>



namespace FEDM {

/// @brief DATA class for one MAC address
class FEDM_CLASS_DEF MacAddress
{
	friend class FedmFriend;

public:
	MacAddress();
	MacAddress(const std::string & addr);

	size_t size(void) const;
	void clear(void);
	bool isValid(void) const;

	uint8_t *data(void);
	const uint8_t *data(void) const;

	uint8_t & operator[] (size_t n);
	uint8_t operator[] (size_t n) const;

	MacAddress & operator=(const MacAddress & other);

	bool operator==(const MacAddress & other) const;
	bool operator!=(const MacAddress & other) const;

	std::string toString(void) const;
	bool fromString(const std::string & addr);

private:
	std::array<uint8_t, 6> m_array;
};



/// @brief DATA class for one IPv4 address
///
/// The bytes are in network (big endian) byte order.
class FEDM_CLASS_DEF IpV4Address
{
	friend class FedmFriend;

public:
	IpV4Address();
	IpV4Address(const std::string & addr);

	size_t size(void) const;
	void clear(void);
	bool isValid(void) const;

	uint8_t *data(void);
	const uint8_t *data(void) const;

	uint8_t & operator[] (size_t n);
	uint8_t operator[] (size_t n) const;

	IpV4Address & operator=(const IpV4Address & other);

	bool operator==(const IpV4Address & other) const;
	bool operator!=(const IpV4Address & other) const;

	std::string toString(void) const;
	bool fromString(const std::string & addr);

	size_t maskLength(void) const;

	static IpV4Address createNetMask(size_t maskLength);

private:
	std::array<uint8_t, 4> m_array;
};



/// @brief DATA class for one IPv6 address
///
/// The bytes are in network (big endian) byte order.
class FEDM_CLASS_DEF IpV6Address
{
	friend class FedmFriend;

public:
	IpV6Address();
	IpV6Address(const std::string & addr);

	size_t size(void) const;
	void clear(void);
	bool isValid(void) const;

	uint8_t *data(void);
	const uint8_t *data(void) const;

	uint8_t & operator[] (size_t n);
	uint8_t operator[] (size_t n) const;

	IpV6Address & operator=(const IpV6Address & other);

	bool operator==(const IpV6Address & other) const;
	bool operator!=(const IpV6Address & other) const;

	std::string toString(void) const;
	bool fromString(const std::string & addr);

	size_t maskLength(void) const;

	static IpV6Address createNetMask(size_t maskLength);

private:
	std::array<uint8_t, 16> m_array;

/* Unicast addresses:
*
*  - Link Locale:
*    FE80::<a>:<b>:<c>:<d>/64
*      with <a>:<b>:<c>:<d> is the 64Bit-Interface-ID
*
*  - Unique Locale:
*    FD00::/8 + 40Bit-Global-ID + 16Bit-Subnet-ID + 64Bit-Interface-ID  // private administration
*    FC00::/8 + 40Bit-Global-ID + 16Bit-Subnet-ID + 64Bit-Interface-ID  // global administration
*
*  - Unique Global:
*    2000::/3 + 61Bit-Subnet-ID + 64Bit-Interface-ID
*/
};

}; // end of namespace FEDM

#endif // FEDM_NET_ADDR_H

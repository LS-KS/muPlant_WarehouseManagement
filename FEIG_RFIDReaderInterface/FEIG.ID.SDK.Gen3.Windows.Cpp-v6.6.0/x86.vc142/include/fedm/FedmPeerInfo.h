/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_PEER_INFO_H
#define FEDM_PEER_INFO_H

#include <string>
#include <FedmBase.h>



namespace FEDM {

/// @brief DATA class with peer information of an accepted reader connection request
class FEDM_CLASS_DEF PeerInfo
{
	friend class FedmFriend;
private:
	std::string m_ipAddress;
	int  m_port;

public:
	PeerInfo();
	PeerInfo(const std::string & ipAddress, int port);

	void clear(void);
	std::string toString() const;
	void fromString(const std::string & peerInfo);

	/// @brief Get remote IP address
	std::string ipAddress() const { return m_ipAddress; }

	/// @brief Get remote port
	int port() const { return m_port; }
};

}; // end of namespace FEDM

#endif // FEDM_PEER_INFO_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TRACE_LOG_MANAGER_H
#define FEDM_TRACE_LOG_MANAGER_H

#include "FedmBasic.h"



namespace FEDM {



/// @brief DATA class with parameters for trace logging
class FEDM_CLASS_DEF TraceLogParameter
{
	friend class FedmFriend;

public:
	TraceLogParameter();

	void clear(void);

	void setLogToConsole(void)
	{
	    m_logToConsole = true;
	}

	void setLogToFile(const std::string & path)
	{
	    m_logToFile = !path.empty();
	    m_logPath = path;
	}

	void setLogToUdp(const std::string & ipAddress, int port)
	{
	    m_logToUdp = (!ipAddress.empty()) && (port > 0) && (port <= 0xFFFF);
	    m_logUdpAddress = ipAddress;
	    m_logUdpPort = port;
	}

	void setLogToAndroidLogCat(void)
	{
	    m_logToAndroidLogCat = true;
	}

	void setLogFeisp(bool communication, bool manager, bool error)
	{
	    m_logFeisp = true;
	    m_logFeispCommunication = communication;
	    m_logFeispManager = manager;
	    m_logFeispError = error;
	}

	void setLogFedm(bool trace, bool error)
	{
	    m_logFedm = true;
	    m_logFedmTrace = trace;
	    m_logFedmError = error;
	}

	std::string toString(void) const;

private:
	bool        m_absTime; // up to now we use absolute time only
	bool        m_logToConsole;
	bool        m_logToFile; // shared file
	std::string m_logPath;
	bool        m_logToUdp;
	std::string m_logUdpAddress;
	int         m_logUdpPort;
	bool        m_logToAndroidLogCat;

	bool        m_logFeisp;
	bool        m_logFeispCommunication;
	bool        m_logFeispManager;
	bool        m_logFeispError;

	bool        m_logFedm;
	bool        m_logFedmTrace;
	bool        m_logFedmError;
};



/// @brief MANAGER class for SDK trace logging
///
/// Trace log parameter must be set before any other call to a SDK function takes place.
/// Otherwise the parameter setting will not have any effect.<br>
/// Trace logging can be activated via configuration file (fedm.conf) as well. Please go in contact with FEIG support for details.
class FEDM_CLASS_DEF TraceLogManager
{
public:
	/// @brief Set trace log parameters in expert mode.
	/// @param[in] parameter Parameter strings will be obtained by FEIG support if there is a need for special support.
	///
	/// There is rarely a need to use this function. Generally the second overload of this function is the best choice.
	static void setParameter(const std::string & parameter);

	/// @brief Set trace log parameters in an easy way
	/// @param[in] parameter A trace log parameter class
	static void setParameter(const TraceLogParameter & parameter);
};

}; // end of namespace FEDM

#endif // FEDM_TRACE_LOG_MANAGER_H

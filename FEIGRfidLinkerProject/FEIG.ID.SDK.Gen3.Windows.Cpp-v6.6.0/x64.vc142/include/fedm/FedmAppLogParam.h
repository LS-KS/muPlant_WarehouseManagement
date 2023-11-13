/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_APP_LOG_PARAM_H
#define FEDM_APP_LOG_PARAM_H

#include <string>

#include "FedmBase.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief DATA class with parameter for application logging
///
/// This parameter class is used by function startLogging() in group Log.
class FEDM_CLASS_DEF AppLoggingParam
{
	friend class FedmFriend;

public:
    AppLoggingParam();
    ~AppLoggingParam();

    /// @brief Create parameter for a queue logger
    static AppLoggingParam createQueueLogger(void);

    /// @brief Create parameter for a file logger
    static AppLoggingParam createFileLogger(const std::string & filename);

    /// @brief Create parameter for an UDP logger
    static AppLoggingParam createUdpLogger(const std::string & ipAddress, int port);

    void useQueueLogging(bool on);
    void useFileLogging(const std::string & filename);
    void useUdpLogging(const std::string & ipAddress, int port);

    bool        isQueueLogging(void) const;

    bool        isFileLogging(void) const;
    std::string logFile(void) const;

    bool        isUdpLogging(void) const;
    std::string logUdpIpAddress(void) const;
    int         logUdpPort(void) const;

    std::string toString(void) const;

private:
    bool        m_logToQueue;
    std::string m_logToFile;
    std::string m_logToUdpAddr;
    int         m_logToUdpPort;

}; // end of class AppLoggingParam

}; // end of namespace FEDM

#endif // FEDM_APP_LOG_PARAM_H

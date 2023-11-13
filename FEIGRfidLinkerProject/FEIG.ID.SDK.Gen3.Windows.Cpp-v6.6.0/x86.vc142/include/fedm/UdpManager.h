/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_UDP_MANAGER_H
#define FEDM_UDP_MANAGER_H

#include "FedmBasic.h"



namespace FEDM {



/// @brief DATA class with access information of a TCP reader
///
/// This information has 3 status types:<br>
/// New reader: A new reader appeared on UDP scan.<br>
/// Reader gone: A reader disappeared on UDP scan.<br>
/// Reader changed: The TCP access information of an already scanned reader changed.<br>
/// This state information is only valid if popped from the event queue
class FEDM_CLASS_DEF UdpNetConfig
{
	friend class FedmFriend;
public:
    static const int NetworkTypeUnknown = 0;
    static const int NetworkTypeEthernet = 1;
    static const int NetworkTypeWifi = 2;

    /// @brief Creates an invalid network configuration item.
    UdpNetConfig();

    /// @brief Set the network configuration item to invalid.
    void clear(void);

    /// When moving from UdpManager.popDiscover() to UdpManager.setup()<br>
    /// This does not clear readerType, deviceId, networkType and the enable flags<br>
    /// The network configuration item stays valid.
    void clearSetup(void);

    /// @brief Check the validity of this network configuration item
    /// @return true: The network configuration item is valid, we have reader type, device ID and network type<br>
    /// false: In case of an empty event queue we get an invalid item
    bool isValid(void) const;

    /// @brief Check if this network configuration belongs to a newly appeared reader
    /// @return true: This reader appeared on UDP scan.
    bool isNewReader(void) const;

    /// @brief Check if this network configuration belongs to a disappeared reader
    /// @return true: This disappeared on UDP scan.
    bool isReaderGone(void) const;

    /// @brief Check if this network configuration is a change
    /// @return true: The TCP access information of an already scanned reader changed.
    bool isReaderChanged(void) const;

    bool isMacAddress(void) const { return !m_macAddress.empty(); }
    bool isIpAddress (void) const { return !m_ipAddress.empty(); }
    bool isPort      (void) const { return m_port > 0; }
    bool isNetMask   (void) const { return !m_netMask.empty(); }
    bool isGateway   (void) const { return !m_gateway.empty(); }
    bool isHostname  (void) const { return !m_hostname.empty(); }
    bool isDomain    (void) const { return !m_domain.empty(); }

    void setNetworkType(int type)      { m_networkType = type; }
    void setReaderType (uint32_t type) { m_readerType = type; }
    void setDeviceId   (uint32_t id)   { m_deviceId = id; }

    int      networkType(void) const { return m_networkType; }
    uint32_t readerType (void) const { return m_readerType; }
    uint32_t deviceId   (void) const { return m_deviceId; }
    std::string readerTypeToString(void) const;
    std::string deviceIdToHexString(void) const;

    void setMacAddress(const std::string & macAddr)  { m_macAddress = macAddr; }
    void setIpAddress (const std::string & ipAddr)   { m_ipAddress = ipAddr; }
    void setPort      (int port)                     { m_port = port; }
    void setNetMask   (const std::string & netMask)  { m_netMask = netMask; }
    void setGateway   (const std::string & gateway)  { m_gateway = gateway; }
    void setHostname  (const std::string & hostname) { m_hostname = hostname; }
    void setDomain    (const std::string & domain)   { m_domain = domain; }

    void setDhcpEnabled    (bool enable) { m_dhcpEnabled = enable; }
    void setHostnameEnabled(bool enable) { m_hostnameEnabled = enable; }

    const std::string & macAddress(void) const { return m_macAddress; }
    const std::string & ipAddress (void) const { return m_ipAddress; }
    int                 port      (void) const { return m_port; }
    const std::string & netMask   (void) const { return m_netMask; }
    const std::string & gateway   (void) const { return m_gateway; }
    const std::string & hostname  (void) const { return m_hostname; }
    const std::string & domain    (void) const { return m_domain; }

    bool isDhcpEnabled    (void) const { return m_dhcpEnabled; }
    bool isHostnameEnabled(void) const { return m_hostnameEnabled; }

    /// @return A connector via IP address and port for ReaderModule's connect function
    Connector connectorViaIpAddress(void) const;
 
    /// @return A connector via Hostname.Domain and port for ReaderModule's connect function
    Connector connectorViaHostname(void) const;

    std::string toString(void) const;
    void        fromString(const std::string & netConfig);

private:
    int         m_state;
    uint32_t    m_readerType;
    uint32_t    m_deviceId;
    int         m_networkType;
    std::string m_macAddress;
    std::string m_ipAddress;
    int         m_port;
    std::string m_netMask;
    std::string m_gateway;
    std::string m_hostname;
    std::string m_domain;
    bool        m_dhcpEnabled;
    bool        m_hostnameEnabled;
};



/// @brief LISTENER for UDP scanning
class FEDM_CLASS_DEF IUdpListener
{
public:
    /// @brief Receives UDP scan events
    ///
	/// This function is running in an own thread.<br>
    /// The overloaded implementation must be reentrant.
    virtual void onUdpEvent(void) { }
};



/// @brief MANAGER class for UDP discovering
///
/// This class supports an UDP scan event queue
class FEDM_CLASS_DEF UdpManager
{
public:
    /// @brief Starts the USB discovering
    ///
    /// @param[in] networkType Up to now, we support UdpNetConfig::NetworkTypeEthernet only
    /// @param[in] interfaceAddress The IP address of the network interface. We support address type IPv4 only.
    /// @param[in] listener A pointer to a listener instance to receive UDP scan events
    /// @return #{DOC_LIB_ERROR_VALUE}
    static int startDiscover(int networkType, const std::string & interfaceAddress, IUdpListener *listener = nullptr);

    /// @brief Stopps the UDP discovering an clears the event queue
    ///
    /// @return #{DOC_LIB_ERROR_VALUE}
    static int stopDiscover(void);

    /// @brief Get the current queue size
    ///
    /// @return The count of UdpNetConfig items in the event queue.
    static size_t readerCount(void);

    /// @brief Get the next queue item
    ///
    /// @return The next UdpNetConfig item. If the queue is empty, the item is invalid
    static UdpNetConfig popDiscover(void);

    /// @brief Change a readers network configuration
    ///
    /// @param[in] netConfig The network configuration to be changed. The setup is only performed for valid items in netConfig.
    /// @param[in] reboot If true the reader will perform a system reset.
    /// @return #{DOC_LIB_ERROR_VALUE}
    static int setup(const UdpNetConfig & netConfig, bool reboot = true);

	static int lastError(void);
	static std::string lastErrorText(void);

}; // end of class UdpManger

}; // end of namespace FEDM

#endif // FEDM_UDP_MANAGER_H

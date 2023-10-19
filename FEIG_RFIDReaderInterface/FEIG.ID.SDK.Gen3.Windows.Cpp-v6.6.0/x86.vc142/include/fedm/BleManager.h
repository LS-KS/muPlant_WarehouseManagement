/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_BlUETOOTH_LE_MANAGER_H
#define FEDM_BlUETOOTH_LE_MANAGER_H

#include "FedmBasic.h"



namespace FEDM {



/// @brief DATA class with access information of a Bluetooth LE reader
///
/// The state information (NewReader / ReaderGone) is only valid if popped from the event queue
class FEDM_CLASS_DEF BluetoothLeScanInfo
{
	friend class FedmFriend;
public:
    /// @brief Creates an invalid scan info item.
	BluetoothLeScanInfo();

    /// @brief Set the scan info item to invalid.
    void clear(void);

    /// @brief Check the validity of the scan info
    /// @return true: The scan info item is valid, we have reader type, device ID and MAC address<br>
    /// false: In case of an empty event queue we get an invalid item
    bool isValid(void) const;

    /// @brief Check if this scan info belongs to a newly appeared reader
    /// @return true: This reader appeared on BLE scan.
    bool isNewReader (void) const;

    /// @brief Check if this scan info belongs to a disappeared reader
    /// @return true: This disappeared on BLE scan.
    bool isReaderGone(void) const;

    void setReaderType(uint32_t type) { m_readerType = type; }
    void setDeviceId  (uint32_t id)   { m_deviceId = id; }
    void setMacAddress(const std::string & macAddr) { m_macAddress = macAddr; }

    uint32_t readerType(void) const { return m_readerType; }
    uint32_t deviceId  (void) const { return m_deviceId; }
    std::string readerTypeToString(void) const;
    std::string deviceIdToHexString(void) const;
    std::string macAddress(void) const { return m_macAddress; }

    /// @return A connector for ReaderModule's connect function
    Connector connector(void) const;

    void fromString(const std::string & scanInfo);

private:
    int         m_state;
    uint32_t    m_readerType;
    uint32_t    m_deviceId;
    std::string m_macAddress;
};



/// @brief LISTENER for Bluetooth LE scanning
class FEDM_CLASS_DEF IBluetoothLeListener
{
public:
    /// @brief Receives Bluetooth LE scan events
    ///
	/// This function is running in an own thread.<br>
    /// The overloaded implementation must be reentrant.
    virtual void onBluetoothLeEvent(void) { }
};



/// @brief MANAGER class for Bluetooth LE discovering
///
/// This class supports a Bluetooth LE scan event queue
class FEDM_CLASS_DEF BluetoothLeManager
{
public:
    /// @brief Starts the Bluetooth LE discovering
    ///
    /// @param[in] listener A pointer to a listener instance to receive BLE scan events
    /// @return #{DOC_LIB_ERROR_VALUE}
	static int startDiscover(IBluetoothLeListener *listener = nullptr);

    /// @brief Stopps the Bluetooth LE discovering an clears the event queue
    ///
    /// @return #{DOC_LIB_ERROR_VALUE}
    static int stopDiscover(void);

    /// @brief Get the current queue size
    ///
    /// @return The count of BluetoothLeScanInfo items in the event queue.
	static size_t readerCount(void);

    /// @brief Get the next queue item
    ///
    /// @return The next BluetoothLeScanInfo item. If the queue is empty, the item is invalid
    static BluetoothLeScanInfo popDiscover(void);

	static int lastError(void);
	static std::string lastErrorText(void);

}; // end of class BluetoothLeManager

}; // end of namespace FEDM

#endif // FEDM_BlUETOOTH_LE_MANAGER_H

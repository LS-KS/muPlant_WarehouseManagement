/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_USB_MANAGER_H
#define FEDM_USB_MANAGER_H

#include "FedmBasic.h"



namespace FEDM {



/// @brief DATA class with access information of a plugged or unplugged USB reader
///
/// The state information (NewReader=plugged / ReaderGone=unplugged) is only valid if popped from the event queue
class FEDM_CLASS_DEF UsbScanInfo
{
	friend class FedmFriend;
public:
    /// @brief Creates an invalid scan info item.
	UsbScanInfo();

    /// @brief Set the scan info item to invalid.
    void clear(void);

    /// @brief Check the validity of the scan info
    /// @return true: The scan info item is valid, we have reader type and device ID<br>
    /// false: In case of an empty event queue we get an invalid item
    bool isValid(void) const;

    /// @brief Check if this scan info is for a new plugged USB reader
    /// @return true: This reader was plugged to USB
    bool isNewReader(void) const;

    /// @brief Check if this scan info is for an unplugged USB reader
    /// @return true: This reader was unplugged from USB
    bool isReaderGone(void) const;

    void setReaderType(uint32_t type) { m_readerType = type; }
    void setDeviceId  (uint32_t id)   { m_deviceId = id; }

    uint32_t readerType(void) const { return m_readerType; }
    uint32_t deviceId  (void) const { return m_deviceId; }
    std::string readerTypeToString(void) const;
    std::string deviceIdToHexString(void) const;

    /// @return A connector for ReaderModule's connect function
    Connector connector(void) const;

    void fromString(const std::string & scanInfo);

private:
    int         m_state;
    uint32_t    m_readerType;
    uint32_t    m_deviceId;

};



/// @brief LISTENER for USB plugging and unplugging
class FEDM_CLASS_DEF IUsbListener
{
public:
	/// @brief Receives plug / unplug events
    ///
    /// This function is running in an own thread.<br>
    /// The overloaded implementation must be reentrant.
    virtual void onUsbEvent(void) { }
};



/// @brief MANAGER class for USB discovering
///
/// This class supports an USB plug / unplug event queue
class FEDM_CLASS_DEF UsbManager
{
public:
    /// @brief Starts the USB discovering and performs an intitial USB enumeration
    ///
    /// @param[in] listener A pointer to a listener instance to receive plug / unplug events
    /// @return <0: An error<br>
    /// >=0: The enumerated reader count of the first scan, i.e. the number of UsbScanInfo items in the event queue.
	static int startDiscover(IUsbListener *listener = nullptr);

    /// @brief Stopps the USB discovering an clears the event queue
    ///
    /// @return #{DOC_LIB_ERROR_VALUE}
    static int stopDiscover(void);

    /// @brief Get the current queue size
    ///
    /// @return The count of UsbScanInfo items in the event queue.
	static size_t readerCount(void);

    /// @brief Get the next queue item
    ///
    /// @return The next UsbScanInfo item. If the queue is empty, the item is invalid
    static UsbScanInfo popDiscover(void);

	static int lastError(void);
	static std::string lastErrorText(void);

}; // end of class UsbManger

}; // end of namespace FEDM

#endif // FEDM_USB_MANAGER_H

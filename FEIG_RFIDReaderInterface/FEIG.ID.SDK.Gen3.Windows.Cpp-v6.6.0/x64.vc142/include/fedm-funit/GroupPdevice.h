/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_PDEVICE_H
#define FEDM_GROUP_PDEVICE_H

#include <memory>

#include <FedmFunitBasic.h>
#include <FedmFunitElements.h>
#include <FedmFunitHide.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief GROUP class for peripheral device support
///
/// When using peripheral devices, the underlying ReaderModule must be in connected state before calling createAllDevices().<br>
/// The reader should configured to HostMode. In other operation modes the reader operations to peripheral devices could conflict with your application operations.
class FEDM_FUNIT_CLASS_DEF Pdevice
{
    friend class ExtensionModule;

public:
/** @name Main
 */
///@{

	/// @brief Create all peripheral devices objects
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This function performs a readReaderInfo and creates peripheral devices objects according to PeriphDev of ReaderInfo.<br>
	/// The underlying ReaderModule must be in connected state.
	int createAllDevices(void);
	
	/// @brief Destroy all created peripheral devices objects
	void removeAllDevices(void);
	
	/// @brief Get a peripheral device object by address
	/// @return A pointer to the peripheral device object or nullptr if no device exists for the given bus address
	PdeviceElement *deviceByAddress(const PdeviceAddress & address) const;

	/// @brief Get the first peripheral device object (lowest bus address)
	/// @return A pointer to the peripheral device object or nullptr if there no devices
	PdeviceElement *firstDevice(void);
	
	/// @brief Get the next peripheral device object (next higher bus address)
	/// @return A pointer to the peripheral device object or nullptr if there is no further device
	PdeviceElement *nextDevice(void);

	/// @brief Query a summary description of the total peripheral device equipment
	///
	/// Call this function after createAllDevices().<br>
	/// The information an diagnostic data of all devices will be read.
	std::string summary(void);

///@}



/** @name People Counter Event Queue
 */
///@{
	/// @brief Clear the people counter queue
	void clearPeopleCounterQueue(void);

	/// @brief Set the maximum people counter queue size
	/// @param[in] max Maximum size of the queue
	/// In case of a full queue: The eldest item is removed before the new item is pushed.
	void setPeopleCounterQueueMaxCount(size_t max);

	/// @brief Get the maximum people counter queue size
	/// @return The maximum number of items in the queue
	size_t maxPeopleCounterQueueCount(void) const;

	/// @brief Current people counter queue size
	/// @return The number of items in the queue
	size_t peopleCounterQueueCount(void) const;

	/// @brief People counter item access
	/// @return The next people counter item as unique pointer or an empty pointer (nullptr) if the queue is empty
	std::unique_ptr<const PeopleCounterEventItem> popPeopleCounterItem(void);
///@}

protected:
    Pdevice();

    Internal::FunitWorker *m_funitWorker; // set by a friend

}; // end of class Funit

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_GROUP_PDEVICE_H

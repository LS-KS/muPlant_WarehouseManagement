/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_TAG_EVENT_H
#define FEDM_GROUP_TAG_EVENT_H

#include <memory>

#include "FedmBasic.h"
#include "FedmHide.h"
#include "TagHandler/Th.h"



namespace FEDM {

/// @brief GROUP class for Buffered Read Mode and Notification Mode based on command [0x2B]
///
/// All functions of the TagEventItem queue are thread save
class FEDM_CLASS_DEF TagEvent
{
	friend class ReaderModule;
	
public:
/** @name Main
 */
///@{					
	/// @brief Read Buffer (command [0x2B])
	/// @param[in] dataSets The number of TagEventItems to be read
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readReaderBuffer(size_t dataSets);

	/// @brief Clear Buffer (command [0x32])
	/// @return #{DOC_LIB_RETURN_VALUE}
	int clearReaderBuffer(void);

	/// @brief Initialize Buffer (command [0x33])
	/// @return #{DOC_LIB_RETURN_VALUE}
	int initializeReaderBuffer(void);

	/// @brief Get Buffer Info (command [0x31])
	/// @param[out] maxTags Capacity of the readers buffer
	/// @param[out] firstTag The index of the first valid item
	/// @param[out] numTags Number of items currently stored in the buffer
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readReaderBufferInfo(BufferInfo & bufferInfo);

	/// @brief Force a trigger to start RFID event notification (command [0x34], mode [0x01])
	/// @param[in] scanTime The scan duration (msec). Value 0 or negative means infinite. RFID scanning can be stopped by triggerStopRfidEvent().
	/// @return #{DOC_LIB_RETURN_VALUE}
	int triggerStartRfidEvent(int scanTime = 0);

	/// @brief Force a trigger to stop RFID event notification (command [0x34], mode [0x10])
	/// @return #{DOC_LIB_RETURN_VALUE}
	int triggerStopRfidEvent(void);

	/// @brief Force a trigger to start barcode event notification (command [0x34], mode [0x01])
	/// @param[in] scanTime The scan duration (msec). This time must not be 0 or negative. Barcode scanning cannot be stopped by command.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int triggerStartBarcodeEvent(int scanTime);

	/// @brief Change the data layout of TagEventItems (command [0x3A])
	/// @param[in] tagEventLayout Configuration for tag event layout in scan mode
	/// @param[in] scanEngine
	/// @return #{DOC_LIB_RETURN_VALUE}
	int changeReaderTagEventLayout(const TagEventLayout & tagEventLayout, int scanEngine);
///@}



/** @name Tag Event Queue
 */
///@{
	/// @brief Clear the TagEventItem queue
	void clearQueue(void);

	/// @brief Set the maximum TagEventItem queue size
	/// @param[in] max Maximum size of the queue.<br>
	/// In case of a full queue: The eldest item is removed before the new item is pushed.
	void setQueueMaxItemCount(size_t max);

	/// @brief Get the maximum TagEventItem queue size
	/// @return The maximum number of items in the queue
	size_t queueMaxItemCount(void) const;

	/// @brief Current TagEventItem queue size
	/// @return The number of available TagEventItem's in the queue
	size_t queueItemCount(void) const;

	/// @brief TagEventItem access
	/// @return The next TagEventItem as unique pointer or an empty pointer (nullptr) if the queue is empty
	std::unique_ptr<const TagEventItem> popItem(void);

	/// @brief Create a tag handler in addressed mode
	/// @return A tag handler created by the TagEventItem
	std::unique_ptr<TagHandler::ThBase> createTagHandler(const TagEventItem & tagEventItem) const;
///@}

protected:
	TagEvent();
	~TagEvent();

	Internal::ReaderBase  *m_rdrBase; // set by a friend

};

}; // end of namespace FEDM

#endif // FEDM_GROUP_TAG_EVENT_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_BRM_H
#define FEDM_GROUP_BRM_H

#include <memory>

#include "FedmBasic.h"
#include "FedmHide.h"
#include "TagHandler/Th.h"



namespace FEDM {

/// @brief GROUP class for Buffered Read Mode and Notification Mode based on command [0x22]
///
/// All functions of the BrmItem queue are thread save
class FEDM_CLASS_DEF Brm
{
	friend class ReaderModule;
	
public:
/** @name Main
 */
///@{					
	/// @brief Read Buffer (command [0x22])
	/// @param[in] dataSets The number of BrmEventItems to be read
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

	/// @brief Force a notification (command [0x34], mode [0x00])
	/// @return #{DOC_LIB_RETURN_VALUE}
	int triggerNotification(void);
	


	/// @brief Set response behavior of command [0x22] for Notification Mode
	/// @param[in] yes If true an acknowledge response command [0x32] is send<br>
	/// If false no response is send
	void setSendAcknowlegdeToBrmEvent_0x22(bool yes);
///@}



/** @name Brm Queue
 */
///@{
	/// @brief Clear the BrmItem queue
	void clearQueue(void);

	/// @brief Set the maximum BrmItem queue size
	/// @param[in] max Maximum size of the queue.<br>
	/// In case of a full queue: The eldest item is removed before the new item is pushed.
	void setQueueMaxItemCount(size_t max);

	/// @brief Get the maximum BrmItem queue size
	/// @return The maximum number of items in the queue
	size_t queueMaxItemCount(void) const;

	/// @brief Current BrmItem queue size
	/// @return The number of available BrmItem's in the queue
	size_t queueItemCount(void) const;

	/// @brief BrmItem access
	/// @return The next BrmItem as unique pointer or an empty pointer (nullptr) if the queue is empty
	std::unique_ptr<const BrmItem> popItem(void);

	/// @brief Create a tag handler in addressed mode
	/// @return A tag handler created by the BrmItem
	std::unique_ptr<TagHandler::ThBase> createTagHandler(const BrmItem & brmItem) const;
///@}

protected:
	Brm();
	~Brm();

	Internal::ReaderBase  *m_rdrBase; // set by a friend

};

}; // end of namespace FEDM

#endif // FEDM_GROUP_BRM_H

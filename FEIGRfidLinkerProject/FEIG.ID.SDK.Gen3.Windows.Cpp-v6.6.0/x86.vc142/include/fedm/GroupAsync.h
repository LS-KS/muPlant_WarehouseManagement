/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_ASYNC_H
#define FEDM_GROUP_ASYNC_H

#include <memory>

#include "FedmBasic.h"
#include "FedmHide.h"
#include "IListenRdr.h"



namespace FEDM {

/// @brief GROUP class for activation of reader driven requests
///
/// To obtain events from a reader via TCP, use the startListenerThread()-function of the ReaderModule to listen for a reader connection request.<br>
/// Use startNotification() to start sampling of reader request data. Optionally you can install an IReaderListener. All event types are signaled via the IReaderListener.<br>
/// Use popEvent to obtain information about the event type.<br>
/// <br>
/// The various event data can be accessed here:<br>
/// - EventType::IdentificationEvent (command 0x2A): Use functions identification() or info() to obtain basic information about the connected reader.<br>
/// This event type is send once after a successful reader connection request.<br>
/// - EventType::DiagEvent (command 0x2D, command 0x6E mode 0x01): Use function popItem() of group diag().<br>
/// - EventType::TagEvent (command 0x2B): Transponder data can be read via function popItem() of group tagEvent().<br>
/// - EventType::BrmEvent (command 0x22): Transponder data can be read via function popItem() of group brm().<br>
/// - EventType::InputEvent (command 0x2C, 0x74): Use function popInItem() of group io().<br>
/// - EventType::PeopleCounterEvent (command 0x2E, 0x77): See group pdevice() of library fedm-funit.<br>
/// <br>
/// The access to all event queues is thread save ( clearQueue(), setQueueMaxItemCount(), queueMaxItemCount(), queueItemCount(), popItem() ).<br>
/// A call to the information getter functions (identification(), info(), diag().data()) is thread save as well.<br>
/// All other functions of the ReaderModule must be called by the same thread!<br>
/// Best practice: use one thread for each ReaderModule for communication.<br>
class FEDM_CLASS_DEF Async
{
	friend class ReaderModule;
	friend class FedmFriend;
	friend class Internal::FunitWorker;

public:
/** @name Main
 */
///@{
	/// @brief Prepare the ReaderModule to handle reader requests
	/// @param[in] listener All event types are signaled via the IReaderListener.<br>
	/// If no listener is set the event type queue and / or the various event data queues must be polled.
	///
	/// Starts sampling of reader request data into the associated event data queues.<br>
	/// Use the event type queue to decide which event data queue holds new data.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int startNotification(IReaderListener *listener = nullptr);

	/// @brief Stop sampling of reader request data.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int stopNotification(void);
///@}



/** @name Event Type Queue
 */
///@{
	/// @brief Clear the event type queue
	void clearEvent(void);

	/// @brief Set the maximum event type queue size
	/// @param[in] max Maximum size of the queue.<br>
	/// In case of a full queue: The eldest item is removed before the new item is pushed.
	void setMaxEventCount(size_t max);

	/// @brief Get the maximum event type queue size
	/// @return The maximum number of items in the queue
	size_t maxEventCount(void) const;

	/// @brief Current event type queue size
	/// @return The number of items in the queue
	size_t eventCount(void) const;

	/// @brief Event type access
	/// @param[out] state The request command state send by the reader
	/// @param[out] command The request command byte
	/// @return The next event type value or an invalid EventType if the queue is empty
	EventType popEvent(int *state = nullptr, uint8_t *command = nullptr);
///@}

protected:
	Async();

	Internal::ReaderBase  *m_rdrBase; // set by a friend

}; // end of class Async

}; // end of namespace FEDM

#endif // FEDM_GROUP_ASYNC_H

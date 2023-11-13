/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_LOG_H
#define FEDM_GROUP_LOG_H

#include <string>
#include <memory>

#include "FedmBasic.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief GROUP class for application logging facilities
///
/// This class supports logging of request and response protocols to and from a reader.
/// The application can push own log messages at any time.<br>
/// Each log messages has a time stamp.<br>
/// Logging outputter can be configured.<br>
///
/// For SDK trace logging use the TraceLogManager class.
class FEDM_CLASS_DEF Log
{
	friend class ReaderModule;

public:
/** @name Main
 */
///@{
	/// @brief Start application logging facility
	/// @param[in] param Parameter for logging outputter
	///
	/// Logging will be done for all exchanged protocols to and from reader.<br>
	/// The application can output own messages at any time (see appendLogMessage()).
	int startLogging(const AppLoggingParam & param);

	/// @brief Stop application logging facility
	int stopLogging(void);

	/// @brief Inject an application message to the protocol logging facility
	/// @param[in] message Append this message all configured logging outputter.<br>
	/// A timestamp is prepended and a newline termination is appended to the message string.<br>
	/// This function is thread save.
	void appendLogMessage(const std::string & message);
///@}



/** @name Logging Queue
 */
///@{
	/// @brief Clear the log message queue
	void clearQueue(void);

	/// @brief Set the maximum log message queue size
	/// @param[in] max Maximum size of the queue.<br>
	/// In case of a full queue: The eldest item is removed before the new item is pushed.<br>
	/// If max=0 the log message queue is disabled.
	void setQueueMaxItemCount(size_t max);

	/// @brief Get the maximum log message queue size
	/// @return The maximum number of log messages in the queue
	size_t queueMaxItemCount(void) const;

	/// @brief Current log message queue size
	/// @return The number of available log messages in the queue
	size_t queueItemCount(void) const;

	/// @brief Log message access
	/// @return The next log message as unique pointer or an empty pointer (nullptr) if the queue is empty
	std::unique_ptr<const std::string> popItem(void);
///@}

protected:
	Log();
	~Log();

	Internal::ReaderBase   *m_rdrBase; // set by a friend

}; // end of class ILogGroup

}; // end of namespace FEDM

#endif // FEDM_GROUP_LOG_H

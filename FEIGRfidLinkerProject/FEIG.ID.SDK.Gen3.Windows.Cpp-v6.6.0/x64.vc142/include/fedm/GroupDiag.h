/**
*
* Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
*
* This software is the confidential and proprietary information of
* FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
* disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered
* into with FEIG ELECTRONIC GmbH.
*/

#ifndef FEDM_GROUP_DIAG_H
#define FEDM_GROUP_DIAG_H

#include <memory>

#include "FedmBasic.h"
#include "FedmHide.h"



namespace FEDM {

/// @brief GROUP class for reader diagnostic data via application and reader driven requests
///
/// All functions of the diagnostic event queue and the data() function are thread save.
class FEDM_CLASS_DEF Diagnostic
{
	friend class ReaderModule;
	friend class FedmFriend;
	
public:
/** @name Main
 */
///@{
	/// @brief Read complete reader diagnostic data (command [0x6E])
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readReaderDiagnostic(void);

	/// @brief Get a copy of previously read diagnostic data
	///
	/// This function is thread save
	ReaderDiag data(void) const;



	/// @brief Read Diagnostic Buffer (command [0x2D] mode [0x00])
	/// @param[in] dataSets The number of DiagEventItems to be read
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readDiagnosticBuffer(size_t dataSets);

	/// @brief Clear Diagnostic Buffer (command [0x2D] mode [0x01])
	/// @return #{DOC_LIB_RETURN_VALUE}
	int clearDiagnosticBuffer(void);

///@}



/** @name Diag Event Queue
 */
///@{
	/// @brief  Clear the DiagEventItem queue
	void clearQueue(void);

	/// @brief Set the maximum DiagEventItem queue size
	/// @param[in] max Maximum size of the queue
	/// In case of a full queue: The eldest item is removed before the new item is pushed.
	void setQueueMaxItemCount(size_t max);

	/// @brief Get the maximum DiagEventItem queue size
	/// @return The maximum number of items in the queue
	size_t queueMaxItemCount(void) const;

	/// @brief Current DiagEventItem queue size
	/// @return The number of items in the queue
	size_t queueItemCount(void) const;

	/// @brief DiagEventItem item access
	/// @return The next diag status item as unique pointer or an empty pointer (nullptr) if the queue is empty
	std::unique_ptr<const DiagEventItem> popItem(void);
///@}

protected:
	Diagnostic();
	~Diagnostic();

	Internal::ReaderBase  *m_rdrBase; // set by a friend

};

}; // end of namespace FEDM

#endif // FEDM_GROUP_DIAG_H

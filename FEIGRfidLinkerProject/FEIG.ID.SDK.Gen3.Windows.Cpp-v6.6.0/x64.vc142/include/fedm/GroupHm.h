/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_HM_H
#define FEDM_GROUP_HM_H

#include <vector>
#include <memory>

#include "FedmBasic.h"
#include "FedmHide.h"
#include "TagHandler/Th.h"



namespace FEDM {

/// @brief GROUP class for application requests in reader Host Mode
class FEDM_CLASS_DEF Hm
{
	friend class ReaderModule;
	
public:

	enum class UsageMode {
		/// inventory() stores tag items in a table.<br>
		/// Access to the tag items must be carried out by the communication thread
		UseTable = 1,

		/// inventory() stores tag items in a queue.<br>
		/// Access to the tag items can be done by any thread
		UseQueue = 2
	};

/** @name Main
 */
///@{					
	void setUsageMode(UsageMode mode) { m_mode = mode; }

	/// @brief Command [0xB0][0x01]
	/// @param[in] all When true, inventory is repeated as long as the reader responds MORE status
	/// @param[in] param Parameter data class to define inventory behaviour.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// If parameter 'param' is created with the special InventoryParam constructor, the More flag must be controlled by the application.
	/// In that case the parameter 'all' is ignored.
	int inventory(bool all = true, const InventoryParam & param = InventoryParam());
///@}



// #################################################### USAGE OF TAG TABLE ##########################################
/** @name Usage of Tag Table
 */
///@{
	/// @brief Tag table size
	/// @return The number of available TagItem's
	size_t itemCount(void) const;


	/// @brief TagItem access via tag table
	/// @param[in] itemIndex The index of TagItem object from last inventory(). Valid range is 0...itemCount()-1.<br>
	/// If itemIndex is out of range std::out_of_range execption is thrown
	/// @return A reference to the inventory tag item
	const TagItem & tagItem(size_t itemIndex) const;


	/// @brief Get tag handler type of a tag table entry
	/// @param[in] itemIndex The index of TagItem object from last inventory(). Valid range is 0...itemCount()-1.<br>
	/// If itemIndex is out of range std::out_of_range execption is thrown
	/// @return The tag handlder type identifier (see #{DOC_LINK_TO_CLASS(FEDM::TagHandler::ThBase)})
	/// @note This function does not return sub types of TypeIso14443.
	uint32_t getTagHandlerType(size_t itemIndex) const;
///@}



// ################################################# USAGE OF TAG QUEUE ##########################################
/** @name Usage of Tag Queue
 */
///@{					
	/// @brief Clear the TagItem queue
	void clearQueue(void);

	/// @brief Set the maximum TagItem queue size
	/// @param[in] max Maximum size of the queue.<br>
	/// In case of a full queue: The eldest item is removed before the new item is pushed.
	void setQueueMaxItemCount(size_t max);

	/// @brief Get the maximum TagItem queue size
	/// @return The maximum number of tag items in the queue
	size_t queueMaxItemCount(void) const;

	/// @brief Current TagItem queue size
	/// @return The number of available tag items in the queue
	size_t queueItemCount(void) const;

	/// @brief TagItem access via tag queue
	/// @return The next tag item as unique pointer or an empty pointer (nullptr) if the queue is empty
	std::unique_ptr<const TagItem> popItem(void);
///@}



// ########################################### ADDRESSESED TAG HANDLER #############################################
/** @name Addressed Tag Handler
 */
///@{
	/// @brief Create a tag handler in addressed mode via tag table
	/// @param[in] itemIndex An index of the tag table.  Valid range is 0...itemCount()-1.<br>
	/// If itemIndex is out of range std::out_of_range execption is thrown
	std::unique_ptr<TagHandler::ThBase> createTagHandler(size_t itemIndex) const { return createTagHandler(tagItem(itemIndex)); }


	/// @brief Create a tag handler in addressed mode via tag table or tag queue
	/// @param[in] tagItem An item from tag table or tag queue
	/// @return An unique pointer object of the tag handler<br>
	/// An empty unique pointer is returned in case of an error<br>
	/// Use the reader module error handling functions to find out details
	std::unique_ptr<TagHandler::ThBase> createTagHandler(const TagItem & tagItem) const;
///@}



// ######################################### SELECTED TAG HANDLER #################################################
/** @name Selected Tag Handler
 */
///@{
	/// @brief Get a tag handler in selected mode via tag table (command [0xB0][0x25])
	/// @param[in] itemIndex An index of the tag table.  Valid range is 0...itemCount()-1.<br>
	/// If itemIndex is out of range std::out_of_range execption is thrown
	/// @param[in] tagDriver ...
	/// @return An unique pointer object of the tag handler<br>
	/// An empty unique pointer is returned in case of an error<br>
	/// Use the reader module error handling functions to find out details
	std::unique_ptr<TagHandler::ThBase> select(size_t itemIndex, FEDM::TagDriverForSelect tagDriver = FEDM::TagDriverForSelect::None) { return select(tagItem(itemIndex), tagDriver); }


	/// @brief Get a tag handler in selected mode via tag table or tag queue (command [0xB0][0x25])
	/// @param[in] tagItem The inventory tag item from tag table or tag queue
	/// @param[in] tagDriver ...
	/// @return An unique pointer object of the tag handler<br>
	/// An empty unique pointer is returned in case of an error<br>
	/// Use the reader module error handling functions to find out details
	std::unique_ptr<TagHandler::ThBase> select(const TagItem & tagItem, FEDM::TagDriverForSelect tagDriver = FEDM::TagDriverForSelect::None);
///@}



// ####################################### NON-ADDRESSED TAG HANDLER ##############################################
/** @name Non-Addressed Tag Handler
 */
///@{
	/// @brief Create a tag handler in non addressed mode
	/// @param[in] tagHandlerType The type of the tag handler (see #{DOC_LINK_TO_CLASS(FEDM::TagHandler::TH_Base)})
	/// @return An unique pointer object of the tag handler<br>
	/// In case of an unknown tagHandlerType the base tag handler class is returned
	std::unique_ptr<TagHandler::ThBase> createNonAddressedTagHandler(uint32_t tagHandlerType);
///@}

protected:
	Hm();
	~Hm();

	Internal::ReaderBase  *m_rdrBase; // set by a friend
	UsageMode m_mode;
};

}; // end of namespace FEDM

#endif // FEDM_GROUP_HM_H

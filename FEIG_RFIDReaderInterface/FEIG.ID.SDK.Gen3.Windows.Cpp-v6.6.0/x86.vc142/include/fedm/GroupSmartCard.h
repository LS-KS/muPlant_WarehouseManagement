/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_SMART_CARD_H
#define FEDM_GROUP_SMART_CARD_H

#include "FedmBasic.h"
#include "FedmHide.h"
#include <memory>


namespace FEDM {


/// @brief SMART-CARD-HANDLER class for communication with a smart card
class FEDM_CLASS_DEF SmartCardHandler
{
	friend class SmartCard;

public:
	~SmartCardHandler();

	/// @brief To copy a SmartCardHandler is not allowed
	SmartCardHandler(SmartCardHandler& other) = delete;

	/// @brief To copy a SmartCardHandler is not allowed
	SmartCardHandler(const SmartCardHandler& other) = delete;

	/// @brief To copy a SmartCardHandler is not allowed
	SmartCardHandler& operator=(SmartCardHandler& other) = delete;

	/// @brief To copy a SmartCardHandler is not allowed
	SmartCardHandler& operator=(const SmartCardHandler& other) = delete;

	int activate(const std::vector<uint8_t> & requestData, std::vector<uint8_t> & responseData);
	int deactivate();
	int apdu(const std::vector<uint8_t> & apduRequestData, std::vector<uint8_t> & apduResponseData);

private:
	SmartCardIso7816::SmartCardSlot *m_smartCardSlot;

	SmartCardHandler(SmartCardIso7816::SmartCardSlot *smartCardSlot);
};



/// @brief GROUP class to control smart cards of a reader
class FEDM_CLASS_DEF SmartCard
{
	friend class ReaderModule;
	
public:
	/// @brief Get count of available smart card slots
	/// @param[out] slotCount The count of available sots
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Requests the number of Smartcard slots from the reader
	int getSlots(size_t & slotCount);

	/// @brief Get slot information
	/// @param[in] slotNumber The slot that should be checked
	/// @return The slot information packed as 'SmartCardItem'
	///
	/// Returns information about the SAM slot
	/// The caller must verify that either 'getSlots()' has been called or a full reader info has been
	/// requested from the reader before this function is called
	SmartCardItem getSmartCardItem(unsigned int slotNumber) const;

	/// @brief Create smart card handler for a slot
	/// @param[in] smartCardItem The target SAM item
	/// @return An unique pointer to the slot handler instance or an empty unique pointer if the handler couldn't be created
	///
	/// Creates a SAM Slot handler for the slot
	std::unique_ptr<SmartCardHandler> createSmartCardHandler(const SmartCardItem & smartCardItem) const;

protected:
	SmartCard();
	~SmartCard();

	Internal::ReaderBase  *m_rdrBase; // set by a friend
};

}; // end of namespace FEDM

#endif // FEDM_GROUP_SMART_CARD_H

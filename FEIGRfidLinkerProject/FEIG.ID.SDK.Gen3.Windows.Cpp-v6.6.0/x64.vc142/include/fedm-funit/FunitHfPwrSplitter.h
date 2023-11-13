/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_HF_POWER_SPLITTER_H
#define FEDM_FUNIT_HF_POWER_SPLITTER_H


#include <FunitElement.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief FUNCTION-UNIT element class HF power splitter
///
/// A power splitter has one input and two outputs.<br>
/// This function unit element represents an 'ID ISC.ANT.PSM-B'.
class FEDM_FUNIT_CLASS_DEF FunitHfPwrSplitter : public FunitElement
{
	friend class Internal::FunitWorker;

public:
	std::string typeToString(void) const override;

	/// @brief Get a child element
	/// @param[in] outChannel Valid values are 1 or 2
	/// @return A pointer to the connected element at outChannel or nullptr if outChannel is out of range or no FunitElement is connected to the given outChannel
	FunitElement *child(size_t outChannel) const;

private:
	std::vector<FunitElement*> m_childElements;

	FunitHfPwrSplitter(size_t parentChannel, FunitElement *parent = nullptr);
	~FunitHfPwrSplitter();

};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_HF_POWER_SPLITTER_H

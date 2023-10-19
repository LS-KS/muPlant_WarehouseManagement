/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_HF_MUX_DUAL_H
#define FEDM_FUNIT_HF_MUX_DUAL_H


#include <FunitElement.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief FUNCTION-UNIT element class HF dual multiplexer with a preconnected HF power splitter
///
/// A dual multiplexer has two inputs which are connected to the two outputs of a power splitter.<br>
/// The parent channel of this function unit element is connected to the input of the power splitter.<br>
/// This input can be switched to one of N pairs of outputs. The output pair arrangement is fixed.<br>
/// In case of a dual 1to4 multiplexer the output pairs are: 1-8, 2-7, 3-6, 4-5<br>
/// This function unit element represents an 'ID ISC.ANT.MUX.M8' in dual mode with a
/// preconnected HF power splitter 'ID ISC.ANT.PSM-B'.
class FEDM_FUNIT_CLASS_DEF FunitHfMuxDual : public FunitElement
{
	friend class Internal::FunitWorker;

public:
	std::string typeToString(void) const override;

	/// @brief Get the count of output channel pairs
	/// @return The count of output channel pairs.
	size_t outChannelPairCount(void) const { return m_childElements.size() / 2; }
	
	/// @brief Get the firmware version of the multiplexer
	/// @return A reference to the firmware version object
	const FunitFirmwareVersion & firmwareVersion(void) const { return m_fwVersion; }

	/// @brief Get a child element
	/// @param[in] outChannel Is in the range 1 ... 2 x outChannelPairCount
	/// @return A pointer to the connected element at outChannel or nullptr if outChannel is out of range or no FunitElement is connected to the given outChannel
	FunitElement *child(size_t outChannel) const;

	/// @brief Get the current selected output channel 1
	/// @return The current selected output channel 1.<br>
	/// Returns UnknownChannel if the output state is unknown, i.e. no select was done before.
	size_t currentOutChannel1(void) const { return m_currentOutChannel1; }

	/// @brief Get the current selected output channel 2
	/// @return The current selected output channel 2.<br>
	/// Returns UnknownChannel if the output state is unknown, i.e. no select was done before.
	size_t currentOutChannel2(void) const { return m_currentOutChannel2; }

/*	/// @brief Select this multiplexer
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This will set the related readers RF output on and select all parent elements recursively.
	int selectMultiplexer(void);
*/

	/// @brief Perform a CPU reset of the multiplexer
	/// @return #{DOC_LIB_RETURN_VALUE}
	int resetCpu(void);

	/// @brief Perform a detection of the multiplexer
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// If successful this function automatically reads the firmware version of the multiplexer.
	int detect(void);

private:
	size_t m_cascadeLevel = 0;
	size_t m_currentOutChannel1 = UnknownChannel; // 0=off, -1=unknown, 1..outChannelPairCount
	size_t m_currentOutChannel2 = UnknownChannel; // 0=off, -1=unknown, m_currentOutChannel1 + outChannelPairCount
	std::vector<FunitElement*> m_childElements;
	std::map<size_t,size_t>    m_mapPairs;
	FunitFirmwareVersion       m_fwVersion;

	FunitHfMuxDual(size_t outChannelPairCount, size_t parentChannel, FunitElement *parentElement = nullptr);
	~FunitHfMuxDual();
	
	/// @brief Set the current output channel for this element
	/// @param[in] outChannel1 Is in the range 1 ... outChannelPairCount. Use 0 to set all outputs off.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	///
	/// The readers RF output must be set on and all parent multiplexer must be selected before.<br>
	/// outChannel2 is set to outChannel1 + outChannelPairCount
	int selectOutChannel(size_t outChannel);

	size_t channelPartner(size_t channel);

};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_HF_MUX_DUAL_H

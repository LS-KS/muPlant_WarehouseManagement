/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_HF_MUX_SINGLE_H
#define FEDM_FUNIT_HF_MUX_SINGLE_H

#include <FunitElement.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief FUNCTION-UNIT element class HF single multiplexer
///
/// A single multiplexer has one input which can be switched to one of N outputs.<br>
/// This function unit element can represent the following FEIG HF multiplexer:<br>
/// 'ID ISC.ANT.MUX.M8'<br>
/// 'ID ISC.ANT.MUX.M5'<br>
/// 'ID ISC.ANT.MUX.M4'
class FEDM_FUNIT_CLASS_DEF FunitHfMuxSingle : public FunitElement
{
	friend class Internal::FunitWorker;

public:
	std::string typeToString(void) const override;

	/// @brief Get the count of output channels
	/// @return The output channel count
	size_t outChannelCount(void) const { return m_childElements.size(); }
	
	/// @brief Get the firmware version of the multiplexer
	/// @return A reference to the firmware version object
	const FunitFirmwareVersion & firmwareVersion(void) const { return m_fwVersion; }

	/// @brief Get a child element
	/// @param[in] outChannel Is in the range 1 ... outChannelCount
	/// @return A pointer to the connected element at outChannel or nullptr if outChannel is out of range or no FunitElement is connected to the given outChannel
	FunitElement *child(size_t outChannel) const;

	/// @brief Get the current selected output channel
	/// @return The current selected output channel.<br>
	/// Returns UnknownChannel if the output state is unknown, i.e. no select was done before.
	size_t currentOutChannel(void) const { return m_currentOutChannel; }

/*	/// @brief Select this multiplexer
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This will set related the readers RF output on and select all parent elements recursively.
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

	/// @brief Read the multiplexer configuration
	/// @param[in] page The index of the configuration page
	/// @param[out] data The data of the configuration page
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Refer to the manual, if the multiplexer can be configured and which pages are available.
	int readConfig(size_t page, std::vector<uint8_t> & data);

	/// @brief Write the multiplexer configuration
	/// @param[in] page The index of the configuration page
	/// @param[in] data The data of the configuration page
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Refer to the manual, if the multiplexer can be configured and which pages are available.
	int writeConfig(size_t page, const std::vector<uint8_t> & data);

private:
	size_t m_cascadeLevel = 0;
	size_t m_currentOutChannel = UnknownChannel; // 0=off, -1=unknown, 1..outChannelCount
	std::vector<FunitElement*> m_childElements;
	FunitFirmwareVersion       m_fwVersion;

	FunitHfMuxSingle(size_t outChannelCount, size_t parentChannel, FunitElement *parentElement = nullptr);
	~FunitHfMuxSingle();
	
	/// @brief Set the current output channel for this element
	/// @param[in] outChannel Is in the range 1 ... outChannelCount. Use 0 to set all outputs off.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// The readers RF output must be set on and all parent multiplexer must be selected before.
	int selectOutChannel(size_t outChannel);

};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_HF_MUX_SINGLE_H

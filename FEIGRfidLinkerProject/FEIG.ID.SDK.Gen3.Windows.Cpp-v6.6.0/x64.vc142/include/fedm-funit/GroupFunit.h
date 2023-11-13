/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_FUNIT_H
#define FEDM_GROUP_FUNIT_H

#include <FedmFunitBasic.h>
#include <FedmFunitElements.h>
#include <FedmFunitHide.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief GROUP class for function unit support
///
/// When using function units, the reader type of the underlying ReaderModule must be set, i.e. a connection should be established, before the ExtensionModule is created!<br>
/// If the function readerRfChannelCount() returns 0 the reader type does not support function units.<br>
/// The reader should configured to HostMode. In other operation modes the reader will automatically scan the configured antennas.
class FEDM_FUNIT_CLASS_DEF Funit
{
    friend class ExtensionModule;

public:
	static const size_t DcPowerSupplyAuto = DC_POWER_SUPPLY_AUTO;
	static const size_t DcPowerSupplyAll = DC_POWER_SUPPLY_ALL;

	/// @brief Create a HF multiplexer - single 1 to 8
	/// @param[in] parentChannel The output channel of the parent which is connected to the multiplexers input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created multiplexer object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader or another HF multiplexer (single).<br>
	/// Valid output channels of this multiplexer are 1 ... 8.<br>
	/// Use this function to create a representation for an 'ID ISC.ANT.MUX.M8'.
	FunitHfMuxSingle *createHfMuxSingle_1to8(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a HF multiplexer - single 1 to 5
	/// @param[in] parentChannel The output channel of the parent which is connected to the multiplexers input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created multiplexer object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader or another HF multiplexer (single).<br>
	/// Valid output channels of this multiplexer are 1 ... 5.<br>
	/// Use this function to create a representation for an 'ID ISC.ANT.MUX.M5'.
	FunitHfMuxSingle *createHfMuxSingle_1to5(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a HF multiplexer - single 1 to 4
	/// @param[in] parentChannel The output channel of the parent which is connected to the multiplexers input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created multiplexer object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader or another HF multiplexer (single).<br>
	/// Valid output channels of this multiplexer are 1 ... 4.<br>
	/// Use this function to create a representation for an 'ID ISC.ANT.MUX.M4'.
	FunitHfMuxSingle *createHfMuxSingle_1to4(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a HF multiplexer - dual 1 to 4 - with a preconnected HF power splitter
	/// @param[in] parentChannel The output channel of the parent which is connected to the multiplexers input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created multiplexer object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader or a HF multiplexer (single).<br>
	/// Valid output channels of this multiplexer are 1 ... 8. These are paired.<br>
	/// The outputs of a pair will be switched together. The pairing is fixed: 1-8, 2-7, 3-6, 4-5<br>
	/// Use this function to create a representation for an 'ID ISC.ANT.MUX.M8' in dual mode with a
	/// preconnected HF power splitter 'ID ISC.ANT.PSM-B'.
	FunitHfMuxDual *createHfMuxDual_1to4(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a HF power splitter
	/// @param[in] parentChannel The output channel of the parent which is connected to the power splitters input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created power splitter object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader, a HF multiplexer (single or dual) or another HF power splitter.<br>
	/// Valid output channels are 1 and 2.<br>
	/// Use this function to create a representation for an 'ID ISC.ANT.PSM-B'.
	FunitHfPwrSplitter *createHfPwrSplitter(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a HF antenna - dynamic (DAT tuner)
	/// @param[in] parentChannel The output channel of the parent which is connected to the antenna input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created antenna object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader, a HF multiplexer (single or dual) or a HF power splitter.<br>
	/// Use this function to create a representation for an 'ID ISC.DAT' with antenna.
	FunitHfAntDynamic *createHfAntDynamic(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a HF antenna - static
	/// @param[in] parentChannel The output channel of the parent which is connected to the antenna input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created antenna object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader, a HF multiplexer (single or dual) or a HF power splitter.
	FunitHfAntStatic *createHfAntStatic(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a UHF multiplexer - single 1 to 8
	/// @param[in] parentChannel The output channel of the parent which is connected to the multiplexers input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created multiplexer object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader or another UHF multiplexer (single).<br>
	/// Valid output channels of this multiplexer are 1 ... 8.<br>
	/// Use this function to create a representation for an 'ID ISC.ANT.UMUX-A'.
	FunitUhfMuxSingle *createUhfMuxSingle_1to8(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Create a UHF antenna - static
	/// @param[in] parentChannel The output channel of the parent which is connected to the antenna input.
	/// @param[in] parentElement A pointer to the parent function unit or nullptr if parent is the reader.
	/// @return A pointer to the created antenna object. The ExtensionModule keeps ownership of this object.<br>
	/// A nullptr is returned if creation failed. Call lastErrorStatusText() for details.
	///
	/// Valid parents are the reader or an UHF multiplexer (single).
	FunitUhfAntStatic *createUhfAntStatic(size_t parentChannel, FunitElement *parentElement = nullptr);

	/// @brief Destroy all created function unit objects
	void removeAllUnits(void);

	/// @brief Query a first level function unit
	/// @return A pointer to the function unit element, which is connected to the given reader RF output channel<br>
	/// or nullptr if channel is out of range or no FunitElement is connected to the given channel.
	FunitElement *firstParent(size_t channel);

	/// @brief Query all first level function units
	/// @return A vector of all function unit elements, which are conneted to a reader RF output.<br>
	/// In case of an unconnected output the vector contains a nullptr.<br>
	/// The index of the vector is reader RF channel - 1.
	std::vector<FunitElement *> allFirstParents(void);

	/// @brief Query all antenna function units
	/// @return A vector of all antenna function units
	std::vector<FunitElement *> allAntennas(void);

	/// @brief Query all address groups of FunitHfAntDynamic antennas
	/// @return A vector of all FunitHfAntDynamic address groups
	///
	/// This function scans the created function unit element tree for FunitHfAntDynamic antennas.
	/// All antennas within a group are switched on synchronous (For details of antenna address groups see FunitAntDynAddressGroup).<br>
	/// Antennas of a group need individual tuner addresses. The address assignment can be done with performAutoAddressing().
	std::vector<FunitAntDynAddressGroup> allAntDynAddressGroups(void);

	/// @brief Auto address assignment for a antanna group
	/// @param[in] antennaGroup Hold a list of FunitHfAntDynamic antennas. Use allAntDynAddressGroups() for creating the groups.
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This function assigns the antenna tuner addresses. In case of success the addresses are 1...4.
	int performAutoAddressing(FunitAntDynAddressGroup & antennaGroup);
	
	/// @brief Query the readers RF channel count
	/// @return The count of RF outputs or 0 if the reader type does not support function units or the underlying ReaderModule is in unconnected state (i.e. the reader type is not set).
	size_t readerRfChannelCount(void) const;

	/// @brief Activate / deactivate a readers RF output for DC power supply
	/// @param[in] channel The RF output channel number (1 ... readerRfChannelCount). Use DcPowerSupplyAll to set all channels. Use DcPowerSupplyAuto for automatic mode.
	/// @param[in] on If true the appropriate RF output will supply DC power when switched on.
	/// 
	/// The value of parameter 'on' is used internally for each RF on command [6A] when an antenna element is selected.<br>
	/// In case of automatic mode all reader outputs connected directly to a FunitHfAntDynamic will switch DC on. All other outputs will switch DC off.
	int setReaderRfChannelDcPowerSupply(size_t channel = DcPowerSupplyAuto, bool on = false);

	/// @brief Activate / deactivate a readers RF on maintain host mode behaviour
	/// @param[in] on If true maintain host mode is on
	/// 
	/// The value of parameter 'on' is used internally for each RF on command [6A] when an antenna element is selected.
	void setMaintainHostMode(bool on);

	/// @brief Query a summary description of the total function unit equipment
	///
	/// Call this function after all function units are created.<br>
	/// All antennas will be selected sequentially and the firmware version information of all active function units will be read.
	std::string summary(void);

protected:
    Funit();

    Internal::FunitWorker *m_funitWorker; // set by a friend

}; // end of class Funit

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_GROUP_FUNIT_H

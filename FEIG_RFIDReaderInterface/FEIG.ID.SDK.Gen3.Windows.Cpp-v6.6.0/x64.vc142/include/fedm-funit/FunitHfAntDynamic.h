/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_HF_ANTENNA_DYNAMIC_H
#define FEDM_FUNIT_HF_ANTENNA_DYNAMIC_H


#include <FunitElement.h>



namespace FEDM {
namespace FunctionUnit {

class FunitHfAntDynamic;



/// @brief FUNCTION-UNIT element class HF dynamic antenna (DAT tuner)
///
/// This function unit element represents an 'ID ISC.DAT' with antenna.
class FEDM_FUNIT_CLASS_DEF FunitHfAntDynamic : public FunitElement
{
	friend class Internal::FunitWorker;

public:
	std::string typeToString(void) const override;

	/// @brief Define the tuner address for this DAT tuner element
	/// @param[in] tunerAddr The tuner address to be use for access the DAT tuner. Values should be 1 to 4 (Default: 1).
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// After a successful setNewAddress() command this function must be called with the new address.
	void useTunerAddress(size_t tunerAddr) { m_tunerAddr = tunerAddr; }

	size_t tunerAddress(void) const { return m_tunerAddr; }

	/// @brief Get the firmware version of the DAT tuner
	/// @return A reference to the firmware version object
	const FunitFirmwareVersion & firmwareVersion(void) const { return m_fwVersion; }

	/// @brief Select this antenna
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This will set the readers RF output on and select all parent elements recursively.
	int selectAntenna(void);

	/// @brief Perform a CPU reset of the DAT tuner
	/// @return #{DOC_LIB_RETURN_VALUE}
	int resetCpu(void);

	/// @brief Set the tuning capacities of the DAT tuner
	/// @param[in] c1
	/// @param[in] c2
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// For valid capacity values see the documentation of the HF antenna tuner
	int setCapacities(uint32_t c1, uint32_t c2);

	/// @brief Query the antenna values of the DAT tuner
	/// @param[out] values The antenna values
	/// @return #{DOC_LIB_RETURN_VALUE}
	int getAntennaValues(FunitHfAntValues & values);

	/// @brief Set the outputs of the DAT tuner
	/// @param[in] outputs
	/// @return #{DOC_LIB_RETURN_VALUE}
	int setOutputs(uint32_t outputs);

	/// @brief Retune the DAT tuner
	/// @return #{DOC_LIB_RETURN_VALUE}
	int retune(void);

	/// @brief Start tuning of the DAT tuner
	/// @return #{DOC_LIB_RETURN_VALUE}
	int startTuning(void);

	/// @brief Perform a detection of the DAT tuner
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// If successful this function automatically reads the firmware version of the DAT tuner.
	int detect(void);

	/// @brief Store the capacity values to EEPROM
	/// @return #{DOC_LIB_RETURN_VALUE}
	int storeSettings(void);

	/// @brief Set a new DAT tuner address
	/// @param[in] newTunerAddr The new DAT tuner address
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// If successful you must call useAddress() with the new DAT tuner address.
	int changeTunerAddress(size_t newTunerAddr);

	/// @brief Set the operation mode
	/// @param[in] mode The new operation mode
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// See the documentation for details.
	int setMode(int mode);
	
private:
	size_t m_tunerAddr = 1;
	FunitFirmwareVersion  m_fwVersion;

    FunitHfAntDynamic(size_t parentChannel, FunitElement *parent = nullptr);
	~FunitHfAntDynamic();

};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_HF_ANTENNA_DYNAMIC_H

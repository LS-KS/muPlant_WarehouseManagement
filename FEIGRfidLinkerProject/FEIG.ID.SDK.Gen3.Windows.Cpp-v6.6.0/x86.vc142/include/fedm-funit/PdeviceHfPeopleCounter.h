/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_PDEVICE_HF_PEOPLE_COUNTER_H
#define FEDM_PDEVICE_HF_PEOPLE_COUNTER_H

#include <PdeviceElement.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief PERIPHERAL-DEVICE element class HF people counter device
class FEDM_FUNIT_CLASS_DEF PdeviceHfPeopleCounter : public PdeviceElement
{
	friend class Internal::FunitWorker;

public:
    std::string typeToString(void) const override { return "HF-People-Counter"; }

	/// @brief Perform a CPU reset of the people counter device
	/// @return #{DOC_LIB_RETURN_VALUE}
    int resetCpu(void);

    /// @brief Read the firmware information of the people counter device
    /// @param[out] info The firmware information
	/// @return #{DOC_LIB_RETURN_VALUE}
    int readInfo(PdeviceInfo & info);

    /// @brief Read the firmware diagnostic of the people counter device
    /// @param[out] diag The firmware diagnostic
	/// @return #{DOC_LIB_RETURN_VALUE}
    int readDiagnostic(PdeviceHfPcDiag & diag);

    /// @brief Get the current people counter values
    /// @param[out] values The current people counter values
	/// @return #{DOC_LIB_RETURN_VALUE}
    int getCounterValues(PdevicePeopleCounterValues & values);

    /// @brief Set the people counter values
    /// @param[in] values The new people counter values
	/// @return #{DOC_LIB_RETURN_VALUE}
    int setCounterValues(const PdevicePeopleCounterValues & values);

private:
    PdeviceHfPeopleCounter(const PdeviceAddress & address);
    ~PdeviceHfPeopleCounter();

};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_PDEVICE_HF_PEOPLE_COUNTER_H

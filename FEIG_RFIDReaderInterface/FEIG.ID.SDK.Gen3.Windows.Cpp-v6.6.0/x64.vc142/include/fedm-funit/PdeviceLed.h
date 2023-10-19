/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_PDEVICE_LED_H
#define FEDM_PDEVICE_LED_H

#include <PdeviceElement.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief PERIPHERAL-DEVICE element class LED device
class FEDM_FUNIT_CLASS_DEF PdeviceLed : public PdeviceElement
{
	friend class Internal::FunitWorker;

public:
    std::string typeToString(void) const override { return "LED-Device"; }

	/// @brief Perform a CPU reset of the LED device
	/// @return #{DOC_LIB_RETURN_VALUE}
    int resetCpu(void);

    /// @brief Read the firmware information of the LED device
    /// @param[out] info The firmware information
	/// @return #{DOC_LIB_RETURN_VALUE}
    int readInfo(PdeviceInfo & info);

    /// @brief Read the firmware diagnostic of the LED device
    /// @param[out] diag The firmware diagnostic
	/// @return #{DOC_LIB_RETURN_VALUE}
    int readDiagnostic(PdeviceLedDiag & diag);

    /// @brief Set the LED output
    /// @param[in] value The new LED output state
	/// @return #{DOC_LIB_RETURN_VALUE}
    int setOutput(const PdeviceLedOutput & value);

private:
    PdeviceLed(const PdeviceAddress & address);
    ~PdeviceLed();
};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_PDEVICE_LED_H

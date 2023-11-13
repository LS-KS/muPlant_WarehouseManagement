/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_OUTPUT_SETTING_04_H
#define FEDM_OUTPUT_SETTING_04_H

#include "FedmConst.h"
#include "FedmHide.h"



namespace FEDM {



/// @brief DATA class with output setting parameter for a reader (command [0x72], mode [0x04])
class FEDM_CLASS_DEF OutputSetting_04
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
    static const int ModeOff = 0;
    static const int Mode1Hz = 1;
    static const int Mode2Hz = 2;
    static const int Mode4Hz = 4;
    static const int Mode8Hz = 8;
    static const int ModeOn = 0xFF;

	/// @brief Standard constructor
	OutputSetting_04();

    /// @return false if constructed by standard constructor, true if constructed by one of the settingXXX()-function
    bool isValid(void) const { return m_type != TypeNone; }

    /// @brief Create a setting for digital output
    /// @param[in] index The digital output index (see reader manual for details)
    /// @param[in] mode The output action mode
    /// @param[in] holdTime The output hold time in millisec. 0 means infinite.
    static OutputSetting_04 settingDigital(int index, int mode, uint32_t holdTime = 0);

    /// @brief Create a setting for LED output
    /// @param[in] index The LED output index (see reader manual for details)
    /// @param[in] mode The output action mode
    /// @param[in] holdTime The output hold time in millisec. 0 means infinite.
    static OutputSetting_04 settingLed(int index, int mode, uint32_t holdTime = 0); // FIXME: int intensity

    /// @brief Create a setting for relais output
    /// @param[in] index The relais output index (see reader manual for details)
    /// @param[in] mode The output action mode
    /// @param[in] holdTime The output hold time in millisec. 0 means infinite.
    static OutputSetting_04 settingRelais(int index, int mode, uint32_t holdTime = 0);

    /// @brief Create a setting for buzzer output
    /// @param[in] index The buzzer output index (see reader manual for details)
    /// @param[in] mode The output action mode
    /// @param[in] holdTime The output hold time in millisec. 0 means infinite.
    static OutputSetting_04 settingBuzzer(int index, int mode, int intensity, int frequency, uint32_t holdTime = 0);

    /// @brief Create a setting for vibrator output
    /// @param[in] index The vibrator output index (see reader manual for details)
    /// @param[in] mode The output action mode
    /// @param[in] holdTime The output hold time in millisec. 0 means infinite.
    static OutputSetting_04 settingVibrator(int index, int mode, int intensity, uint32_t holdTime = 0);

private:
    static const int TypeNone = 0;
	static const int TypeDigital = 1;
	static const int TypeLed = 2;
	static const int TypeRelais = 3;
	static const int TypeBuzzer = 4;
	static const int TypeVibrator = 5;

    int m_type;
    int m_index;
    int m_mode;
    uint32_t m_holdTime; // msec (0=infinite)
    int m_intensity;
    int m_frequency;
};

}; // end of namespace FEDM

#endif // FEDM_OUTPUT_SETTING_04_H

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_OUTPUT_SETTING_H
#define FEDM_OUTPUT_SETTING_H

#include "FedmConst.h"



namespace FEDM {



/// @brief DATA class with output setting parameter for a reader (command [0x72], modes [0x00] and [0x01])
///
/// See the reader manual for the supported values for outN, outS.<br>
/// See [Set Output](./#/api(content:samples/ReaderCommands.SetOutput)) for a collection of frequently used values
class FEDM_CLASS_DEF OutputSetting
{
	friend class FedmFriend;

public:
	/// @brief Standard constructor
	OutputSetting();

	/// @brief Settings constructor
	/// @param[in] outN The output type parameter (see [Set Output](./#/api(content:samples/ReaderCommands.SetOutput)))
	/// @param[in] outS The output action parameter (see [Set Output](./#/api(content:samples/ReaderCommands.SetOutput)))
	/// @param[in] holdTime The output holdtime. A value of 0xFFFF means continuously active
	OutputSetting(uint8_t outN, uint8_t outS, uint16_t holdTime = 0xFFFF);

	void clear(void);

	void setOutN(uint8_t outN) { m_outN = outN; } ///< outN is the output type parameter (see [Set Output](./#/api(content:samples/ReaderCommands.SetOutput)))
	void setOutS(uint8_t outS) { m_outS = outS; } ///< outS is the output action parameter (see [Set Output](./#/api(content:samples/ReaderCommands.SetOutput)))
	void setHoldTime(uint16_t holdTime) { m_holdTime = holdTime; } ///< holdTime 0xFFFF means continuously active

	uint8_t outN(void) const { return m_outN; }
	uint8_t outS(void) const { return m_outS; }
	uint16_t holdTime(void) const { return m_holdTime; }

private:
	uint8_t  m_outN;
	uint8_t  m_outS;
	uint16_t m_holdTime;
};

}; // end of namespace FEDM

#endif // FEDM_OUTPUT_SETTING_H



/*************************************************************************

There is no warranty for the completeness of the following constants
nor the correctness for all FEIG reader types.
You should have a look to the reader manual (command [0x72]) anyway !


==================
Constants for outN
==================

static const uint8_t Mode0TypeOutput = 0x00;
static const uint8_t Mode0TypeLed    = 0x20;
static const uint8_t Mode0TypeBuzzer = 0x40;

static const uint8_t Mode1TypeOutput   = 0x00;
static const uint8_t Mode1TypeLed      = 0x20;
static const uint8_t Mode1TypeBuzzer   = 0x40;
static const uint8_t Mode1TypeVibrator = 0x60;
static const uint8_t Mode1TypeRelay    = 0x80;
static const uint8_t Mode1TypeLock     = 0xE0;

These values must be OR-ed by the out index/color (0x00 ... 0x0F)


==================
Constants for outS
==================

static const uint8_t Mode0ActionOff       = 0x00;
static const uint8_t Mode0ActionOn        = 0x01;
static const uint8_t Mode0ActionFlashSlow = 0x02;
static const uint8_t Mode0ActionFlashFast = 0x03;

static const uint8_t Mode1ActionOff = 0x02;
static const uint8_t Mode1ActionOn  = 0x01;
static const uint8_t Mode1ActionHz1 = 0x0F;
static const uint8_t Mode1ActionHz2 = 0x0B;
static const uint8_t Mode1ActionHz4 = 0x07;
static const uint8_t Mode1ActionHz8 = 0x03;

****************************************************************************/

/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_PDEVICE_ELEMENT_H
#define FEDM_PDEVICE_ELEMENT_H

/*
#include <string>

#include <FedmFunitBase.h>
#include <FedmFunitHide.h>
*/
#include <PdeviceData.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief PERIPHERAL-DEVICE element base class
class FEDM_FUNIT_CLASS_DEF PdeviceElement
{
	friend class Internal::FunitWorker;

public:
	// These values are identical to ReaderInfo::PeriphAddr::Type...
	static const int TypeNone = 0;
    static const int TypeHfPeopleCounter = 1;
    static const int TypeLed = 3;
//  static const int TypeExternalIO = 2;
//  static const int TypeUhfPeopleCounter = 4;
	
	/// @brief Get the type of the peripheral device
	/// @return The type constant of this peripheral device element
	int type(void) const { return m_type; }

	/// @brief Get a string description of the peripheral device type
	/// @return A string description of the peripheral device type.
	virtual std::string typeToString(void) const { return "Peripheral-Device"; }

	/// @brief Get the address of the peripheral device
	/// @return The address of this peripheral device element
	const PdeviceAddress & address(void) const { return m_address; }
	
protected:
	// Piggypack device types
	static const int DeviceNone = 0;
	static const int DeviceHfPeopleCounter = PdeviceInfo::SwTypeHfPeopleCounter;
	static const int DeviceLed = PdeviceInfo::SwTypeLed;

	Internal::FunitWorker *m_funitWorker;

	int m_type = TypeNone;
	int m_device = DeviceNone;
	PdeviceAddress m_address;

    PdeviceElement(const PdeviceAddress & address);
    virtual ~PdeviceElement();

	int setLastError(int error);
	void setPiggypackParam(void);
};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_PDEVICE_ELEMENT_H

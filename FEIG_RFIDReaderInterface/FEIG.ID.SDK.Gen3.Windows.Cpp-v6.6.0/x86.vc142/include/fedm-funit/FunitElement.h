/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_ELEMENT_H
#define FEDM_FUNIT_ELEMENT_H

#include <FunitData.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief FUNCTION-UNIT element base class
class FEDM_FUNIT_CLASS_DEF FunitElement
{
	friend class Internal::FunitWorker;

public:
	static const int TypeNone = 0;
	static const int TypeHfMuxSingle = 1;
	static const int TypeHfMuxDual = 2;
	static const int TypeHfPwrSplitter = 3;
	static const int TypeHfAntDynamic = 4; // Antenna with DAT-tuner
	static const int TypeHfAntStatic = 5;
	static const int TypeUhfMuxSingle = 10;
	static const int TypeUhfAntStatic = 11;

	static const size_t UnknownChannel = -1;
	
	/// @brief Get the type of the function unit
	/// @return The type constant of this function unit element
	int type(void) const { return m_type; }

	/// @brief Get a string description of the function unit type
	/// @return A string description of the function unit type. Example: HF-Mux-Single-1to8
	virtual std::string typeToString(void) const { return "Function-Unit"; }
	
	/// @brief Query the address path to this function unit
	/// @return An object which holds the address path information of this function unit
	FunitAddress address(void) const;

	/// @brief Query the parents element path list
	/// @return A vector of parent elements. The first element (index 0) is the function unit connected to readers RF output.
	/// The last element is this function unit.
	std::vector<FunitElement *> elementPath(void);
	
	/// @brief Get the parents output channel where this element is connected to.
	/// @return The output channel of the parent element.<br>
	/// If parentElement() returns nullptr this is the readers antenna output.
	size_t parentChannel(void) const { return m_parentChannel; }

	/// @brief Get the parent of this function unit
	/// @return A pointer to the parent element.<br>
	/// If parent is the reader nullptr is returned. In that case parentChannel() returns the readers antenna output.
	FunitElement *parentElement(void) const { return m_parentElement; }

	void *applicationData(void) const { return m_applicationData; }

	void setApplicationData(void *applicationData) { m_applicationData = applicationData; }
	
protected:
	Internal::FunitWorker *m_funitWorker;

	int           m_type = TypeNone;
	size_t        m_parentChannel = UnknownChannel; // from 1..
	FunitElement *m_parentElement = nullptr;

	void *m_applicationData = nullptr;

	FunitElement(size_t parentChannel, FunitElement *parentElement = nullptr);
	virtual ~FunitElement();

	int setLastError(int error);
};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_ELEMENT_H

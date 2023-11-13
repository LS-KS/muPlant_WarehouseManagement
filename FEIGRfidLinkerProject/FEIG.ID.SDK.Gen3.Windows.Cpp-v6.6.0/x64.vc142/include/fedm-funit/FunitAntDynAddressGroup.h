/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_ANT_DYN_ADDR_GROUP_H
#define FEDM_FUNIT_ANT_DYN_ADDR_GROUP_H

#include <vector>

#include <FedmFunitElements.h>



namespace FEDM {
namespace FunctionUnit {



/// @brief DATA class for antenna tuner address groups.
///
/// All antennas within a group are switched on synchronous. The following groups can be detected:<br>
/// - The trivial case: A single antenna connected at a reader or multiplexer output.<br>
/// - Two antennas connected at power splitter outputs.<br>
/// - Two antennas connected at one output pair of a dual multiplexer.<br>
/// - A very special case: Four antennas connected with three cascated power splitter.<br>
///
/// Tuner address groups are created by function Funit::allAntDynAddressGroups().<br>
/// They are used by the function Funit::performAutoAddressing().
class FEDM_FUNIT_CLASS_DEF FunitAntDynAddressGroup
{
	friend class Internal::FunitWorker;

public:
    FunitAntDynAddressGroup();

	void clear(void);

    /// @return True if rootElement exists and the antenna count is 1, 2 or 4 and all FunitElement's are not nullptr
	bool isValid(void) const;

    FunitElement *rootElement(void) const { return m_rootElement; }

    /// @return In case of a isValid() is true 1, 2 or 4 is returned.
    size_t antennaCount(void) const { return m_antennas.size(); }

    FunitHfAntDynamic *operator[](size_t index) const { return m_antennas[index]; }
    FunitHfAntDynamic *antenna(size_t index) const    { return m_antennas.at(index); }

    std::string groupToString(void) const;
    std::string antennaToString(size_t index) const;
	
private:
    FunitElement *m_rootElement = nullptr;
    std::vector<FunitHfAntDynamic *> m_antennas;

    FunitAntDynAddressGroup(FunitHfAntDynamic *ant); // here: root = ant
    FunitAntDynAddressGroup(FunitElement *root, FunitHfAntDynamic *ant1, FunitHfAntDynamic *ant2);
    FunitAntDynAddressGroup(FunitElement *root, FunitHfAntDynamic *ant1, FunitHfAntDynamic *ant2, FunitHfAntDynamic *ant3, FunitHfAntDynamic *ant4);

    static void addToAddressPath(std::string & path, const FunitElement *level); // recursive
    static std::string elementTypeToString(int type);
};



}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_ANT_DYN_ADDR_GROUP_H

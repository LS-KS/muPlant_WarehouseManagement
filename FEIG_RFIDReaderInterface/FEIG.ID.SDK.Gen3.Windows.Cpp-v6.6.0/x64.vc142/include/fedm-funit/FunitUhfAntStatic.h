/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_UHF_ANTENNA_STATIC_H
#define FEDM_FUNIT_UHF_ANTENNA_STATIC_H


#include <FunitElement.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief FUNCTION-UNIT element class UHF static antenna
///
/// A static antenna cannot be tunned
class FEDM_FUNIT_CLASS_DEF FunitUhfAntStatic : public FunitElement
{
	friend class Internal::FunitWorker;

public:
	std::string typeToString(void) const override;

	/// @brief Select this antenna
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This will set the readers RF output on and select all parent elements recursively.
	int selectAntenna(void);
	
private:
	FunitUhfAntStatic(size_t parentChannel, FunitElement *parent = nullptr);
	~FunitUhfAntStatic();

};

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_UHF_ANTENNA_STATIC_H

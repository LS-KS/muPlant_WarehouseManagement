/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_NOISE_LEVEL_H
#define FEDM_NOISE_LEVEL_H

#include "FedmConst.h"
#include "FedmHide.h"

namespace FEDM {

/// @brief DATA class with noise level information of a reader
class FEDM_CLASS_DEF NoiseLevel
{
	friend class Internal::ReaderBase;
	friend class FedmFriend;

public:
	NoiseLevel();
	~NoiseLevel();

	/// set to defaults
	void clear(void);

	uint32_t avgNoiseLevel() const {
		return m_avgNoiseLevel;
	}

	uint32_t maxNoiseLevel() const {
		return m_maxNoiseLevel;
	}

	uint32_t minNoiseLevel() const {
		return m_minNoiseLevel;
	}

private:
	uint32_t m_minNoiseLevel;
	uint32_t m_avgNoiseLevel;
	uint32_t m_maxNoiseLevel;

}; // end of class NoiseLevel

}; // end of namespace FEDM

#endif // FEDM_NOISE_LEVEL_H

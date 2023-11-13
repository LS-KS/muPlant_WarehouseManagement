/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_BUFFER_INFO_H
#define FEDM_BUFFER_INFO_H

#include "FedmConst.h"
#include "FedmHide.h"

namespace FEDM
{

/// @brief DATA ckass with state values of the readers internal tag event buffer
class FEDM_CLASS_DEF BufferInfo
{
	friend class Payload::PlBase;
	friend class FedmFriend;

public:
	BufferInfo();

	void clear();

	/// @brief First valid entry in the buffer
	size_t firstTag() const	{
		return m_firstTag;
	}

	/// @brief Size of reader's event buffer, i.e. maximum number of tag event entries
	size_t maxTags() const {
		return m_maxTags;
	}

	/// @brief Avaliable number of tag event entries
	size_t numTags() const {
		return m_numTags;
	}

private:
	size_t m_maxTags;
	size_t m_firstTag;
	size_t m_numTags;

}; // end of class BufferInfo

}; // end of namespace FEDM

#endif // FEDM_BUFFER_INFO_H

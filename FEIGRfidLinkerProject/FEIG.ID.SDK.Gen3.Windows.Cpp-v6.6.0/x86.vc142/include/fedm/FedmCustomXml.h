/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_CUSTOM_XML_H
#define FEDM_CUSTOM_XML_H

#include <string>


namespace FEDM {


/// @brief DATA class with additional application information for a configuration XML file
class FEDM_CLASS_DEF CustomXmlData {
	friend class FedmFriend;

public:
	CustomXmlData() {
	}

	CustomXmlData(const std::string & programName, const std::string & programVersion, const std::string & comment) {
		m_programName = programName;
		m_programVersion = programVersion;
		m_comment = comment;
	}

	const std::string & programName() const {
		return m_programName;
	};

	const std::string & programVersion() const {
		return m_programVersion;
	};

	const std::string & comment() const {
		return m_comment;
	};

	void setProgramName(const std::string & programName) {
		m_programName = programName;
	}

	void setProgramVersion(const std::string & programVersion) {
		m_programVersion = programVersion;
	}

	void setComment(const std::string & comment) {
		m_comment = comment;
	}

private:
	std::string m_programName;
	std::string m_programVersion;
	std::string m_comment;
};

} // end of namespace FEDM

#endif /* FEDM_CUSTOM_XML_H */

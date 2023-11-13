/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_GROUP_CONFIG_H
#define FEDM_GROUP_CONFIG_H

#include "FedmBasic.h"
#include "FedmHide.h"
#include "ReaderConfigPara.h"



namespace FEDM {

/// @brief GROUP class for reader configuration
///
/// To operate on a readers configuration an initial call to readCompleteConfiguration() is required.<br>
/// Now configuration parameter of ReaderModule's internal config memory can be queried or manipulated.<br>
/// Finally changes can be written back to the reader with writeCompleteConfiguration() or applyConfiguration().<br>
/// To change one parameter and send it to the reader imediatly call one of the changeConfigPara() functions.<br>
/// Use the high level functions to operate with whole reader configurations.
class FEDM_CLASS_DEF Config
{
	friend class ReaderModule;
	
public:
	/// @brief Check if a config parameter is applicable with the connected Reader
	/// @param[in] param A string with parameter name.<br>
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[out] paramInfo Physical information of the parameter
	/// @return true if parameter is applicable, false otherwise
	bool hasConfigPara(const std::string & param, ConfigParamInfo & paramInfo) const;


/** @name Query config parameter from ReaderModule's internal config memory
 */
///@{
	/// @brief Get boolean config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[out] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return #{DOC_LIB_ERROR_VALUE}
	int getConfigPara(const std::string & param, bool & data, bool persistent = true) const;

	/// @brief Get uint8_t config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[out] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return #{DOC_LIB_ERROR_VALUE}
	int getConfigPara(const std::string & param, uint8_t & data, bool persistent = true) const;

	/// @brief Get uint32_t config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[out] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return #{DOC_LIB_ERROR_VALUE}
	int getConfigPara(const std::string & param, uint32_t & data, bool persistent = true) const;

	/// @brief Get byte array config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[out] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return #{DOC_LIB_ERROR_VALUE}
	int getConfigPara(const std::string & param, std::vector<uint8_t> & data, bool persistent = true) const;

	/// @brief Get hex coded string config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[out] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return #{DOC_LIB_ERROR_VALUE}
	int getConfigPara(const std::string & param, std::string & data, bool persistent = true) const;
///@}
	

/** @name Change config parameter of ReaderModule's internal config memory
 */
///@{
	/// @brief Set boolean config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	int setConfigPara(const std::string & param, bool data, bool persistent = true);

	/// @brief Set uint8_t config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	int setConfigPara(const std::string & param, uint8_t data, bool persistent = true);

	/// @brief Set uint32_t config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	int setConfigPara(const std::string & param, uint32_t data, bool persistent = true);

	/// @brief Set byte array config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	int setConfigPara(const std::string & param, const std::vector<uint8_t> & data, bool persistent = true);

	/// @brief Set hex coded string config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	int setConfigPara(const std::string & param, const std::string & data, bool persistent = true);
///@}
	

/** @name Change config parameter of ReaderModule's internal config memory and write it into the reader
 */
///@{
	/// @brief Set boolean config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	/// - \> 1	reader status of the responded protocol, if the Reader signals a problem (see DOC_LINK_TO_CLASS(FEDM::ReaderStatus))
	int changeConfigPara(const std::string & param, bool data, bool persistent = true);

	/// @brief Set uint8_t config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	/// - \> 1	reader status of the responded protocol, if the Reader signals a problem (see DOC_LINK_TO_CLASS(FEDM::ReaderStatus))
	int changeConfigPara(const std::string & param, uint8_t data, bool persistent = true);

	/// @brief Set uint32_t config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	/// - \> 1	reader status of the responded protocol, if the Reader signals a problem (see DOC_LINK_TO_CLASS(FEDM::ReaderStatus))
	int changeConfigPara(const std::string & param, uint32_t data, bool persistent = true);

	/// @brief Set byte array config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	/// - \> 1	reader status of the responded protocol, if the Reader signals a problem (see DOC_LINK_TO_CLASS(FEDM::ReaderStatus))
	int changeConfigPara(const std::string & param, const std::vector<uint8_t> & data, bool persistent = true);

	/// @brief Set hex coded string config parameter
	/// @param[in] param A string with parameter name.
	/// The parameter name is one of the namespace FEDM::ReaderConfig and must be applicable with the connected Reader
	/// @param[in] data The parameter value
	/// @param[in] persistent If true, the parameter is stored persistent in the EEPROM
	/// @return
	/// - 0: OK and value not modified
	/// - 1: OK and value modified
	/// - \<0: #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	/// - \> 1	reader status of the responded protocol, if the Reader signals a problem (see DOC_LINK_TO_CLASS(FEDM::ReaderStatus))
	int changeConfigPara(const std::string & param, const std::string & data, bool persistent = true);
///@}


/** @name Read, write, reset reader configuration
 */
///@{
	/// @brief Reads complete configuration from Reader to ReaderModule's internal config memeory
	/// @param[in] persistent If true, parameters are read from EEPROM, otherwise from RAM
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readCompleteConfiguration(bool persistent = true);

	/// @brief Reads one configuration page from Reader
	/// @param[in] page The page index
	/// @param[in] persistent If true, parameters are read from EEPROM, otherwise from RAM
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readConfigurationPage(size_t page, bool persistent = true);

	/// @brief Writes complete configuration of ReaderModule's internal config memeory into the Reader
	/// @param[in] persistent If true, parameters are written into EEPROM, otherwise into RAM
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeCompleteConfiguration(bool persistent = true);

	/// @brief Writes one configuration page from Reader
	/// @param[in] page The page index
	/// @param[in] persistent If true, parameters are read from EEPROM, otherwise from RAM
	/// @return #{DOC_LIB_RETURN_VALUE}
	int writeConfigurationPage(size_t page, bool persistent = true);

	/// @brief Applies configuration changes of ReaderModule's internal config memeory into the Reader
	/// @param[in] persistent If true, parameters are written into RAM and EEPROM, otherwise only into RAM
	/// @return
	/// - 0	if nothing to be applied to
	///	- 1	if at least one page is successfully written
	/// - \< 0 error code (see DOC_LINK_TO_CLASS(FEDM::ErrorCode))
	/// - \> 1	reader status of the responded protocol, if the Reader signals a problem (see DOC_LINK_TO_CLASS(FEDM::ReaderStatus))
	int applyConfiguration(bool persistent = true);

	/// @brief Resets readers complete configuration to factory default
	/// @param[in] persistent If true, the EEPROM configuration is reset, otherwise the RAM configuration
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This function does not change ReaderModule's internal config memeory
	int resetCompleteConfiguration(bool persistent = true);

	/// @brief Resets one configuration page to factory default
	/// @param[in] page The page index
	/// @param[in] persistent If true, parameters are read from EEPROM, otherwise from RAM
	/// @return #{DOC_LIB_RETURN_VALUE}
	int resetConfigurationPage(size_t page, bool persistent = true);
///@}


/** @name Login to reader's configuration
 */
///@{
	/// @brief A login for access to the Reader's configuration is executed with the [0xA0] Reader Login command.
	/// @param[in] password A 8 sign hex coded string password (4 raw byte length)
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readerLogin(const std::string & password);


	/// @brief A login for access to the Reader's configuration is executed with the [0xA1] Reader Login command.
	/// @param[in] username An ASCII string (max. 16 signs)
	/// @param[in] password An ASCII string (max. 16 signs)
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readerLogin(const std::string & username, const std::string & password);
///@}



/** @name High level configuration functions
 */
///@{
	/// @brief Write complete reader configuration to XML file
	/// @param[in] fileName Name of the XML file
	/// @param[in] customXmlData Custumer application data added to the file
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// This function writes the config data of ReaderModule's internal config memeory to a XML file.<br>
	/// Prior to this the reader's configuration must be read with readCompleteConfiguration().
	int serializeToFile(const std::string & fileName, const CustomXmlData & customXmlData);

	/// @brief Read complete reader configuration from XML file
	/// @param[in] fileName Name of the XML file
	/// @param[out] customXmlData Custumer application data from the file
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// This function reads a XML file into ReaderModule's internal config memeory.<br>
	/// Next you can write that content to the reader with writeCompleteConfiguration().
	int deserializeFromFile(const std::string & fileName, CustomXmlData & customXmlData);
	
	/// @brief Direct configuration transfer from file to reader
	/// @param[in] fileName Name of the profile file
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This function calls deserializeFromFile() and writeCompleteConfiguration().
	int transferXmlFileToReaderCfg(const std::string & fileName);

	/// @brief Direct configuration transfer from reader to file
	/// @param[in] fileName Name of the profile file
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This function calls readCompleteConfiguration() and serializeToFile().
	int transferReaderCfgToXmlFile(const std::string & fileName, const CustomXmlData & customXmlData = CustomXmlData());
///@}
	
protected:
	Config();
	~Config();
	
	Internal::ReaderBase  *m_rdrBase; // set by a friend

	int writeCfgPageOfParam(const std::string & param, bool persistent);

	static bool isParamAll(const std::string & param) { return param == "All"; }
};

}; // end of namespace FEDM

#endif // FEDM_GROUP_CONFIG_H

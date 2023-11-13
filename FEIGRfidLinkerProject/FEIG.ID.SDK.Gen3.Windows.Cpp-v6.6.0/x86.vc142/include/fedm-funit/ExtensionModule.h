/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_MODULE_H
#define FEDM_FUNIT_MODULE_H

#include <Fedm.h>
#include <FedmFunitBasic.h>
#include <FedmFunitElements.h>
#include <FedmFunitHide.h>
#include <GroupFunit.h>
#include <GroupPdevice.h>



namespace FEDM {
namespace FunctionUnit {

/// @brief MAIN class for function unit and peripheral device extensions of a ReaderModule
class FEDM_FUNIT_CLASS_DEF ExtensionModule
{
public:
/** @name Main
 */
///@{
	/// @brief Constructor for the function unit module
	/// @param[in] reader A pointer to a ReaderModule
	///
	/// The function unit module does not take ownership of the reader module.<br>
	/// The function unit module must be destroyed before reader module's destructor is called !<br>
	/// The reader module must hold the reader information (reader type) before calling this constructor!
	ExtensionModule(ReaderModule *reader);

	/// @brief The standard constructor is not allowed
	ExtensionModule() = delete;

	/// @brief To copy a ExtensionModule is not allowed
	ExtensionModule(ExtensionModule & other) = delete;

	/// @brief To copy a ExtensionModule is not allowed
	ExtensionModule(const ExtensionModule & other) = delete;

	/// @brief To copy a ExtensionModule is not allowed
	ExtensionModule & operator=(ExtensionModule & other) = delete;

	/// @brief To copy a ExtensionModule is not allowed
	ExtensionModule & operator=(const ExtensionModule & other) = delete;

	~ExtensionModule();

	/// @brief Query the version the fedm-funit library
	static std::string libVersion(void);
///@}



// ############################################################# Error Handling #############################################################
/** @name Error Handling
 */
///@{
	/// @brief Get last library error code
	/// @return The last library error code
	///
	/// If the last library function call delivered a negative return code this function will return this value.<br>
	/// Otherwise 0 will be returned.
	int lastError(void) const;

	/// @brief Get status code of last reader response
	/// @return The last reader status #{DOC_LINK_TO_CLASS(FEDM::ReaderStatus)}
	///
	/// If the last library function call delivered a positive return code this function will return the LSB of that.
	int lastReaderStatus(void) const;

	/// @brief Get status code of last function unit response
	/// @return The last function unit status #{DOC_LINK_TO_CLASS(FEDM::ReaderStatus)}
	///
	/// If the last library function call delivered a positive return code this function will return the 2nd LSB of that.
	int lastFunctionUnitStatus(void) const;

	/// @brief Get last error or status text
	/// @return The text of last library error, reader status or function unit status
	std::string lastErrorStatusText(void) const;
///@}


// ####################################################### Extension Function Groups #######################################################
/** @name Extension Function Groups Non-Const
 */
///@{
	Funit   & funit  (void) { return m_funit; }
	Pdevice & pdevice(void) { return m_pdevice; }
///@}

/** @name Extension Function Groups Const
 */
///@{
	const Funit   & funit  (void) const { return m_funit; }
	const Pdevice & pdevice(void) const { return m_pdevice; }
///@}


private:
	Internal::FunitWorker *m_funitWorker;

	Funit   m_funit;
	Pdevice m_pdevice;

}; // end of class ExtensionModule

}; // end of namespace FunctionUnit
}; // end of namespace FEDM

#endif // FEDM_FUNIT_MODULE_H

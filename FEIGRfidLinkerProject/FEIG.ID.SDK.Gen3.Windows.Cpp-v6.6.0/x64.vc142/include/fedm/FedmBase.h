/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_BASE_H
#define FEDM_BASE_H


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// !!! NO FURTHER INCLUDES ARE ALLOWED IN THIS FILE !!!
// Don't put C++ stuff here



#if (defined(_WIN32) || defined(_WIN64))
/***** WINDOWS *****/

#ifdef FEDMDLL // Windows-DLL

#define FEDM_CLASS_DEF __declspec(dllexport)
#define FEDM_CALL_DEF(type) __declspec(dllexport) type __cdecl
#define FEDM_EXT_CALL __cdecl

#else // Windows-APP
	
#define FEDM_CLASS_DEF __declspec(dllimport)
#define FEDM_CALL_DEF(type) __declspec(dllimport) type __cdecl
#define FEDM_EXT_CALL __cdecl

#endif // end of WINDOWS


#else
/***** ALL OTHER PLATFORMS *****/

#define FEDM_CLASS_DEF
#define FEDM_CALL_DEF(type) type
#define FEDM_EXT_CALL

#endif // end of LINUX

#define FEDM_INTERNAL_CLASS_DEF FEDM_CLASS_DEF

#define FEDM_VERSION_MAJOR 6
#define FEDM_VERSION_MINOR 6
#define FEDM_VERSION_DEVEL 0
#define FEDM_VERSION_REVISION ""

// Set the following macro to '1' in case the revision should be included in the VERSION_STRING
#define FEDM_VERSION_REVISION_INCLUDE 0


#define STRING_QUOTE(name) #name
#define STRING_VALUE(macro) STRING_QUOTE(macro)

#ifndef __CMAKE_ARCHITECTURE
#define __CMAKE_ARCHITECTURE ""
#endif

#if FEDM_VERSION_REVISION_INCLUDE == 0
#define FEDM_VERSION_STRING    STRING_VALUE(FEDM_VERSION_MAJOR) "." STRING_VALUE(FEDM_VERSION_MINOR) "." STRING_VALUE(FEDM_VERSION_DEVEL) "  " __CMAKE_ARCHITECTURE
#else
#define FEDM_VERSION_STRING    STRING_VALUE(FEDM_VERSION_MAJOR) "." STRING_VALUE(FEDM_VERSION_MINOR) "." STRING_VALUE(FEDM_VERSION_DEVEL) "-" FEDM_VERSION_REVISION "  " __CMAKE_ARCHITECTURE
#endif


#endif // FEDM_BASE_H



/*
Documentation Macros:

/// #{DOC_LINK_TO_CLASS(classname)}
	[???]{classname}

/// #{DOC_LIB_RETURN_VALUE}
	/// -   0 if OK
	/// - \< 0 Error code (see #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)})
	/// - \> 0 Reader status of the responded protocol, if the Reader signals a problem (see #{DOC_LINK_TO_CLASS(FEDM::ReaderStatus)})

/// #{DOC_LIB_ERROR_VALUE}
	/// -   0 If OK
	/// - \< 0 Error code (see #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)})

*/

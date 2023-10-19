/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FUNIT_BASE_H
#define FEDM_FUNIT_BASE_H



#if (defined(_WIN32) || defined(_WIN64))
/***** WINDOWS *****/

#ifdef FEDMFUNITDLL // Windows-DLL

#define FEDM_FUNIT_CLASS_DEF __declspec(dllexport)
#define FEDM_FUNIT_CALL_DEF(type) __declspec(dllexport) type __cdecl
#define FEDM_FUNIT_EXT_CALL __cdecl


#else // Windows-APP

#define FEDM_FUNIT_CLASS_DEF __declspec(dllimport)
#define FEDM_FUNIT_CALL_DEF(type) __declspec(dllimport) type __cdecl
#define FEDM_FUNIT_EXT_CALL __cdecl

#endif // end of WINDOWS


#else
/***** ALL OTHER PLATFORMS *****/

#define FEDM_FUNIT_CLASS_DEF
#define FEDM_FUNIT_CALL_DEF(type) type
#define FEDM_FUNIT_EXT_CALL

#endif // end of LINUX



/***** VERSION *****/

#define FEDM_FUNIT_VERSION_MAJOR 1
#define FEDM_FUNIT_VERSION_MINOR 1
#define FEDM_FUNIT_VERSION_DEVEL 0
#define FEDM_FUNIT_VERSION_REVISION ""



#define STRING_QUOTE(name) #name
#define STRING_VALUE(macro) STRING_QUOTE(macro)

#ifndef __CMAKE_ARCHITECTURE
#define __CMAKE_ARCHITECTURE ""
#endif

#define FEDM_FUNIT_VERSION_STRING    STRING_VALUE(FEDM_FUNIT_VERSION_MAJOR) "." STRING_VALUE(FEDM_FUNIT_VERSION_MINOR) "." STRING_VALUE(FEDM_FUNIT_VERSION_DEVEL) "-" FEDM_FUNIT_VERSION_REVISION "  " __CMAKE_ARCHITECTURE



#endif // FEDM_FUNIT_BASE_H



/*
Documentation Macros:

/// #{DOC_LINK_TO_CLASS(classname)}
	[???]{classname}

/// #{DOC_LIB_RETURN_VALUE}
	/// -   0 if OK
	/// - \< 0 Error code (see #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)})
	/// - \> 0 Reader status of the responded protocol, if the reader signals a problem (LSB) or
    ///      function unit status, if the function unit signals a problem (2nd LSB).
    ///      See #{DOC_LINK_TO_CLASS(FEDM::ReaderStatus)} and #{DOC_LINK_TO_CLASS(FEDM::ExtensionModule)} functions lastReaderStatus() and lastFunctionUnitStatus().

/// #{DOC_LIB_ERROR_VALUE}
	/// -   0 If OK
	/// - \< 0 Error code (see #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)})

*/

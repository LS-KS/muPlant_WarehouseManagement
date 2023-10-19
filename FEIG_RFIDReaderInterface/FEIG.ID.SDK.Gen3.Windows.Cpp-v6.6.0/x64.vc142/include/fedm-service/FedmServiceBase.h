/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_SERVICE_BASE_H
#define FEDM_SERVICE_BASE_H



#if (defined(_WIN32) || defined(_WIN64))
/***** WINDOWS *****/

#ifdef FEDMSERVICEDLL // Windows-DLL

#define FEDM_SERVICE_CLASS_DEF __declspec(dllexport)
#define FEDM_SERVICE_CALL_DEF(type) __declspec(dllexport) type __cdecl
#define FEDM_SERVICE_EXT_CALL __cdecl


#else // Windows-APP

#define FEDM_SERVICE_CLASS_DEF __declspec(dllimport)
#define FEDM_SERVICE_CALL_DEF(type) __declspec(dllimport) type __cdecl
#define FEDM_SERVICE_EXT_CALL __cdecl

#endif // end of WINDOWS


#else
/***** ALL OTHER PLATFORMS *****/

#define FEDM_SERVICE_CLASS_DEF
#define FEDM_SERVICE_CALL_DEF(type) type
#define FEDM_SERVICE_EXT_CALL

#endif // end of LINUX



/***** VERSION *****/

#define FEDM_SERVICE_VERSION_MAJOR 10
#define FEDM_SERVICE_VERSION_MINOR 2
#define FEDM_SERVICE_VERSION_DEVEL 0
#define FEDM_SERVICE_VERSION_REVISION ""



#define STRING_QUOTE(name) #name
#define STRING_VALUE(macro) STRING_QUOTE(macro)

#ifndef __CMAKE_ARCHITECTURE
#define __CMAKE_ARCHITECTURE ""
#endif

#define FEDM_SERVICE_VERSION_STRING    STRING_VALUE(FEDM_SERVICE_VERSION_MAJOR) "." STRING_VALUE(FEDM_SERVICE_VERSION_MINOR) "." STRING_VALUE(FEDM_SERVICE_VERSION_DEVEL) "-" FEDM_SERVICE_VERSION_REVISION "  " __CMAKE_ARCHITECTURE



#endif // FEDM_SERVICE_BASE_H

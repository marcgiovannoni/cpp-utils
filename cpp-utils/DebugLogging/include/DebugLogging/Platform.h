/*
 *  Platform.h
 *
 *  Created by Marc Giovannoni on 03/05/2016
 */

#ifndef     __PLATFORM_H__
#define     __PLATFORM_H__

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef _MSC_VER
#define MSVC_C4127_DISABLE __pragma(warning(push)) __pragma(warning(disable:4127))
#define MSVC_C4127_RESTORE __pragma(warning(pop))
#else
#define MSVC_C4127_DISABLE
#define MSVC_C4127_RESTORE
#endif

#endif  //  __PLATFORM_H__

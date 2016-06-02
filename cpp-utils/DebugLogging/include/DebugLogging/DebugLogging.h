/*
 *  DebugLogging.h
 *
 *  Created by Marc Giovannoni on 19/04/2016
 */

#ifndef     __DEBUGLOGGING_H__
#define     __DEBUGLOGGING_H__

//
// System includes
//

#include <cstdarg>
#include <string>

//
// Project includes
//

#include "Platform.h"

#define MACRO_BEGIN_BLOCK if MSVC_C4127_DISABLE (1 == 1) MSVC_C4127_RESTORE {
#define MACRO_END_BLOCK } else (void)0

namespace DebugLogging
{
    enum LogLevel
    {
        llFatal,
        llError,
        llWarning,
        llInfo,
        llDebug,
        llPerformance
    };

    void logMessageV(LogLevel logLevel, const char *scope, const char *fileName, int lineNumber, const char *message, va_list args);
    void logMessage(LogLevel logLevel, const char *scope, const char *fileName, int lineNumber, const char *message, ...);
}

#define LOG_MESSAGE_DISABLED(logLevel, scope, message, ...) MACRO_BEGIN_BLOCK MACRO_END_BLOCK

#ifdef _MSC_VER

#define LOG_MESSAGE(logLevel, scope, message, ...) DebugLogging::logMessage(DebugLogging::ll##logLevel, #scope, __FILE__, __LINE__, message, __VA_ARGS__)

#define LOG_FATAL(scope, message, ...) LOG_MESSAGE(Fatal, scope, message, __VA_ARGS__)
#define LOG_ERROR(scope, message, ...) LOG_MESSAGE(Error, scope, message, __VA_ARGS__)
#define LOG_WARNING(scope, message, ...) LOG_MESSAGE(Warning, scope, message, __VA_ARGS__)
#define LOG_INFO(scope, message, ...) LOG_MESSAGE(Info, scope, message, __VA_ARGS__)
#define LOG_PERFORMANCE(scope, message, ...) LOG_MESSAGE(Performance, scope, message, __VA_ARGS__)

#ifndef NDEBUG
#define LOG_DEBUG(scope, message, ...) LOG_MESSAGE(Debug, scope, message, __VA_ARGS__)
#else // NDEBUG
#define LOG_DEBUG(scope, message, ...) LOG_MESSAGE_DISABLED(Debug, scope, message, __VA_ARGS__)
#endif // NDEBUG

#endif  // _MSC_VER

#endif  //  __DEBUGLOGGING_H__

/*
 *  DebugLogging.cpp
 *  
 *  Created by Marc Giovannoni on 19/04/2016
 */

#include "DebugLogging/DebugLogging.h"

using namespace DebugLogging;

#ifdef _WIN32

#include <codecvt>

void DebugLogging::logMessageV(LogLevel logLevel, const char *scope, const char *fileName, int lineNumber, const char *message, va_list args)
{
    static const char LOG_LEVEL_TLAS[7][3] = {
        { 'F', 'T', 'L' },
        { 'E', 'R', 'R' },
        { 'W', 'R', 'N' },
        { 'I', 'N', 'F' },
        { 'D', 'B', 'G' },
        { 'P', 'F', 'M' },
        { '?', '?', '?' } };

    unsigned int messageIndex = ((static_cast<int>(logLevel) < 0) || (static_cast<int>(logLevel) > 6)) ?
        6 :
        static_cast<unsigned int>(logLevel);

    const char *logLevelTLA = LOG_LEVEL_TLAS[messageIndex];

    // Message prefix is: filename + "(" + line number + "): [" + TLA + "] " + scope + ": "
    int prefixSize = _scprintf("%s(%d): [%c%c%c] %s: ", fileName, lineNumber, logLevelTLA[0], logLevelTLA[1], logLevelTLA[2], scope);
    int messageSize = _vscprintf(message, args);
    int totalSize = prefixSize + messageSize;
    int bufferSize = totalSize + 3;
    char *messageBuffer = new char[bufferSize];

    int prefixWritten = _snprintf(messageBuffer, bufferSize, "%s(%d): [%c%c%c] %s: ", fileName, lineNumber, logLevelTLA[0], logLevelTLA[1], logLevelTLA[2], scope);
    int messageWritten = _vsnprintf(messageBuffer + prefixSize, bufferSize - prefixSize, message, args);
    if ((prefixWritten != prefixSize) || (messageWritten != messageSize) || (messageBuffer[totalSize] != 0))
    {
        // Printed a different number of characters than expected.
        delete[] messageBuffer;
        return;
    }

    printf("%s\n", messageBuffer);

    messageBuffer[totalSize + 0] = 13;
    messageBuffer[totalSize + 1] = 10;
    messageBuffer[totalSize + 2] = 0;
    OutputDebugStringA(messageBuffer);

    delete[] messageBuffer;
}

#endif  // _WIN32

 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 // Platform-independent debug logging.
 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void DebugLogging::logMessage(LogLevel logLevel, const char *scope, const char *fileName, int lineNumber, const char *message, ...)
{
    va_list args;
    va_start(args, message);
    logMessageV(logLevel, scope, fileName, lineNumber, message, args);
    va_end(args);
}

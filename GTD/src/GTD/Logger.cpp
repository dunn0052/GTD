#pragma once
#include "PCH/PCH.h"


#include "include/Logger.h"

namespace GTD
{
    const WORD Logger::COLOR_BLUE(10);
    const WORD Logger::COLOR_GREEN(11);
    const WORD Logger::COLOR_YELLOW(14);
    const WORD Logger::COLOR_RED(12);

    HANDLE const Logger::console = GetStdHandle(STD_OUTPUT_HANDLE);

    Logger& Logger::Instance(void)
    {
        static Logger instance;
        return instance;
    }

    void Logger::Log(LogLevel level, const char* debugLevel, const char* fileName, int lineNum, const char* format, ...)
    {
        //const std::lock_guard<std::mutex> lock(mMutex);

        if (level != mLogLevel)
        {
            mLogLevel = level;
            // Change logging color
            // Could just set enums to logging color
            switch (mLogLevel)
            {
            case LogLevel::DEBUG:
                {
                    SetConsoleTextAttribute(console, COLOR_BLUE); //blue
                    break;
                }

            case LogLevel::INFO:
                {
                    SetConsoleTextAttribute(console, COLOR_GREEN); //green
                    break;
                }

            case LogLevel::WARN:
                {
                    SetConsoleTextAttribute(console, COLOR_YELLOW); //yellow
                    break;
                }

            case LogLevel::FATAL:
                {
                    SetConsoleTextAttribute(console, COLOR_RED); //red
                    break;
                }
            default:
                {
                    SetConsoleTextAttribute(console, 0); // reset
                }
            }
        }

        printf_s("[%s][%s : %i] ", debugLevel, fileName, lineNum);
        char* sMessage = NULL;
        int nLength = 0;
        va_list args;
        va_start(args, format);
        //  Return the number of characters in the string referenced the list of arguments.
        // _vscprintf doesn't count terminating '\0' (that's why +1)
        nLength = _vscprintf(format, args) + 1;
        sMessage = new char[nLength];
        vsprintf_s(sMessage, nLength, format, args);
        //vsprintf(sMessage, format, args);
        std::cout << sMessage << "\n";
        va_end(args);

        delete[] sMessage;
    }
}

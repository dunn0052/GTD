#pragma once
#include <iostream>
#include <cstdarg>
#include <mutex>
#ifdef GTD_PLATFORM_WINDOWS
    #include <Windows.h>
#else
    #include <stdlib.h> // Linux or Mac? 
#endif

#include "Core.h"

#define DEBUG_MODE 1

#if DEBUG_MODE
    #define LOG_GENERAL( MESSAGE, LEVEL ) GTD::Logger::Instance().Log(LEVEL, "[%s:%d] %s", __FILE__, __LINE__, MESSAGE )
#else
    #define LOG_GENERAL
#endif
    
#define LOG_DEBUG( MESSAGE ) LOG_GENERAL( MESSAGE, GTD::LogLevel::DEBUG ) 	
#define LOG_INFO( MESSAGE ) LOG_GENERAL( MESSAGE, GTD::LogLevel::INFO ) 	
#define LOG_WARN( MESSAGE ) LOG_GENERAL( MESSAGE, GTD::LogLevel::WARN ) 	
#define LOG_FATAL( MESSAGE ) LOG_GENERAL( MESSAGE, GTD::LogLevel::FATAL ) 	


namespace GTD
{
    enum class GTD_API LogLevel
    {
        DEBUG,
        INFO,
        WARN,
        FATAL,
        NONE
    };

    class GTD_API Logger
    {
    public:
        static Logger& Instance(void);

        void Log(LogLevel level, const char* format, ...);

    private:
        Logger() {}
        ~Logger() {/* should clean up any file streams here*/};
        Logger(Logger const&) = delete;
        void operator = (Logger const&) = delete;
        LogLevel mLogLevel = LogLevel::NONE;

        // colors
        static const WORD COLOR_BLUE;
        static const WORD COLOR_GREEN;
        static const WORD COLOR_YELLOW;
        static const WORD COLOR_RED;
        static const HANDLE console;

        // thread guard
        std::mutex mMutex;
    };
}
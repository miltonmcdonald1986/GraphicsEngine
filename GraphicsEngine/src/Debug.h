#pragma once

#ifdef _WIN32
    #include <Windows.h>
    #define BREAKPOINT DebugBreak()
#elif defined(__linux__)
    #ifndef NDEBUG
        #include <signal.h>
        #define BREAKPOINT raise(SIGTRAP)
    #else
        #define BREAKPOINT
    #endif
#else
    #define BREAKPOINT
#endif

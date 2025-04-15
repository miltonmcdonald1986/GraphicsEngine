#pragma once

#ifdef _WIN32
    #include <windows.h>
    #define BREAKPOINT DebugBreak()
#elif defined(__linux__)
    #ifdef _DEBUG
        #include <signal.h>
        #define BREAKPOINT raise(SIGTRAP)
    #else
        #define BREAKPOINT
    #endif
#else
    #define BREAKPOINT
#endif

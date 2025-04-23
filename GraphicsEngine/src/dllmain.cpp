// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#ifdef _WIN32

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD /*ul_reason_for_call*/, LPVOID /*lpReserved*/)    //NOSONAR
{
    return TRUE;
}

#endif

#pragma once

#ifdef _WIN32
    #ifdef GRAPHICSENGINE_EXPORTS
		#define DLLEXPORT __declspec(dllexport)
	#else
		#define DLLEXPORT __declspec(dllimport)
	#endif
#elif defined(__linux__)
    #define DLLEXPORT
#else
    #define DLLEXPORT
#endif
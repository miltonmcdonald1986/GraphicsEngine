#pragma once

#ifdef _WIN32
    #ifdef GRAPHICSENGINE_EXPORTS
		#define GRAPHICSENGINE_API __declspec(dllexport)
	#else
		#define GRAPHICSENGINE_API __declspec(dllimport)
	#endif
#elif defined(__linux__)
    #define GRAPHICSENGINE_API
#else
    #define GRAPHICSENGINE_API
#endif
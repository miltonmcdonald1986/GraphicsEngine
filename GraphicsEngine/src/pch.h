#pragma once

#include <fstream>
#include <sstream>

#ifdef _WIN32

	// g++ does not support <stacktrace> yet
	#include <stacktrace>

	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

#endif

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

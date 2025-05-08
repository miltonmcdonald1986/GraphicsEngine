#pragma once

#include <filesystem>
#include <format>
#include <fstream>
#include <math.h>
#include <numbers>
#include <numeric>
#include <ranges>
#include <sstream>

#ifdef _WIN32

	// g++ does not support <stacktrace> yet
	#include <stacktrace>

	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

#endif

#include "glad/glad.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

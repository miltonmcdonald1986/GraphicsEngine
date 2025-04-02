#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stacktrace>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/ringbuffer_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include "glad/glad.h"

#include "glm/vec3.hpp"

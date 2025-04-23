#pragma once

#ifdef _WIN32
#endif

#include <filesystem>
#include <fstream>
#include <sstream>

#pragma warning ( push, 0 )

#include "spdlog/spdlog.h"
#include "spdlog/sinks/ringbuffer_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

#pragma warning ( pop )

#include "glad/glad.h"

#include "glm/vec3.hpp"

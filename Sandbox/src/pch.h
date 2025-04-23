#pragma once

#include <algorithm>
#include <filesystem>
#include <format>
#include <map>
#include <numbers>

#ifdef _WIN32
#include <crtdbg.h>
#endif

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/ext/matrix_transform.hpp"

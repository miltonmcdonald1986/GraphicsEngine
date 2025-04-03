#pragma once

#include <memory>

struct GLFWwindow;
using GLFWwindowSharedPtr = std::shared_ptr<GLFWwindow>;

class Widget;
using WidgetUniquePointer = std::unique_ptr<Widget>;

struct GEengine;
using GEengineSharedPtr = std::shared_ptr<GEengine>;

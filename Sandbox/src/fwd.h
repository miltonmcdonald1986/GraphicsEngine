#pragma once

#include <memory>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#define OUTPUT_DEBUG_STRING(msg) OutputDebugStringA(msg)
#else
#define OUTPUT_DEBUG_STRING(msg) ((void)0)  // Does nothing on non-Windows systems
#endif

namespace graphics_engine
{
	class IEngine;
	using IEnginePtr = std::shared_ptr<IEngine>;

	class ILog;
	using ILogPtr = std::shared_ptr<ILog>;

	class IShader;
	using IShaderPtr = std::shared_ptr<IShader>;

	class IUniform;
	using IUniformPtr = std::shared_ptr<IUniform>;

}

typedef struct GLFWwindow GLFWwindow;	//NOSONAR
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);	//NOSONAR

class Widget;
using WidgetPtr = std::shared_ptr<Widget>;
using Widgets = std::vector<WidgetPtr>;

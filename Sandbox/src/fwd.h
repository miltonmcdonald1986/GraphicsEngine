#pragma once

#include <memory>

namespace GraphicsEngine
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

typedef struct GLFWwindow GLFWwindow;
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);

class Widget;
using WidgetPtr = std::unique_ptr<Widget>;
using Widgets = std::vector<WidgetPtr>;

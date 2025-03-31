#pragma once

#include <memory>

#pragma region Forward declarations

struct GLFWwindow;
using GLFWwindowSharedPtr = std::shared_ptr<GLFWwindow>;

namespace GraphicsEngine
{
	class IEngine;
	using IEngineSharedPtr = std::shared_ptr<IEngine>;
}

#pragma endregion

class Widget
{
public:

	Widget(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine);

	virtual auto Iterate() -> void = 0;

protected:

	GLFWwindowSharedPtr m_spWindow;
	GraphicsEngine::IEngineSharedPtr m_spEngine;

};

using WidgetUniquePointer = std::unique_ptr<Widget>;

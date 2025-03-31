#pragma once

#include <memory>
#include <vector>

#pragma region Forward declarations

struct GLFWwindow;
using GLFWwindowSharedPtr = std::shared_ptr<GLFWwindow>;

class Widget;
using WidgetUniquePointer = std::unique_ptr<Widget>;

namespace GraphicsEngine
{

	class IEngine;
	using IEngineSharedPtr = std::shared_ptr<IEngine>;

}

#pragma endregion

class App
{
public:

	App(std::shared_ptr<GLFWwindow> spWindow, GraphicsEngine::IEngineSharedPtr spEngine);
	virtual ~App();

	virtual auto Run() -> void = 0;

protected:

	auto IterateWidgets() -> void;

	GLFWwindowSharedPtr m_spWindow;
	GraphicsEngine::IEngineSharedPtr m_spEngine;
	std::vector<WidgetUniquePointer> m_Widgets;
};

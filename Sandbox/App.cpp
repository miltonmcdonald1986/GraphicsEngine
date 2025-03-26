#include "App.h"
#include "Widget.h"

App::App(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine)
	: m_spWindow(spWindow),
	  m_spEngine(spEngine)
{
}

App::~App() = default;

auto App::IterateWidgets() -> void
{
	for (auto& upWidget : m_Widgets)
	{
		upWidget->Iterate();
	}
}

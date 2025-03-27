#include "App.h"
#include "Widget.h"

using namespace GraphicsEngine;

App::App(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<Engine> spEngine)
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

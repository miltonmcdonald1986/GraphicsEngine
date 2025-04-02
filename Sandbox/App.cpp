#include "App.h"

#include "GraphicsEngine/IEngine.h"

#include "Widget.h"

App::App(std::shared_ptr<GLFWwindow> spWindow)
	: m_spWindow(spWindow),
	  m_spEngine(GraphicsEngine::CreateEngine())
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

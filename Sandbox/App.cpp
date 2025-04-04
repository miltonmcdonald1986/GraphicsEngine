#include "App.h"

#include "GraphicsEngine/IEngine.h"

#include "Widget.h"

App::App(GLFWwindowSharedPtr spWindow)
	: m_spWindow(spWindow),
	  m_spEngine(std::shared_ptr<GEengine>(geCreateGraphicsEngine(), [](GEengine* pEngine) { geDestroyGraphicsEngine(pEngine); }))
{
}

App::~App()
{
}

auto App::IterateWidgets() -> void
{
	for (auto& upWidget : m_Widgets)
	{
		upWidget->Iterate();
	}
}

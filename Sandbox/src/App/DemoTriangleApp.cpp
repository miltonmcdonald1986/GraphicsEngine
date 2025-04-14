#include "DemoTriangleApp.h"

#include "IEngine.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	float vertices[] =
	{
		-1.f,  -0.5f, 0.f,
		 0.f,  -0.5f, 0.f,
		-0.5f,  0.5f, 0.f,
		 0.f,  -0.5f, 0.f,
		 1.f,  -0.5f, 0.f,
		 0.5f,  0.5f, 0.f
	};
    // geGenerateEntity_Pos3f(m_spEngine.get(), sizeof(vertices), vertices);

    m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
}

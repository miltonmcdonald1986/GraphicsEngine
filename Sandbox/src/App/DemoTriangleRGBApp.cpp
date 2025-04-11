#include "DemoTriangleRGBApp.h"

#include "IEngine.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "ShaderWidget.h"

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindow* spWindow)
    : App(spWindow)
{
	float vertices[] =
	{
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	geGenerateEntity_Pos3fCol3f(m_spEngine.get(), sizeof(vertices), vertices);

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, m_spEngine)));
}

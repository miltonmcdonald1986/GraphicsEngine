#include "DemoTriangleRGBApp.h"

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IAttribute.h"
#include "GraphicsEngine/IEntity.h"

#include "glm/vec3.hpp"

#include "BackgroundColorWidget.h"
#include "EngineLogWidget.h"
#include "PolygonModeWidget.h"
#include "ShaderWidget.h"

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindow* spWindow)
    : App(spWindow)
{
	m_spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f,  0.5f, 0.0f)
	};

	std::vector<glm::vec3> colors =
	{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	GraphicsEngine::IAttributes attributes = { GraphicsEngine::CreateAttribute(vertices), GraphicsEngine::CreateAttribute(colors)};
	auto spEntity = m_spEngine->CreateNewEntity(attributes);
	spEntity->SetShader(m_spEngine->CreateNewShaderFromFiles("shaders/DemoTriangleRGB.vert", "", "shaders/DemoTriangleRGB.frag"));

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new EngineLogWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, m_spEngine)));
}

#include "DemoTriangleRGBApp.h"

#include "IEngine.h"
#include "IAttribute.h"
#include "IEntity.h"

#include "glm/vec3.hpp"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "ShaderWidget.h"

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindow* spWindow)
    : App(spWindow)
{
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

	GraphicsEngine::IAttributes attributes = { GraphicsEngine::CreateAttribute(vertices), GraphicsEngine::CreateAttribute(colors) };
	auto spEntity = m_spEngine->CreateNewEntity(attributes);
	spEntity->SetShader(m_spEngine->CreateNewShaderFromFiles("shaders/A0Pos3fA1Dummy3f.vert", "", "shaders/A1RGB.frag"));

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, m_spEngine)));
}

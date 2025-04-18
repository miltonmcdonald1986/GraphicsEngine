#include "DemoTriangleApp.h"

#include "glm/vec3.hpp"

#include "IAttribute.h"
#include "IEngine.h"
#include "IEntity.h"

#include "BackgroundColorWidget.h"
#include "EngineLogWidget.h"
#include "PolygonModeWidget.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3( 0.5f, -0.5f, 0.f),
		glm::vec3( 0.f,   0.5f, 0.f)
	};

	GraphicsEngine::IAttributes attributes;
	attributes.push_back(GraphicsEngine::CreateAttribute(vertices));
	auto spEntity = m_spEngine->CreateNewEntity(attributes);
	spEntity->SetShader(m_spEngine->CreateNewShaderFromFiles("shaders/A0Pos32f.vert", "", "shaders/ColorIs0080233.frag"));

    m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new EngineLogWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
}

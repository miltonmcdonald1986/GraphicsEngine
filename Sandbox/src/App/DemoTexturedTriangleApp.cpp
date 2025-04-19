#include "DemoTexturedTriangleApp.h"

#include "glm/vec3.hpp"

#include "IAttribute.h"
#include "IEngine.h"
#include "IEntity.h"

#include "BackgroundColorWidget.h"
#include "EngineLogWidget.h"
#include "PolygonModeWidget.h"

DemoTexturedTriangleApp::DemoTexturedTriangleApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.f,   0.5f, 0.f)
	};

	auto spEntity = m_spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices) });
	spEntity->SetShader(m_spEngine->CreateNewShaderFromFiles("shaders/A0Pos3fA1Dummy2f.vert", "", "shaders/Texture2d.frag"));

	m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new EngineLogWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
}

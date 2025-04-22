#include "DemoTriangleApp.h"

#include "glm/vec3.hpp"

#include "GraphicsEngine/IAttribute.h"
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IEntity.h"

#include "BackgroundColorWidget.h"
#include "EngineLogWidget.h"
#include "PolygonModeWidget.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	m_spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3( 0.5f, -0.5f, 0.f),
		glm::vec3( 0.f,   0.5f, 0.f)
	};

	auto spEntity = m_spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices) });
	spEntity->SetShader(m_spEngine->CreateNewShaderFromFiles("shaders/DemoTriangle.vert", "", "shaders/DemoTriangle.frag"));
}

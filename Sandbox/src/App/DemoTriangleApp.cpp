#include "DemoTriangleApp.h"

#include "GraphicsEngine/IEngine.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	auto spEngine = GetEngine();

	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3( 0.5f, -0.5f, 0.f),
		glm::vec3( 0.f,   0.5f, 0.f)
	};

	auto spEntity = spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices) });
	spEntity->SetShader(spEngine->CreateNewShaderFromFiles("shaders/DemoTriangle.vert", "", "shaders/DemoTriangle.frag"));
}

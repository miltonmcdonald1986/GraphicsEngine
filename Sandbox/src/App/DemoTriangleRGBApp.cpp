#include "DemoTriangleRGBApp.h"

#include "GraphicsEngine/IEngine.h"

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindow* spWindow)
    : App(spWindow)
{
	auto spEngine = GetEngine();
	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

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
	auto spEntity = spEngine->CreateNewEntity(attributes);
	spEntity->SetShader(spEngine->CreateNewShaderFromFiles(std::filesystem::path(SHADERS_DIR)/"DemoTriangleRGB.vert", "", std::filesystem::path(SHADERS_DIR)/"DemoTriangleRGB.frag"));
}

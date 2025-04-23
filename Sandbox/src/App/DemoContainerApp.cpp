#include "DemoContainerApp.h"

#include "GraphicsEngine/IEngine.h"

DemoContainerApp::DemoContainerApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	m_spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.f),
		glm::vec3(-0.5f, 0.5f, 0.f)
	};

	std::vector<glm::vec2> texCoords =
	{
		glm::vec2(0.f, 0.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(0.f, 1.f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	auto spEntity = m_spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices), GraphicsEngine::CreateAttribute(texCoords) }, indices);
	spEntity->SetShader(m_spEngine->CreateNewShaderFromFiles("shaders/DemoContainer.vert", "", "shaders/DemoContainer.frag"));
	spEntity->SetTextures({ m_spEngine->CreateNewTextureFromFile("uTexture", "textures/container.jpg") });
}

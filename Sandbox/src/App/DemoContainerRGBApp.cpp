#include "DemoContainerRGBApp.h"

#include "GraphicsEngine/IEngine.h"

DemoContainerRGBApp::DemoContainerRGBApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	auto spEngine = GetEngine();
	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.f),
		glm::vec3(-0.5f, 0.5f, 0.f)
	};

	std::vector<glm::vec3> colors =
	{
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(1.f, 1.f, 0.f)
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

	auto oShaderId = spEngine->GetShaderManager()->AddShader(std::filesystem::path(SHADERS_DIR) / "DemoContainerRGB.vert", std::filesystem::path(SHADERS_DIR) / "DemoContainerRGB.frag");

	auto spEntity = spEngine->CreateNewEntity({
		GraphicsEngine::CreateAttribute(vertices), 
		GraphicsEngine::CreateAttribute(colors),
		GraphicsEngine::CreateAttribute(texCoords) 
		}, indices);

	spEntity->SetShaderId(*oShaderId);
	spEntity->SetTextures({ spEngine->CreateNewTextureFromFile("uTexture", std::filesystem::path(TEXTURES_DIR)/"container.jpg") });
}

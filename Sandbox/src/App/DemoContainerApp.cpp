#include "DemoContainerApp.h"

#include "GraphicsEngine/IEngine.h"

DemoContainerApp::DemoContainerApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	auto spEngine = GetEngine();

	spEngine->SetBackgroundColor(graphics_engine::Types::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

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
	
	auto pEntity = spEngine->GetEntityManager()->AddEntity({ vertices, texCoords }, indices);	
	pEntity->pShader = spEngine->GetShaderManager ()->AddShaderFromFiles (std::filesystem::path (SHADERS_DIR) / "DemoContainer.vert", std::filesystem::path (SHADERS_DIR) / "DemoContainer.frag");
	pEntity->textures = { spEngine->CreateNewTextureFromFile("uTexture", std::filesystem::path(TEXTURES_DIR)/"container.jpg") };
}

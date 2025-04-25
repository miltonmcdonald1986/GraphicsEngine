#include "DemoTexturedTriangleApp.h"

#include "GraphicsEngine/IEngine.h"

DemoTexturedTriangleApp::DemoTexturedTriangleApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	auto spEngine = GetEngine();
	if (!spEngine)
		return;
	
	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.f,   0.5f, 0.f)
	};

	std::vector<glm::vec2> texCoords =
	{
		glm::vec2(0.f, 0.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.5f, 1.f)
	};

	auto spEntity = spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices), GraphicsEngine::CreateAttribute(texCoords) });
	spEntity->SetShader(spEngine->CreateNewShaderFromFiles(std::filesystem::path(SHADERS_DIR)/"DemoTexturedTriangle.vert", "", std::filesystem::path(SHADERS_DIR)/"DemoTexturedTriangle.frag"));
	spEntity->SetTextures({ spEngine->CreateNewTextureFromFile("uTexture", std::filesystem::path(TEXTURES_DIR)/"wall.jpg") });
}

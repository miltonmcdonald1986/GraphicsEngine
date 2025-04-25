#include "DemoTexturesCombinedApp.h"

#include "GraphicsEngine/IEngine.h"

DemoTexturesCombinedApp::DemoTexturesCombinedApp(GLFWwindow* pWindow)
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

	auto spEntity = spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices), GraphicsEngine::CreateAttribute(texCoords) }, indices);
	auto spShader = spEngine->CreateNewShaderFromFiles(std::filesystem::path(SHADERS_DIR)/"DemoTexturesCombined.vert", "", std::filesystem::path(SHADERS_DIR)/"DemoTexturesCombined.frag");
    spEntity->SetShader(spShader);
	spEntity->SetTextures({ 
        spEngine->CreateNewTextureFromFile("uTextureContainer", std::filesystem::path(TEXTURES_DIR)/"container.jpg"),
        spEngine->CreateNewTextureFromFile("uTextureAwesomeFace", std::filesystem::path(TEXTURES_DIR)/"awesomeface.png")
        });

    if (spShader)
        {
            auto spUniform = spShader->GetActiveUniform("uMix");
            if (spUniform)
                spUniform->SetData(0.2f);
        }
}

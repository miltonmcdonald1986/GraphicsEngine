#include "DemoTexturesCombinedApp.h"
#include "DemoCoordinateSystemsUtilities.h"

#include "GraphicsEngine/IEngine.h"

DemoTexturesCombinedApp::DemoTexturesCombinedApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	auto spEngine = GetEngine();
	if (!spEngine)
		return;

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

	m_pEntity = spEngine->GetEntityManager()->AddEntity({ vertices, texCoords }, indices);

	auto [shader, textures] = Utilities::PrepareShaderAndTextures(spEngine);
	m_pEntity->shader = shader;
	m_pEntity->textures = textures;
	
	m_pEntity->modelMatrix = glm::mat4(1.f);
	m_pEntity->shader->SetUniformData("view", glm::mat4(1.f));
}

auto DemoTexturesCombinedApp::Iterate() -> void
{
	int width;
	int height;
	glfwGetWindowSize(GetWindow(), &width, &height);
	auto fWidth = static_cast<float>(width);
	auto fHeight = static_cast<float>(height);
	m_pEntity->shader->SetUniformData("projection", glm::ortho(-fWidth / fHeight, fWidth / fHeight, -1.f, 1.f, -1.f, 1.f));

	App::Iterate();
}

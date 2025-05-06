#include "DemoCoordinateSystemsApp.h"
#include "DemoCoordinateSystemsUtilities.h"

#include "glm/ext/matrix_clip_space.hpp"

DemoCoordinateSystemsApp::DemoCoordinateSystemsApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    auto spEngine = GetEngine();
    if (!spEngine)
        return;

    spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

    GraphicsEngine::IAttributePtr spAttrVertices = GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{
        glm::vec3(-0.5f, -0.5f, 0.f),
            glm::vec3(0.5f, -0.5f, 0.f),
            glm::vec3(0.5f, 0.5f, 0.f),
            glm::vec3(-0.5f, 0.5f, 0.f)
    });

    GraphicsEngine::IAttributePtr spAttrTexCoords = GraphicsEngine::CreateAttribute(std::vector<glm::vec2>{
        glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f)
    });

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    auto pEntity = spEngine->GetEntityManager()->AddEntity({ spAttrVertices, spAttrTexCoords }, indices);
    if (!pEntity)
    {
        GetEngine()->GetLog()->Error("Failed to create entity.");
        return;
    }

    pEntity->modelMatrix = glm::rotate(glm::mat4(1.f), glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));

    auto pShaderManager = spEngine->GetShaderManager();
    if (!pShaderManager)
        return;

	auto [shaderId, textures] = Utilities::PrepareShaderAndTextures(GetEngine());
    pShaderManager->SetUniformData(shaderId, "view", glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)));
    pShaderManager->SetUniformData(shaderId, "projection", glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f));

    pEntity->shaderId = shaderId;
    pEntity->textures = textures;
}

auto DemoCoordinateSystemsApp::Iterate() -> void
{
    int width;
    int height;
    glfwGetWindowSize(GetWindow(), &width, &height);

    auto pShaderManager = GetEngine()->GetShaderManager();
    pShaderManager->SetUniformData(*pShaderManager->GetCurrentShader(), "projection", glm::perspective(glm::radians(45.f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f));

    App::Iterate();
}

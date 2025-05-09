#include "DemoCoordinateSystemsDepthApp.h"
#include "DemoCoordinateSystemsUtilities.h"
#include "EngineLogWidget.h"

#include "GraphicsEngine/AttributeFactory.h"
#include "GraphicsEngine/IEntityFactory.h"

#include "glm/ext/matrix_clip_space.hpp"

auto InitCube(GraphicsEngine::IEnginePtr spEngine) -> GraphicsEngine::Entity*
{
    auto [shaderId, textures] = Utilities::PrepareShaderAndTextures(spEngine);
    auto spEntityFactory = GraphicsEngine::CreateEntityFactory(spEngine);

    auto spAttrPos = GraphicsEngine::AttributeFactory::Cube::Position();
    auto spAttrTexCoords = GraphicsEngine::AttributeFactory::Cube::TextureCoordinates();
    auto spCube = spEntityFactory->AddCube({ spAttrPos, spAttrTexCoords });
    spCube->shaderId = shaderId;
    spCube->textures = textures;

    return spCube;
}

DemoCoordinateSystemsDepthApp::DemoCoordinateSystemsDepthApp(GLFWwindow* pWindow)
    :   App(pWindow),
        m_pEntity(InitCube(GetEngine()))
{
    GetEngine()->SetBackgroundColor(GraphicsEngine::Color{.r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f});

    m_pEntity->modelMatrix = glm::rotate(glm::mat4(1.f), glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));

    auto pShaderManager = GetEngine()->GetShaderManager();
    pShaderManager->SetUniformData(m_pEntity->shaderId, "view", glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)));
    pShaderManager->SetUniformData(m_pEntity->shaderId, "projection", glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f));
}

auto DemoCoordinateSystemsDepthApp::Iterate() -> void
{
    static auto start = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();
    auto diff = now - start;
    auto seconds = std::chrono::duration<float>(diff).count();

    auto pShaderManager = GetEngine()->GetShaderManager();
    auto shaderId = pShaderManager->GetCurrentShader();

    m_pEntity->modelMatrix = glm::rotate(glm::mat4(1.f), seconds * glm::radians(50.f), glm::vec3(0.5f, 1.f, 0.f));
    pShaderManager->SetUniformData(*shaderId, "model", m_pEntity->modelMatrix);

    int width;
    int height;
    glfwGetWindowSize(GetWindow(), &width, &height);
    pShaderManager->SetUniformData(*shaderId, "projection", glm::perspective(glm::radians(45.f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f));

    App::Iterate();
}

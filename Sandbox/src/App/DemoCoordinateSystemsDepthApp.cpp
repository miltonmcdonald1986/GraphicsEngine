#include "DemoCoordinateSystemsDepthApp.h"
#include "DemoCoordinateSystemsUtilities.h"
#include "EngineLogWidget.h"

#include "GraphicsEngine/AttributeFactory.h"
#include "GraphicsEngine/IEntityFactory.h"

#include "glm/ext/matrix_clip_space.hpp"

auto InitCube(GraphicsEngine::IEnginePtr spEngine) -> GraphicsEngine::Entity*
{
    auto [pShader, textures] = Utilities::PrepareShaderAndTextures(spEngine);
    auto spEntityFactory = GraphicsEngine::CreateEntityFactory(spEngine);

    auto spAttrPos = GraphicsEngine::AttributeFactory::Cube::Position();
    auto spAttrTexCoords = GraphicsEngine::AttributeFactory::Cube::TextureCoordinates();
    auto spCube = spEntityFactory->AddCube({ spAttrPos, spAttrTexCoords });
    spCube->pShader = pShader;
    spCube->textures = textures;

    return spCube;
}

DemoCoordinateSystemsDepthApp::DemoCoordinateSystemsDepthApp(GLFWwindow* pWindow)
    :   App(pWindow),
        m_pEntity(InitCube(GetEngine()))
{
    GetEngine()->SetBackgroundColor(GraphicsEngine::Types::Color{.r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f});

    m_pEntity->modelMatrix = glm::rotate(glm::mat4(1.f), glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));

    auto pShader = GetEngine ()->GetShaderManager ()->GetCurrentShader ();
    pShader->SetUniformData("view", glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)));
    pShader->SetUniformData("projection", glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f));
}

auto DemoCoordinateSystemsDepthApp::Iterate() -> void
{
    static auto start = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();
    auto diff = now - start;
    auto seconds = std::chrono::duration<float>(diff).count();

    auto pShader = GetEngine()->GetShaderManager()->GetCurrentShader ();
    m_pEntity->modelMatrix = glm::rotate(glm::mat4(1.f), seconds * glm::radians(50.f), glm::vec3(0.5f, 1.f, 0.f));
    pShader->SetUniformData("model", m_pEntity->modelMatrix);

    int width;
    int height;
    glfwGetWindowSize(GetWindow(), &width, &height);
    pShader->SetUniformData("projection", glm::perspective(glm::radians(45.f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f));

    App::Iterate();
}

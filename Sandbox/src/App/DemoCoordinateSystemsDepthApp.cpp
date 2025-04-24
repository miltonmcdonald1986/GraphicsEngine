#include "DemoCoordinateSystemsDepthApp.h"
#include "EngineLogWidget.h"

#include "GraphicsEngine/IEntityFactory.h"

#include "glm/ext/matrix_clip_space.hpp"

DemoCoordinateSystemsDepthApp::DemoCoordinateSystemsDepthApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    GetEngine()->SetBackgroundColor(GraphicsEngine::Color{.r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f});

    auto spShader = GetEngine()->CreateNewShaderFromFiles("shaders/DemoCoordinateSystems.vert", "", "shaders/DemoCoordinateSystems.frag");
    if (!spShader)
    {
        GetEngine()->GetLog()->Error("Failed to create shader.");
        return;
    }

    GraphicsEngine::ITextures textures;
    textures.push_back(GetEngine()->CreateNewTextureFromFile("texture1", "textures/container.jpg"));
    textures.push_back(GetEngine()->CreateNewTextureFromFile("texture2", "textures/awesomeface.png"));

    auto spEntityFactory = GraphicsEngine::CreateEntityFactory(GetEngine());
    m_spEntity = spEntityFactory->CreateCubeTextured(spShader, textures);

    m_spEntity->SetModelMatrix(glm::rotate(glm::mat4(1.f), glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f)));

    spShader->GetActiveUniform("model")->SetData(m_spEntity->GetModelMatrix());
    spShader->GetActiveUniform("view")->SetData(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)));
    spShader->GetActiveUniform("projection")->SetData(glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f));
}

auto DemoCoordinateSystemsDepthApp::Iterate() -> void
{
    static auto start = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();
    auto diff = now - start;
    auto seconds = std::chrono::duration<float>(diff).count();\

        m_spEntity->SetModelMatrix(glm::rotate(glm::mat4(1.f), seconds * glm::radians(50.f), glm::vec3(0.5f, 1.f, 0.f)));
    m_spEntity->GetShader()->GetActiveUniform("model")->SetData(m_spEntity->GetModelMatrix());

    App::Iterate();
}

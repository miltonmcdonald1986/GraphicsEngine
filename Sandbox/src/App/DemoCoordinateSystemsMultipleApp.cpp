#include "DemoCoordinateSystemsMultipleApp.h"
#include "DemoCoordinateSystemsUtilities.h"
#include "EngineLogWidget.h"

#include "GraphicsEngine/ICameraFly.h"
#include "GraphicsEngine/IEntityFactory.h"

#include "glm/ext/matrix_clip_space.hpp"

DemoCoordinateSystemsMultipleApp::DemoCoordinateSystemsMultipleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    GetEngine()->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

    auto [spShader, textures] = Utilities::PrepareShaderAndTextures(GetEngine());

    auto spEntityFactory = GraphicsEngine::CreateEntityFactory(GetEngine());

    std::vector<glm::vec3> positions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    GraphicsEngine::IEntities cubes;
    for (size_t i = 0; i < positions.size(); ++i)
    {
        cubes.push_back(spEntityFactory->CreateCubeTextured(spShader, textures));
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, positions[i]);
        model = glm::rotate(model, glm::radians(20.f * i), glm::vec3(1.0f, 0.3f, 0.5f));
        cubes.back()->SetModelMatrix(model);
    }

    GetEngine()->SetCamera(GraphicsEngine::CreateCameraFly());

    //spShader->GetActiveUniform("view")->SetData(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)));
    spShader->GetActiveUniform("projection")->SetData(glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f));
}

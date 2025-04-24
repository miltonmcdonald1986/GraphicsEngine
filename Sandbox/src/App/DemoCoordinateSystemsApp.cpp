#include "DemoCoordinateSystemsApp.h"

#include "glm/ext/matrix_clip_space.hpp"

DemoCoordinateSystemsApp::DemoCoordinateSystemsApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    GetEngine()->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

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

    auto spEntity = GetEngine()->CreateNewEntity({ spAttrVertices, spAttrTexCoords }, indices);
    if (!spEntity)
    {
        GetEngine()->GetLog()->Error("Failed to create entity.");
        return;
    }

    auto spShader = GetEngine()->CreateNewShaderFromFiles("shaders/DemoCoordinateSystems.vert", "", "shaders/DemoCoordinateSystems.frag");
    if (!spShader)
    {
        GetEngine()->GetLog()->Error("Failed to create shader.");
        return;
    }

    spShader->GetActiveUniform("model")->SetData(glm::rotate(glm::mat4(1.f), glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f)));
    spShader->GetActiveUniform("view")->SetData(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)));
    spShader->GetActiveUniform("projection")->SetData(glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f));

    spEntity->SetShader(spShader);

    auto spTexture1 = GetEngine()->CreateNewTextureFromFile("texture1", "textures/container.jpg");
    auto spTexture2 = GetEngine()->CreateNewTextureFromFile("texture2", "textures/awesomeface.png");

    spEntity->SetTextures({ spTexture1, spTexture2 });
}

#include "DemoIndexedPointsApp.h"

#include "GraphicsEngine/IEngine.h"

DemoIndexedPointsApp::DemoIndexedPointsApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    auto spEngine = GetEngine();
    if (!spEngine)
        return;
    
    spEngine->SetBackgroundColor(GraphicsEngine::Types::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

    std::vector<glm::vec3> vertices = {
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f,  0.5f, 0.0f) 
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    auto pEntity = spEngine->GetEntityManager()->AddEntity({ vertices }, indices);
    auto pShader = spEngine->GetShaderManager()->AddShaderFromFiles(std::filesystem::path(SHADERS_DIR)/"DemoIndexedPoints.vert", std::filesystem::path(SHADERS_DIR)/"DemoIndexedPoints.frag");
    pEntity->pShader= pShader;
}

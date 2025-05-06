#include "DemoIndexedPointsApp.h"

#include "GraphicsEngine/IEngine.h"

DemoIndexedPointsApp::DemoIndexedPointsApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    auto spEngine = GetEngine();
    if (!spEngine)
        return;
    
    spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

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

    auto spEntity = spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices) }, indices);
    auto shaderId = spEngine->GetShaderManager()->AddShader(std::filesystem::path(SHADERS_DIR)/"DemoIndexedPoints.vert", std::filesystem::path(SHADERS_DIR)/"DemoIndexedPoints.frag");
    spEntity->SetShaderId(*shaderId);
}

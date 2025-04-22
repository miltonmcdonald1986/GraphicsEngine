#include "DemoIndexedPointsApp.h"

#include "glm/glm.hpp"

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IAttribute.h"
#include "GraphicsEngine/IEntity.h"

#include "BackgroundColorWidget.h"
#include "EngineLogWidget.h"
#include "PolygonModeWidget.h"

DemoIndexedPointsApp::DemoIndexedPointsApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    m_spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

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

    auto spEntity = m_spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices) }, indices);
    auto spShader = m_spEngine->CreateNewShaderFromFiles("shaders/DemoIndexedPoints.vert", "", "shaders/DemoIndexedPoints.frag");
    spEntity->SetShader(spShader);
}

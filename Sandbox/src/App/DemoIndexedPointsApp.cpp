#include "DemoIndexedPointsApp.h"

#include "glm/glm.hpp"

#include "IEngine.h"
#include "IAttribute.h"
#include "IEntity.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"

DemoIndexedPointsApp::DemoIndexedPointsApp(GLFWwindow* pWindow)
    : App(pWindow)
{
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
    auto spShader = m_spEngine->CreateNewShaderFromFiles("shaders/A0Pos3f.vert", "", "shaders/ColorIs008033.frag");
    spEntity->SetShader(spShader);

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(pWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(pWindow, m_spEngine)));
}

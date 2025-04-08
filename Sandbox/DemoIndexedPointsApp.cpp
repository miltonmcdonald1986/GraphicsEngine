#include "DemoIndexedPointsApp.h"

#include "glm/glm.hpp"

#include "GraphicsEngine/IEngine.h"

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

    geGenerateEntity_IndexedPoints3DBasic(m_spEngine.get(), 3*vertices.size()*sizeof(float), &vertices[0][0], indices.size()*sizeof(unsigned int), indices.data());

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(pWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(pWindow, m_spEngine)));
}

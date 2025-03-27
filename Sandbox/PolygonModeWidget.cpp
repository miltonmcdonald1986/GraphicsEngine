#include "PolygonModeWidget.h"

#include <Windows.h>

#include "imgui.h"

#include "GraphicsEngine/GLUtilities.h"

PolygonModeWidget::PolygonModeWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine)
    : Widget(spWindow, spEngine)
{
    GLint param[2];
    glGetIntegerv(GL_POLYGON_MODE, param);
    
    if (static_cast<GraphicsEngine::GL::PolygonModeType>(param[0]) == GraphicsEngine::GL::PolygonModeType::Point)
        m_Mode = 0;
    if (static_cast<GraphicsEngine::GL::PolygonModeType>(param[0]) == GraphicsEngine::GL::PolygonModeType::Line)
        m_Mode = 1;
    if (static_cast<GraphicsEngine::GL::PolygonModeType>(param[0]) == GraphicsEngine::GL::PolygonModeType::Fill)
        m_Mode = 2;
}

void PolygonModeWidget::Iterate()
{
    auto UpdatePolygonMode = [](int mode)
    {
        GraphicsEngine::GL::PolygonModeType modeType = GraphicsEngine::GL::PolygonModeType::Fill;
        switch (mode)
        {
        case 0:
            modeType = GraphicsEngine::GL::PolygonModeType::Point;
            break;
        case 1:
            modeType = GraphicsEngine::GL::PolygonModeType::Line;
            break;
        case 2:
            modeType = GraphicsEngine::GL::PolygonModeType::Fill;
            break;
        }

        GraphicsEngine::GL::PolygonMode(modeType);
    };

    ImGui::Begin("Polygon Mode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::RadioButton("Point", &m_Mode, 0))
        UpdatePolygonMode(m_Mode);
    ImGui::SameLine();
    if (ImGui::RadioButton("Line", &m_Mode, 1))
        UpdatePolygonMode(m_Mode);
    ImGui::SameLine();
    if (ImGui::RadioButton("Fill", &m_Mode, 2))
        UpdatePolygonMode(m_Mode);
    ImGui::End();
}

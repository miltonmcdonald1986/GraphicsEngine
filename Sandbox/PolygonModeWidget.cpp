#include "PolygonModeWidget.h"

#include <Windows.h>

#include "imgui.h"

#include "GLUtilities.h"

PolygonModeWidget::PolygonModeWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine)
    : Widget(spWindow, spEngine)
{
    GLint param[2];
    glGetIntegerv(GL_POLYGON_MODE, param);
    
    if (static_cast<GraphicsEngine::GL::Utilities::PolygonModeType>(param[0]) == GraphicsEngine::GL::Utilities::PolygonModeType::Point)
        m_Mode = 0;
    if (static_cast<GraphicsEngine::GL::Utilities::PolygonModeType>(param[0]) == GraphicsEngine::GL::Utilities::PolygonModeType::Line)
        m_Mode = 1;
    if (static_cast<GraphicsEngine::GL::Utilities::PolygonModeType>(param[0]) == GraphicsEngine::GL::Utilities::PolygonModeType::Fill)
        m_Mode = 2;
}

void PolygonModeWidget::Iterate()
{
    auto UpdatePolygonMode = [](int mode)
    {
        GraphicsEngine::GL::Utilities::PolygonModeType modeType = GraphicsEngine::GL::Utilities::PolygonModeType::Fill;
        switch (mode)
        {
        case 0:
            modeType = GraphicsEngine::GL::Utilities::PolygonModeType::Point;
            break;
        case 1:
            modeType = GraphicsEngine::GL::Utilities::PolygonModeType::Line;
            break;
        case 2:
            modeType = GraphicsEngine::GL::Utilities::PolygonModeType::Fill;
            break;
        }

        GraphicsEngine::GL::Utilities::PolygonMode(modeType);
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

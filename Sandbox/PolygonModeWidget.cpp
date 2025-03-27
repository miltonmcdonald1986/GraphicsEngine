#include "PolygonModeWidget.h"

#include <Windows.h>

#include "imgui.h"

#include "GraphicsEngine/GL.h"

using namespace GraphicsEngine;

PolygonModeWidget::PolygonModeWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<Engine> spEngine)
    : Widget(spWindow, spEngine)
{
    GLint param[2];
    glGetIntegerv(GL_POLYGON_MODE, param);
    
    if (static_cast<GL::PolygonModeType>(param[0]) == GL::PolygonModeType::Point)
        m_Mode = 0;
    if (static_cast<GL::PolygonModeType>(param[0]) == GL::PolygonModeType::Line)
        m_Mode = 1;
    if (static_cast<GL::PolygonModeType>(param[0]) == GL::PolygonModeType::Fill)
        m_Mode = 2;
}

void PolygonModeWidget::Iterate()
{
    auto UpdatePolygonMode = [](int mode)
    {
        GL::PolygonModeType modeType = GL::PolygonModeType::Fill;
        switch (mode)
        {
        case 0:
            modeType = GL::PolygonModeType::Point;
            break;
        case 1:
            modeType = GL::PolygonModeType::Line;
            break;
        case 2:
            modeType = GL::PolygonModeType::Fill;
            break;
        }

        GL::PolygonMode(modeType);
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

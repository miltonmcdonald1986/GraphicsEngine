#include "PolygonModeWidget.h"

#include "imgui.h"

#include "GraphicsEngine/GL.h"

using namespace GraphicsEngine;

PolygonModeWidget::PolygonModeWidget(std::shared_ptr<GLFWwindow> spWindow, IEngineSharedPtr spEngine)
    : Widget(spWindow, spEngine)
{
    switch (GraphicsEngine::GL::GetPolygonMode())
    {
    case GL::PolygonMode::Point:
        m_Mode = 0;
        break;
    case GL::PolygonMode::Line:
        m_Mode = 1;
        break;
    default:
        m_Mode = 2;
        break;
    }
}

void PolygonModeWidget::Iterate()
{
    ImGui::Begin("Polygon Mode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::RadioButton("Point", &m_Mode, 0))
        GL::SetPolygonMode(GL::PolygonMode::Point);
    ImGui::SameLine();
    if (ImGui::RadioButton("Line", &m_Mode, 1))
        GL::SetPolygonMode(GL::PolygonMode::Line);
    ImGui::SameLine();
    if (ImGui::RadioButton("Fill", &m_Mode, 2))
        GL::SetPolygonMode(GL::PolygonMode::Fill);
    ImGui::End();
}

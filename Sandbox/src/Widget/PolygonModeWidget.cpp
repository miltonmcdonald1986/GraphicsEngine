#include "PolygonModeWidget.h"

#include "imgui.h"

#include "IEngine.h"

PolygonModeWidget::PolygonModeWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine)
{
    switch (m_spEngine->GetPolygonMode())
    {
    case GraphicsEngine::PolygonMode::Fill:
        m_Mode = 2;
        break;
    case GraphicsEngine::PolygonMode::Line:
        m_Mode = 1;
        break;
    case GraphicsEngine::PolygonMode::Point:
    default:
        m_Mode = 0;
        break;
    }
}

void PolygonModeWidget::Iterate()
{
    ImGui::Begin("Polygon Mode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::RadioButton("Point", &m_Mode, 0))
        m_spEngine->SetPolygonMode(GraphicsEngine::PolygonMode::Point);
    ImGui::SameLine();
    if (ImGui::RadioButton("Line", &m_Mode, 1))
        m_spEngine->SetPolygonMode(GraphicsEngine::PolygonMode::Line);
    ImGui::SameLine();
    if (ImGui::RadioButton("Fill", &m_Mode, 2))
        m_spEngine->SetPolygonMode(GraphicsEngine::PolygonMode::Fill);
    ImGui::End();
}

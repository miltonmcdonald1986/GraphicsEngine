#include "PolygonModeWidget.h"

#include "GraphicsEngine/IEngine.h"

PolygonModeWidget::PolygonModeWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine)
{
    switch (m_spEngine->GetPolygonMode())
    {
	using enum GraphicsEngine::PolygonMode;
    case Fill:
        m_Mode = 2;
        break;
    case Line:
        m_Mode = 1;
        break;
    case Point:
    default:
        m_Mode = 0;
        break;
    }
}

void PolygonModeWidget::Iterate()
{
	using enum GraphicsEngine::PolygonMode;

    ImGui::Begin("Polygon Mode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::RadioButton("Point", &m_Mode, 0))
        m_spEngine->SetPolygonMode(Point);
    ImGui::SameLine();
    if (ImGui::RadioButton("Line", &m_Mode, 1))
        m_spEngine->SetPolygonMode(Line);
    ImGui::SameLine();
    if (ImGui::RadioButton("Fill", &m_Mode, 2))
        m_spEngine->SetPolygonMode(Fill);
    ImGui::End();
}

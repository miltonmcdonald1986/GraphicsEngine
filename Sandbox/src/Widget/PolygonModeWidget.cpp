#include "PolygonModeWidget.h"

#include "GraphicsEngine/IEngine.h"

PolygonModeWidget::PolygonModeWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine)
{
    switch (GetEngine()->GetPolygonMode())
    {
	using enum graphics_engine::Types::PolygonMode;
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

void PolygonModeWidget::Iterate(bool* pShow)
{
	using enum graphics_engine::Types::PolygonMode;

    auto spEngine = GetEngine();
    ImGui::Begin("Polygon Mode", pShow, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::RadioButton("Point", &m_Mode, 0))
        spEngine->SetPolygonMode(Point);
    ImGui::SameLine();
    if (ImGui::RadioButton("Line", &m_Mode, 1))
        spEngine->SetPolygonMode(Line);
    ImGui::SameLine();
    if (ImGui::RadioButton("Fill", &m_Mode, 2))
        spEngine->SetPolygonMode(Fill);
    ImGui::End();
}

auto CreatePolygonModeWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine) -> PolygonModeWidgetPtr
{
    return std::make_shared<PolygonModeWidget>(pWindow, spEngine);
}

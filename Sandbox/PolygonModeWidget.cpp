#include "PolygonModeWidget.h"

#include "imgui.h"

#include "GraphicsEngine/IEngine.h"

PolygonModeWidget::PolygonModeWidget(GLFWwindowSharedPtr spWindow, GEengineSharedPtr spEngine)
    : Widget(spWindow, spEngine)
{
    switch (geGetPolygonMode())
    {
    case GE_POLYGON_MODE_POINT:
        m_Mode = 0;
        break;
    case GE_POLYGON_MODE_LINE:
        m_Mode = 1;
        break;
    case GE_POLYGON_MODE_FILL:
    default:
        m_Mode = 2;
        break;
    }
}

void PolygonModeWidget::Iterate()
{
    ImGui::Begin("Polygon Mode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::RadioButton("Point", &m_Mode, 0))
        geSetPolygonMode(GE_POLYGON_MODE_POINT);
    ImGui::SameLine();
    if (ImGui::RadioButton("Line", &m_Mode, 1))
        geSetPolygonMode(GE_POLYGON_MODE_LINE);
    ImGui::SameLine();
    if (ImGui::RadioButton("Fill", &m_Mode, 2))
        geSetPolygonMode(GE_POLYGON_MODE_FILL);
    ImGui::End();
}

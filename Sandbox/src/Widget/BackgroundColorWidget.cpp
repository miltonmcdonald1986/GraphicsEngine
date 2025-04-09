#include "BackgroundColorWidget.h"

#include "IEngine.h"

#include "imgui.h"

BackgroundColorWidget::BackgroundColorWidget(GLFWwindow* pWindow, GEengineSharedPtr spEngine)
    : Widget(pWindow, spEngine)
{
    geGetBackgroundColor(m_Color);
}

void BackgroundColorWidget::Iterate()
{
    ImGui::Begin("Background Color", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::ColorEdit4("##2f", m_Color, ImGuiColorEditFlags_Float))
    {
        geSetBackgroundColor(m_Color);
    }

    ImGui::End();
}

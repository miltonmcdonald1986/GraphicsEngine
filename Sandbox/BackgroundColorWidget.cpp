#include "BackgroundColorWidget.h"

#include "imgui.h"

#include "glm/gtc/type_ptr.hpp"

#include "GraphicsEngine/IEngine.h"

BackgroundColorWidget::BackgroundColorWidget(GLFWwindowSharedPtr spWindow, GEengineSharedPtr spEngine)
    : Widget(spWindow, spEngine)
{
    geGetBackgroundColor(m_Color);
}

void BackgroundColorWidget::Iterate()
{
    ImGui::Begin("Background Color", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::ColorEdit4("MyColor##2f", m_Color, ImGuiColorEditFlags_Float))
    {
        geSetBackgroundColor(m_Color);
    }

    ImGui::End();
}

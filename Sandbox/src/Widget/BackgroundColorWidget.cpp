#include "BackgroundColorWidget.h"

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/Types.h"

BackgroundColorWidget::BackgroundColorWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine)
{
  graphics_engine::Types::Color color = spEngine->GetBackgroundColor();
    m_Color[0] = color.r;
    m_Color[1] = color.g;
    m_Color[2] = color.b;
}

void BackgroundColorWidget::Iterate(bool* pShow)
{
    ImGui::Begin("Background Color", pShow, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::ColorEdit4("##2f", m_Color.data(), ImGuiColorEditFlags_Float))
    {
      graphics_engine::Types::Color color;
        color.r = m_Color[0];
        color.g = m_Color[1];
        color.b = m_Color[2];
        color.a = 1.f;
        
        GetEngine()->SetBackgroundColor(color);
    }

    ImGui::End();
}

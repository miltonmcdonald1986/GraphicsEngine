#include "BackgroundColorWidget.h"

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/Types.h"

BackgroundColorWidget::BackgroundColorWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine)
{
    GraphicsEngine::Color color = spEngine->GetBackgroundColor();
    m_Color[0] = color.r;
    m_Color[1] = color.g;
    m_Color[2] = color.b;
}

void BackgroundColorWidget::Iterate()
{
    ImGui::Begin("Background Color", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::ColorEdit4("##2f", m_Color.data(), ImGuiColorEditFlags_Float))
    {
        GraphicsEngine::Color color;
        color.r = m_Color[0];
        color.g = m_Color[1];
        color.b = m_Color[2];
        color.a = 1.f;
        
        m_spEngine->SetBackgroundColor(color);
    }

    ImGui::End();
}

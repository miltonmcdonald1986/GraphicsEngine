#include "BackgroundColorWidget.h"

#include "imgui.h"

#include "GraphicsEngine/GL.h"

using namespace GraphicsEngine;

BackgroundColorWidget::BackgroundColorWidget(std::shared_ptr<GLFWwindow> spWindow, IEngineSharedPtr spEngine)
    : Widget(spWindow, spEngine)
{
    float backgroundColor[4];
    GraphicsEngine::GL::GetFloatv(GraphicsEngine::GL::StateVariable::ColorClearValue, backgroundColor);

    std::copy(backgroundColor, backgroundColor + 4, m_Color);
}

void BackgroundColorWidget::Iterate()
{
    ImGui::Begin("Background Color", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::ColorEdit4("MyColor##2f", m_Color, ImGuiColorEditFlags_Float))
    {
        GraphicsEngine::GL::ClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
    }

    ImGui::End();
}

#include "BackgroundColorWidget.h"

#include "imgui.h"

#include "GLUtilities.h"

BackgroundColorWidget::BackgroundColorWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine)
    : Widget(spWindow, spEngine)
{
    auto optBackgroundColor = GraphicsEngine::GL::Utilities::GetColorClearValue();
    if (optBackgroundColor)
        std::copy(optBackgroundColor->data(), optBackgroundColor->data() + 4, m_Color);
}

void BackgroundColorWidget::Iterate()
{
    ImGui::Begin("Background Color", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::ColorEdit4("MyColor##2f", m_Color, ImGuiColorEditFlags_Float))
        GraphicsEngine::GL::Utilities::ClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    ImGui::End();
}

#include "BackgroundColorWidget.h"

#include "imgui.h"

#include "glm/gtc/type_ptr.hpp"

#include "GraphicsEngine/GL.h"

using namespace GraphicsEngine;

BackgroundColorWidget::BackgroundColorWidget(std::shared_ptr<GLFWwindow> spWindow, GEengineSharedPtr spEngine)
    : Widget(spWindow, spEngine)
{
    glm::vec4 backgroundColor = GraphicsEngine::GL::GetColorClearValue();
    float* pBackgroundColor = glm::value_ptr(backgroundColor);
    std::copy(pBackgroundColor, pBackgroundColor + 4, m_Color);
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

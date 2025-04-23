#include "DearImGuiDemoWindowWidget.h"

DearImGuiDemoWindowWidget::DearImGuiDemoWindowWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine)
{
}

auto DearImGuiDemoWindowWidget::Iterate() -> void
{
    ImGui::ShowDemoWindow();
}

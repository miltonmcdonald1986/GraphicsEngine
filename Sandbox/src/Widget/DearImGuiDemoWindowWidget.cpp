#include "DearImGuiDemoWindowWidget.h"

DearImGuiDemoWindowWidget::DearImGuiDemoWindowWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine)
{
}

auto DearImGuiDemoWindowWidget::Iterate(bool* pShow) -> void
{
    ImGui::ShowDemoWindow(pShow);
}

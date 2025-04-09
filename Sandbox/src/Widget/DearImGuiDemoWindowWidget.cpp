#include "DearImGuiDemoWindowWidget.h"

#include "imgui.h"

DearImGuiDemoWindowWidget::DearImGuiDemoWindowWidget(GLFWwindow* pWindow, GEengineSharedPtr spEngine)
    : Widget(pWindow, spEngine)
{
}

auto DearImGuiDemoWindowWidget::Iterate() -> void
{
    ImGui::ShowDemoWindow();
}

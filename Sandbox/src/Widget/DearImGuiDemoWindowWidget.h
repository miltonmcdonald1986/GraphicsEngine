#pragma once

#include "Widget.h"

class DearImGuiDemoWindowWidget : public Widget
{
public:
    DearImGuiDemoWindowWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine);
    auto Iterate(bool* pShow) -> void override;
};

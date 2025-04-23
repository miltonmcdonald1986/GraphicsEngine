#pragma once

#include "Widget.h"

class DearImGuiDemoWindowWidget : public Widget
{
public:
    DearImGuiDemoWindowWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine);
    auto Iterate() -> void override;
};

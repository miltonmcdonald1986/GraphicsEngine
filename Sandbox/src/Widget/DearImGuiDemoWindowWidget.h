#pragma once

#include "GraphicsEngine/GraphicsEngineFwd.h"

#include "Widget.h"

class DearImGuiDemoWindowWidget : public Widget
{
public:
    DearImGuiDemoWindowWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine);
    virtual auto Iterate() -> void override;
};

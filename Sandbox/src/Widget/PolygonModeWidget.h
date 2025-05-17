#pragma once

#include "Widget.h"

class PolygonModeWidget : public Widget
{
public:
    PolygonModeWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine);

    auto Iterate(bool* pShow) -> void override;

private:
    int m_Mode = 0;
};

using PolygonModeWidgetPtr = std::shared_ptr<PolygonModeWidget>;
auto CreatePolygonModeWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine) -> PolygonModeWidgetPtr;

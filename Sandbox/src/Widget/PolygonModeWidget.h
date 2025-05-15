#pragma once

#include "Widget.h"

class PolygonModeWidget : public Widget
{
public:
    PolygonModeWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine);

    auto Iterate(bool* pShow) -> void override;

private:
    int m_Mode = 0;
};

using PolygonModeWidgetPtr = std::shared_ptr<PolygonModeWidget>;
auto CreatePolygonModeWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine) -> PolygonModeWidgetPtr;

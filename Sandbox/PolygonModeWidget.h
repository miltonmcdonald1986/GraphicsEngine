#pragma once

#include "Widget.h"

class PolygonModeWidget : public Widget
{
public:
    PolygonModeWidget(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine);

    virtual auto Iterate() -> void override;

private:
    int m_Mode = 0;
};

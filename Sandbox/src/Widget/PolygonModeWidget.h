#pragma once

#include "Widget.h"

class PolygonModeWidget : public Widget
{
public:
    PolygonModeWidget(GLFWwindow* spWindow, GraphicsEngine::IEnginePtr spEngine);

    virtual auto Iterate() -> void override;

private:
    int m_Mode = 0;
};

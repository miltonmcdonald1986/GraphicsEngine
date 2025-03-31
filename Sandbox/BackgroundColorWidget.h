#pragma once

#include "Widget.h"

class BackgroundColorWidget : public Widget
{
public:
    BackgroundColorWidget(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine);

    virtual auto Iterate() -> void override;

private:
    float m_Color[4] = { 0.f, 0.f, 0.f, 1.f };
};

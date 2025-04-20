#pragma once

#include "GraphicsEngine/GraphicsEngineFwd.h"

#include "Widget.h"

class BackgroundColorWidget : public Widget
{
public:
    BackgroundColorWidget(GLFWwindow* spWindow, GraphicsEngine::IEnginePtr spEngine);
    virtual auto Iterate() -> void override;

private:
    float m_Color[4] = { 0.f, 0.f, 0.f, 1.f };
};

#pragma once

#include <array>

#include "Widget.h"

class BackgroundColorWidget : public Widget
{
public:
    BackgroundColorWidget(GLFWwindow* spWindow, GraphicsEngine::IEnginePtr spEngine);
    auto Iterate(bool* pShow) -> void override;

private:
    std::array<float, 4> m_Color = { 0.f, 0.f, 0.f, 1.f };
};

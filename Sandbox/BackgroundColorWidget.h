#pragma once

#include "Header.h"
#include "Widget.h"

class BackgroundColorWidget : public Widget
{
public:
    BackgroundColorWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

    virtual auto Iterate() -> void override;

private:
    float m_Color[4] = { 0.f, 0.f, 0.f, 1.f };
};

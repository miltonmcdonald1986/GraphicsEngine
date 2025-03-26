#pragma once

#include "Header.h"
#include "Widget.h"

class PolygonModeWidget : public Widget
{
public:
    PolygonModeWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

    virtual auto Iterate() -> void override;

private:
    int m_Mode = 0;
};

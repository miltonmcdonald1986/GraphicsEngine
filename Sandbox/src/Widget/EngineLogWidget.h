#pragma once

#include "Widget.h"

#include "fwd.h"

class EngineLogWidget : public Widget
{
public:

    EngineLogWidget(GLFWwindow* spWindow, GraphicsEngine::IEnginePtr spEngine);

    virtual auto Iterate() -> void override;

private:

    GraphicsEngine::ILogPtr m_spLog = nullptr;
    int m_LogLevel = 0;
};

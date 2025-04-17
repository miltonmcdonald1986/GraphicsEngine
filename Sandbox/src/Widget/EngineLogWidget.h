#pragma once

#include "Widget.h"

#include "IEngine.h"
#include "ILog.h"

class EngineLogWidget : public Widget
{
public:

    EngineLogWidget(GLFWwindow* spWindow, GraphicsEngine::IEnginePtr spEngine);

    virtual auto Iterate() -> void override;

private:

    GraphicsEngine::ILogPtr m_spLog = nullptr;
    int m_LogLevel = static_cast<int>(GraphicsEngine::LogLevel::Info);
};

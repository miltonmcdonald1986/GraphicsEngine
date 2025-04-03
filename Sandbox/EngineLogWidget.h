#pragma once

#include "Widget.h"

#include "GraphicsEngine/Log.h"

class EngineLogWidget : public Widget
{
public:

    EngineLogWidget(GLFWwindowSharedPtr spWindow, GEengineSharedPtr spEngine);

    virtual auto Iterate() -> void override;

private:

    int m_LogLevel = static_cast<int>(GraphicsEngine::Log::LogLevel::Warn);
};

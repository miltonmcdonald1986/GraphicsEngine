#pragma once

#include "Widget.h"

#include "IEngine.h"

class EngineLogWidget : public Widget
{
public:

    EngineLogWidget(GLFWwindow* spWindow, GEengineSharedPtr spEngine);

    virtual auto Iterate() -> void override;

private:

    int m_LogLevel = GE_LOG_LEVEL_INFO;
};

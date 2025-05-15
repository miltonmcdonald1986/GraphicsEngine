#pragma once

#include "Widget.h"

#include "fwd.h"

class EngineLogWidget : public Widget
{
public:

    EngineLogWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine);

    auto Iterate(bool* pShow) -> void override;

private:

    GraphicsEngine::ILogPtr m_spLog = nullptr;
    int m_LogLevel = 0;
};

using EngineLogWidgetPtr = std::shared_ptr<EngineLogWidget>;
auto CreateEngineLogWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine) -> EngineLogWidgetPtr;

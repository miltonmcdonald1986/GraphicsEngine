#pragma once

#include "Widget.h"

#include "fwd.h"

class EngineLogWidget : public Widget
{
public:

    EngineLogWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine);

    auto Iterate(bool* pShow) -> void override;

private:

  graphics_engine::ILogPtr m_spLog = nullptr;
    int m_LogLevel = 0;
};

using EngineLogWidgetPtr = std::shared_ptr<EngineLogWidget>;
auto CreateEngineLogWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine) -> EngineLogWidgetPtr;

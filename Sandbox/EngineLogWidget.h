#pragma once

#include "Header.h"
#include "Widget.h"

class EngineLogWidget : public Widget
{
public:

    EngineLogWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

    virtual auto Iterate() -> void override;

private:

    int m_LogLevel = static_cast<int>(GraphicsEngine::Log::Utilities::LogLevel::Warn);
};

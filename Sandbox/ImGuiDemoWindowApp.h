#pragma once

#include "App.h"

class ImGuiDemoWindowApp : public App
{
public:

	ImGuiDemoWindowApp(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine);

	virtual auto Run() -> void override;

};

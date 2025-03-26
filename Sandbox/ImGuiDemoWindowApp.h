#pragma once

#include "Header.h"
#include "App.h"

class ImGuiDemoWindowApp : public App
{
public:

	ImGuiDemoWindowApp(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

	virtual auto Run() -> void override;

};

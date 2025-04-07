#pragma once

#include "App.h"

class ImGuiDemoWindowApp : public App
{
public:
	ImGuiDemoWindowApp(GLFWwindow* pWindow);
	virtual ~ImGuiDemoWindowApp() = default;
	virtual auto GetUserDataPointer() -> void* override;
	virtual auto Run() -> void override;
};

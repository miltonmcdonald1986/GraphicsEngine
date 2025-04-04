#pragma once

#include "App.h"

class ImGuiDemoWindowApp : public App
{
public:

	ImGuiDemoWindowApp(GLFWwindowSharedPtr spWindow);
	virtual auto GetUserDataPointer() -> void* override;
	virtual auto Run() -> void override;
};

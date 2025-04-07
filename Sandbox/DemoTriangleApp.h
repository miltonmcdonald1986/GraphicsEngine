#pragma once

#include "App.h"

class DemoTriangleApp : public App
{
public:
	DemoTriangleApp(GLFWwindow* pWindow);
	virtual ~DemoTriangleApp() override = default;
	virtual auto GetUserDataPointer(void) -> void* override;
	virtual auto Run() -> void override;
};

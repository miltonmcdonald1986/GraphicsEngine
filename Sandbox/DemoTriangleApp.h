#pragma once

#include "App.h"

class Widget;

class DemoTriangleApp : public App
{
public:

	DemoTriangleApp(GLFWwindowSharedPtr spWindow);
	~DemoTriangleApp();
	virtual auto GetUserDataPointer(void) -> void* override;
	virtual auto Run() -> void override;
};

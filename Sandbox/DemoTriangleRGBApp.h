#pragma once

#include "App.h"

class Widget;

class DemoTriangleRGBApp : public App
{
public:

	DemoTriangleRGBApp(GLFWwindowSharedPtr spWindow);

	virtual auto Run() -> void override;
};

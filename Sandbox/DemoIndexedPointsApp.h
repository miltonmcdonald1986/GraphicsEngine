#pragma once

#include "App.h"

class DemoIndexedPointsApp : public App
{
public:

	DemoIndexedPointsApp(GLFWwindow* spWindow);
	virtual auto GetUserDataPointer() -> void* override;
	virtual auto Run() -> void override;
};

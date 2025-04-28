#pragma once

#include "App.h"

class DemoCoordinateSystemsApp : public App
{
public:
	explicit DemoCoordinateSystemsApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;
};

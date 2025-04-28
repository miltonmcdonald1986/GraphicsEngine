#pragma once

#include "App.h"

class DemoCoordinateSystemsMultipleApp : public App
{
public:
	explicit DemoCoordinateSystemsMultipleApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;
};

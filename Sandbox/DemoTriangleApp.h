#pragma once

#include "App.h"

class Widget;

class DemoTriangleApp : public App
{
public:

	DemoTriangleApp(GLFWwindowSharedPtr spWindow);
	~DemoTriangleApp();

	virtual auto Run() -> void override;

private:
	
	bool m_Running = true;
};

#pragma once

#include "App.h"

class Widget;

class DemoTriangleRGBApp : public App
{
public:

	DemoTriangleRGBApp(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine);

	virtual auto Run() -> void override;

private:

	void Render() const;

	unsigned int m_VAO = 0;
};

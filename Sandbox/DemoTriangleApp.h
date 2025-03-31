#pragma once

#include "App.h"

class Widget;

class DemoTriangleApp : public App
{
public:

	DemoTriangleApp(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine);

	virtual auto Run() -> void override;

private:

	void Render() const;

	unsigned int m_VAO = 0;
};

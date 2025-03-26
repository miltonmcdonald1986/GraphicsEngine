#pragma once

#include "Header.h"
#include "App.h"

class Widget;

class DemoTriangleApp : public App
{
public:

	DemoTriangleApp(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

	virtual auto Run() -> void override;

private:

	void Render() const;

	unsigned int m_VAO = 0;
};

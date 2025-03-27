#pragma once

#include "Header.h"
#include "App.h"

class Widget;

class DemoIndexedPointsApp : public App
{
public:

	DemoIndexedPointsApp(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

	virtual auto Run() -> void override;

private:

	void Render() const;

	std::vector<unsigned int> m_Indices;
	unsigned int m_VAO = 0;
};

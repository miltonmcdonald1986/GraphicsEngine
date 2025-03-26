#pragma once

#include "Header.h"
#include "Widget.h"

#include <memory>
#include <vector>

class App
{
public:

	App(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);
	virtual ~App();

	virtual auto Run() -> void = 0;

protected:

	auto IterateWidgets() -> void;

	std::shared_ptr<GLFWwindow> m_spWindow;
	std::shared_ptr<GraphicsEngine::Engine> m_spEngine;
	std::vector<std::unique_ptr<Widget> > m_Widgets;
};

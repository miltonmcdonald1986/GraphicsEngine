#pragma once

#include "Header.h"

class Widget
{
public:

	Widget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

	virtual auto Iterate() -> void = 0;

protected:

	std::shared_ptr<GLFWwindow> m_spWindow;
	std::shared_ptr<GraphicsEngine::Engine> m_spEngine;

};

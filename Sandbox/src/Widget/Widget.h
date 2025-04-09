#pragma once

#include <memory>

#include "GLFW/glfw3.h"

#include "fwd.h"

class Widget
{
public:

	Widget(GLFWwindow* spWindow, GEengineSharedPtr spEngine);
	virtual ~Widget() = default;
	virtual auto Iterate() -> void = 0;

protected:

	GLFWwindow* m_pWindow;
	GEengineSharedPtr m_spEngine;

};

using WidgetUniquePointer = std::unique_ptr<Widget>;

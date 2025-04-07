#pragma once

#include <vector>

#include "GLFW/glfw3.h"

#include "fwd.h"

class App
{
public:

	App(GLFWwindow* pWindow);
	virtual ~App();
	virtual auto GetUserDataPointer() -> void* = 0;
	virtual auto Run() -> void = 0;

protected:

	auto IterateWidgets() -> void;

	bool m_Running = true;
	GLFWwindow* m_pWindow;
	GEengineSharedPtr m_spEngine;
	std::vector<WidgetUniquePointer> m_Widgets;
};

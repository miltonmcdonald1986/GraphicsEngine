#pragma once

#include <vector>

#include "fwd.h"

class App
{
public:

	App(GLFWwindowSharedPtr spWindow);
	virtual ~App();

	virtual auto Run() -> void = 0;

protected:

	auto IterateWidgets() -> void;

	GLFWwindowSharedPtr m_spWindow;
	GEengineSharedPtr m_spEngine;
	std::vector<WidgetUniquePointer> m_Widgets;
};

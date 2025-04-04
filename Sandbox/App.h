#pragma once

#include <vector>

#include "fwd.h"

class App
{
public:

	App(GLFWwindowSharedPtr spWindow);
	virtual ~App();
	virtual auto GetUserDataPointer() -> void* = 0;
	virtual auto Run() -> void = 0;

protected:

	auto IterateWidgets() -> void;

	bool m_Running = true;
	GLFWwindowSharedPtr m_spWindow;
	GEengineSharedPtr m_spEngine;
	std::vector<WidgetUniquePointer> m_Widgets;
};

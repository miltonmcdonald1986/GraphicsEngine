#pragma once

#include <memory>

#include "fwd.h"

class Widget
{
public:

	Widget(GLFWwindowSharedPtr spWindow, GEengineSharedPtr spEngine);

	virtual auto Iterate() -> void = 0;

protected:

	GLFWwindowSharedPtr m_spWindow;
	GEengineSharedPtr m_spEngine;

};

using WidgetUniquePointer = std::unique_ptr<Widget>;

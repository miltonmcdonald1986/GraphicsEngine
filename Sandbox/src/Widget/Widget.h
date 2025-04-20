#pragma once

#include <memory>

#include "GraphicsEngine/GraphicsEngineFwd.h"

#include "GLFW/glfw3.h"

#include "fwd.h"

class Widget
{
public:

	Widget(GLFWwindow* spWindow, GraphicsEngine::IEnginePtr spEngine);
	virtual ~Widget() = default;
	virtual auto Iterate() -> void = 0;

protected:

	GLFWwindow* m_pWindow;
	GraphicsEngine::IEnginePtr m_spEngine;

};

using WidgetUniquePointer = std::unique_ptr<Widget>;

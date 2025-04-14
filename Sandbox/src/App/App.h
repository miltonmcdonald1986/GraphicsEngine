#pragma once

#include <vector>

#include "GLFW/glfw3.h"

#include "fwd.h"

#include "GraphicsEngineFwd.h"

class App
{
public:

	App(GLFWwindow* pWindow);
	virtual ~App();
	virtual auto GetUserDataPointer() -> void*;
	virtual auto RenderDockSpace() -> void;
	virtual auto Run() -> void;

protected:

	auto IterateWidgets() -> void;

	bool m_Running = true;
	GLFWkeyfun m_PrevKeyCallback;
	GLFWwindow* m_pWindow;
	GraphicsEngine::IEnginePtr m_spEngine;
	std::vector<WidgetUniquePointer> m_Widgets;
	void* m_PrevUserPointer = nullptr;
};

#pragma once

#include "fwd.h"

class App
{
public:

	explicit App(GLFWwindow* pWindow);
	virtual ~App();
	virtual auto GetUserDataPointer() -> void*;
	virtual auto Iterate() -> void;
	virtual auto RenderDockSpace() -> void;
	virtual auto Run() -> void;

protected:

	auto IterateWidgets() -> void;

	bool m_Running = true;
	GLFWkeyfun m_PrevKeyCallback;
	GLFWwindow* m_pWindow;
	GraphicsEngine::IEnginePtr m_spEngine;
	Widgets m_Widgets;
	void* m_PrevUserPointer = nullptr;
};

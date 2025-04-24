#pragma once

#include "fwd.h"

#include "GraphicsEngine/IEngine.h"

class App
{
public:

	explicit App(GLFWwindow* pWindow);
	virtual ~App();
	virtual auto Iterate() -> void;
	virtual auto OnFramebufferSize(int width, int height) -> void;
	virtual auto RenderDockSpace() -> void;
	virtual auto Run() -> void;
	virtual auto SetIsRunning(bool isRunning) -> void;

protected:

	auto GetEngine() const -> GraphicsEngine::IEnginePtr;
	auto GetIsRunning() const -> bool;
	auto GetWidgets() -> Widgets&;
	auto GetWindow() const -> GLFWwindow*;
	auto IterateWidgets() const -> void;

private:

	bool m_Running = true;
	GLFWkeyfun m_PrevKeyCallback;
	GLFWwindow* m_pWindow;
	GraphicsEngine::IEnginePtr m_spEngine = nullptr;
	Widgets m_Widgets;
	void* m_PrevUserPointer = nullptr;	//NOSONAR: GLFW does not have a proper type for this
};

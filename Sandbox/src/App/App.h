#pragma once

#include "fwd.h"

class App
{
public:

	explicit App(GLFWwindow* pWindow);
	virtual ~App();
	virtual auto GetUserDataPointer() -> std::byte*;
	virtual auto Iterate() -> void;
	virtual auto RenderDockSpace() -> void;
	virtual auto Run() -> void;

protected:

	auto GetEngine() const -> GraphicsEngine::IEnginePtr;
	auto GetIsRunning() const -> bool;
	auto GetWidgets() -> Widgets&;
	auto GetWindow() const -> GLFWwindow*;
	auto IterateWidgets() const -> void;
	auto SetIsRunning(bool isRunning) -> void;

private:

	bool m_Running = true;
	GLFWkeyfun m_PrevKeyCallback;
	GLFWwindow* m_pWindow;
	GraphicsEngine::IEnginePtr m_spEngine = nullptr;
	Widgets m_Widgets;
	void* m_PrevUserPointer = nullptr;	//NOSONAR: GLFW does not have a proper type for this
};

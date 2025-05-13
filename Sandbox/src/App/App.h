#pragma once

#include "fwd.h"

#include "GraphicsEngine/IEngine.h"

class EngineLogWidget;
using EngineLogWidgetPtr = std::shared_ptr<EngineLogWidget>;

class PolygonModeWidget;
using PolygonModeWidgetPtr = std::shared_ptr<PolygonModeWidget>;

class ShaderWidget;
using ShaderWidgetPtr = std::shared_ptr<ShaderWidget>;

class App
{
public:

	explicit App(GLFWwindow* pWindow);
	virtual ~App();
	
	virtual auto Iterate() -> void;
	virtual auto RenderDockSpace() -> void;
	virtual auto Run() -> void;
	virtual auto SetIsRunning(bool isRunning) -> void;

	auto GetEngine() const->GraphicsEngine::IEnginePtr;

protected:

	auto GetIsRunning() const -> bool;
	auto GetWidgets() -> Widgets&;
	auto GetWindow() const -> GLFWwindow*;
	auto IterateWidgets() -> void;

private:

	GLFWframebuffersizefun m_pPrevFramebufferSizeCallback = nullptr;
	bool m_Running = true;
	GLFWkeyfun m_PrevKeyCallback;
	GLFWwindow* m_pWindow;
	GraphicsEngine::IEnginePtr m_spEngine = nullptr;
	EngineLogWidgetPtr m_spWidgetEngineLog = nullptr;
	PolygonModeWidgetPtr m_spWidgetPolygonMode = nullptr;
	ShaderWidgetPtr m_spWidgetShader = nullptr;
	Widgets m_Widgets;
	void* m_PrevUserPointer = nullptr;	//NOSONAR: GLFW does not have a proper type for this
	bool m_ShowEngineLogWidget = false;
	bool m_ShowPolygonModeWidget = false;
	bool m_ShowShaderWidget = false;
};

namespace AppCallbacks
{

	void OnFramebufferSize(GLFWwindow* pWindow, int newWidth, int newHeight);

}

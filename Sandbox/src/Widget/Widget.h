#pragma once

#include "fwd.h"

class Widget
{
public:

	Widget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine);
	virtual ~Widget() = default;
	virtual auto Iterate(bool* pShow = nullptr) -> void = 0;

protected:

	auto GetWindow() const -> GLFWwindow*;
	auto GetEngine() const -> GraphicsEngine::IEnginePtr;

private:

	GLFWwindow* m_pWindow;
	GraphicsEngine::IEnginePtr m_spEngine;

};

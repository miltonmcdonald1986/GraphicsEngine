#pragma once

#include "fwd.h"

class Widget
{
public:

	Widget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine);
	virtual ~Widget() = default;
	virtual auto Iterate(bool* pShow = nullptr) -> void = 0;

protected:

	auto GetWindow() const -> GLFWwindow*;
	auto GetEngine() const ->graphics_engine::IEnginePtr;

private:

	GLFWwindow* m_pWindow;
	graphics_engine::IEnginePtr m_spEngine;

};

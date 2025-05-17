#include "Widget.h"

Widget::Widget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine)
	: m_pWindow(pWindow),
	  m_spEngine(spEngine)
{
}

auto Widget::GetWindow() const -> GLFWwindow*
{
	return m_pWindow;
}

auto Widget::GetEngine() const -> graphics_engine::IEnginePtr
{
	return m_spEngine;
}

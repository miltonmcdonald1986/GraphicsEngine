#include "Widget.h"

Widget::Widget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
	: m_pWindow(pWindow),
	  m_spEngine(spEngine)
{
}

auto Widget::GetWindow() const -> GLFWwindow*
{
	return m_pWindow;
}

auto Widget::GetEngine() const -> GraphicsEngine::IEnginePtr
{
	return m_spEngine;
}

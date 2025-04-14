#include "Widget.h"

Widget::Widget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
	: m_pWindow(pWindow),
	  m_spEngine(spEngine)
{
}

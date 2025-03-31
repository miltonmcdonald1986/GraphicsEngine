#include "Widget.h"

Widget::Widget(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine)
	: m_spWindow(spWindow),
	  m_spEngine(spEngine)
{
}

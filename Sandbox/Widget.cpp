#include "Widget.h"

Widget::Widget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine)
	: m_spWindow(spWindow),
	  m_spEngine(spEngine)
{
}

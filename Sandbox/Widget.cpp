#include "Widget.h"

using namespace GraphicsEngine;

Widget::Widget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<Engine> spEngine)
	: m_spWindow(spWindow),
	  m_spEngine(spEngine)
{
}

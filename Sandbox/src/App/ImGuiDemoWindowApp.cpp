#include "ImGuiDemoWindowApp.h"

#include "DearImGuiDemoWindowWidget.h"

ImGuiDemoWindowApp::ImGuiDemoWindowApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	m_Widgets.push_back(WidgetPtr(new DearImGuiDemoWindowWidget(m_pWindow, m_spEngine)));
}

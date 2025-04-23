#include "ImGuiDemoWindowApp.h"

#include "DearImGuiDemoWindowWidget.h"

ImGuiDemoWindowApp::ImGuiDemoWindowApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	GetWidgets().push_back(std::make_unique<DearImGuiDemoWindowWidget>(pWindow, GetEngine()));
}

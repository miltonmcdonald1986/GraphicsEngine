#include "MainLoop.h"

#include "GLFW/glfw3.h"

#include "Apps.h"
#include "DemoIndexedPointsApp.h"
#include "DemoTriangleApp.h"
#include "DemoTriangleRGBApp.h"
#include "ImGuiDemoWindowApp.h"
#include "MainMenuApp.h"

namespace
{

	auto OnKey(GLFWwindow* pWindow, int key, int /*scancode*/, int action, int /*mods*/) -> void
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
	}

}

auto RunApp(GLFWwindow* pWindow, Apps whichApp)
{
	switch (whichApp)
	{
	case Apps::DemoTriangleBasic:
	{
		DemoTriangleApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoTriangleRGB:
	{
		DemoTriangleRGBApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoIndexedPoints:
	{
		DemoIndexedPointsApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::ImGuiDemoWindow:
	{
		ImGuiDemoWindowApp app(pWindow);
		app.Run();
		break;
	}
	}
}

auto MainLoop(GLFWwindow* pWindow) -> void
{
	glfwSetKeyCallback(pWindow, OnKey);

	bool appSelected = false;
	int selectedItem = 0;
	while (!glfwWindowShouldClose(pWindow))
	{
		if (!appSelected)
		{
			MainMenuApp mainMenuApp(pWindow);
			mainMenuApp.Run();
			std::tie(appSelected, selectedItem) = mainMenuApp.GetResults();
		}
		else
		{
			RunApp(pWindow, static_cast<Apps>(selectedItem));
			appSelected = false;
		}

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}
}

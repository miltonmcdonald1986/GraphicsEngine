#include "MainLoop.h"

#include "Apps.h"
#include "DemoContainerApp.h"
#include "DemoContainerRGBApp.h"
#include "DemoCoordinateSystemsApp.h"
#include "DemoCoordinateSystemsDepthApp.h"
#include "DemoCoordinateSystemsMultipleApp.h"
#include "DemoFlashingGreenTriangleApp.h"
#include "DemoFlyCameraApp.h"
#include "DemoIndexedPointsApp.h"
#include "DemoTexturedTriangleApp.h"
#include "DemoTexturesCombinedApp.h"
#include "DemoTransformationsApp.h"
#include "DemoTriangleApp.h"
#include "DemoTriangleRGBApp.h"
#include "ImGuiDemoWindowApp.h"
#include "MainMenuApp.h"
#include "TestApp.h"

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
	case Apps::Test:
	{
		TestApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoFlyCameraApp:
	{
		DemoFlyCameraApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoCoordianteSystemsMultiple:
	{
		DemoCoordinateSystemsMultipleApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoCoordinateSystemsDepth:
	{
		DemoCoordinateSystemsDepthApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoCoordinateSystems:
	{
		DemoCoordinateSystemsApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoTransformations:
	{
		DemoTransformationsApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoTexturesCombined:
	{
		DemoTexturesCombinedApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoContainerRGB:
	{
		DemoContainerRGBApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoContainer:
	{
		DemoContainerApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoTexturedTriangle:
	{
		DemoTexturedTriangleApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::DemoFlashingGreenTriangle:
	{
		DemoFlashingGreenTriangleApp app(pWindow);
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
	case Apps::DemoTriangle:
	{
		DemoTriangleApp app(pWindow);
		app.Run();
		break;
	}
	case Apps::ImGuiDemoWindow:
	{
		ImGuiDemoWindowApp app(pWindow);
		app.Run();
		break;
	}
	default:
		break;
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

#include "MainLoop.h"

#pragma warning(push)
#pragma warning(disable : 4244)
#include <algorithm>
#pragma warning(pop)
#include <iterator>
#include <map>
#include <vector>

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "DemoTriangleApp.h"
#include "ImGuiDemoWindowApp.h"

namespace
{

	auto OnKey(GLFWwindow* pWindow, int key, int /*scancode*/, int action, int /*mods*/) -> void
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
	}

}

enum class Apps : int
{
	DemoTriangleBasic = 0,
	DemoTriangleRGB,
	DemoIndexedPoints,
	ImGuiDemoWindow,
	NumApps
};

using AppInfo_t = std::pair<Apps, const char*>;
using AppMap_t = std::map<Apps, const char*>;
const AppMap_t AppMap = 
{
	std::make_pair(Apps::DemoTriangleBasic, "Demo triangle"),
	std::make_pair(Apps::DemoTriangleRGB, "Demo triangle rgb"),
	std::make_pair(Apps::DemoIndexedPoints, "Demo indexed points"),
	std::make_pair(Apps::ImGuiDemoWindow, "Demo \"Dear ImGui\" window"),
};

using AppNames_t = std::vector<const char*>;
const AppNames_t AppNames = ([](const AppMap_t& appMap) -> AppNames_t 
	{
		AppNames_t appNames;
		std::transform(appMap.begin(), appMap.end(), std::back_inserter(appNames), [](const AppInfo_t& appInfo) 
			{
				return appInfo.second; 
			});

		return appNames;
	})(AppMap);

auto MainMenu(bool& appSelected, int& selectedItem) -> bool
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::OpenPopup("Main Menu");

	// Ensure the popup fills the entire screen
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 displaySize = io.DisplaySize;
	ImGui::SetNextWindowSize(displaySize);
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar))
	{
		// Calculate position to center the contents
		ImVec2 contentSize = ImVec2(300, 200); // Define the size of your content
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 centerPos = ImVec2((windowSize.x - contentSize.x) * 0.5f, (windowSize.y - contentSize.y) * 0.5f);

		// Move the cursor to the calculated center position
		ImGui::SetCursorPos(centerPos);

		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Graphics Engine Sandbox").x) * 0.5f);
		ImGui::Text("Graphics Engine Sandbox");
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Please make a selection").x) * 0.5f);
		ImGui::Text("Please make a selection");
		ImGui::SetNextWindowSize(ImVec2(400, static_cast<float>(Apps::NumApps) * ImGui::GetTextLineHeight() + 2 * ImGui::GetStyle().ItemSpacing.y + 4 * ImGui::GetStyle().FramePadding.y));
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 400) * 0.5f);
		ImGui::ListBox("##Items", &selectedItem, AppNames.data(), static_cast<int>(AppNames.size()));
		float windowWidth = ImGui::GetWindowSize().x;
		float buttonWidth = 100.0f; // Set your button width
		ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
		if (ImGui::Button("Run", ImVec2(buttonWidth, 30.f)))
		{
			ImGui::CloseCurrentPopup();
			appSelected = true;
		}

		ImGui::EndPopup();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return appSelected;
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
		//DemoTriangleRGBApp app(pWindow);
		//app.Run();
		break;
	}
	case Apps::DemoIndexedPoints:
	{
		//DemoIndexedPointsApp app(pWindow);
		//app.Run();
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
			MainMenu(appSelected, selectedItem);
		else
		{
			RunApp(pWindow, static_cast<Apps>(selectedItem));
			appSelected = false;
		}

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}
}

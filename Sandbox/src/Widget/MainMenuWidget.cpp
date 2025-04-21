#include "MainMenuWidget.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

#include "imgui.h"

#include "Apps.h"

using AppInfo_t = std::pair<Apps, const char*>;
using AppMap_t = std::map<Apps, const char*>;
const AppMap_t AppMap =
{
	std::make_pair(Apps::DemoTexturesCombined, "Demo textures combined"),
	std::make_pair(Apps::DemoContainerRGB, "Demo container rgb"),
	std::make_pair(Apps::DemoContainer, "Demo container"),
	std::make_pair(Apps::DemoFlashingGreenTriangle, "Demo flashing green triangle"),
	std::make_pair(Apps::DemoIndexedPoints, "Demo indexed points"),
	std::make_pair(Apps::DemoTexturedTriangle, "Demo textured triangle"),
	std::make_pair(Apps::DemoTriangle, "Demo triangle"),
	std::make_pair(Apps::DemoTriangleRGB, "Demo triangle rgb"),
	std::make_pair(Apps::ImGuiDemoWindow, "Demo \"Dear ImGui\" window")
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

MainMenuWidget::MainMenuWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine, bool& appSelected, int& selectedItem)
	: Widget(pWindow, spEngine)
	, m_AppSelected(appSelected)
	, m_SelectedItem(selectedItem)
{
}

auto MainMenuWidget::Iterate() -> void
{
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
		ImGui::ListBox("##Items", &m_SelectedItem, AppNames.data(), static_cast<int>(AppNames.size()));
		float windowWidth = ImGui::GetWindowSize().x;
		float buttonWidth = 100.0f; // Set your button width
		ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
		if (ImGui::Button("Run", ImVec2(buttonWidth, 30.f)))
		{
			ImGui::CloseCurrentPopup();
			m_AppSelected = true;
		}

		ImGui::EndPopup();
	}
}

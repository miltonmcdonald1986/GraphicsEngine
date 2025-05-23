#include "MainMenuWidget.h"

#include "Apps.h"

using AppInfo_t = std::pair<Apps, const char*>;
using AppMap_t = std::map<Apps, const char*>;
const AppMap_t AppMap =
{
	std::make_pair(Apps::Test, "Test app"),
	std::make_pair(Apps::DemoCoordianteSystemsMultiple, "Demo coordinate systems multiple"),
	std::make_pair(Apps::DemoCoordinateSystemsDepth, "Demo coordinate systems depth"),
	std::make_pair(Apps::DemoCoordinateSystems, "Demo coordinate systems"),
	std::make_pair(Apps::DemoFlyCameraApp, "Demo fly camera"),
	std::make_pair(Apps::DemoTransformations, "Demo transformations"),
	std::make_pair(Apps::DemoTexturesCombined, "Demo textures combined"),
	std::make_pair(Apps::DemoContainerRGB, "Demo container rgb"),
	std::make_pair(Apps::DemoContainer, "Demo container"),
	std::make_pair(Apps::DemoTexturedTriangle, "Demo textured triangle"),
	std::make_pair(Apps::DemoFlashingGreenTriangle, "Demo flashing green triangle"),
	std::make_pair(Apps::DemoTriangleRGB, "Demo triangle rgb"),
	std::make_pair(Apps::DemoIndexedPoints, "Demo indexed points"),
	std::make_pair(Apps::DemoTriangle, "Demo triangle"),
	std::make_pair(Apps::ImGuiDemoWindow, "Demo \"Dear ImGui\" window")
};

using AppNames_t = std::vector<const char*>;
const AppNames_t AppNames = ([](const AppMap_t& appMap)
	{
		AppNames_t appNames;
		std::ranges::transform(appMap, std::back_inserter(appNames), [](const AppInfo_t& appInfo)
			{
				return appInfo.second;
			});

		return appNames;
	})(AppMap);

MainMenuWidget::MainMenuWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine, bool& appSelected, int& selectedItem)
	: Widget(pWindow, spEngine)
	, m_AppSelected(appSelected)
	, m_SelectedItem(selectedItem)
{
}

auto MainMenuWidget::Iterate(bool* /*pShow*/) -> void
{
	ImGui::OpenPopup("Main Menu");

	// Ensure the popup fills the entire screen
	const ImGuiIO& io = ImGui::GetIO();
	ImVec2 displaySize = io.DisplaySize;
	ImGui::SetNextWindowSize(displaySize);
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar))
	{
		float sx = io.DisplaySize.x;
		float sy = io.DisplaySize.y;

		float baseX = 800.f;
		float baseY = 600.f;

		// Calculate position to center the contents
		auto contentSize = ImVec2(300*sx/baseX, 200*sy/baseY); // Define the size of your content
		auto windowSize = ImGui::GetWindowSize();
		auto centerPos = ImVec2((windowSize.x - contentSize.x) * 0.5f, (windowSize.y - contentSize.y) * 0.5f);

		// Move the cursor to the calculated center position
		ImGui::SetCursorPos(centerPos);

		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Graphics Engine Sandbox").x) * 0.5f);
		ImGui::Text("Graphics Engine Sandbox");
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Please make a selection").x) * 0.5f);
		ImGui::Text("Please make a selection");
		ImGui::SetNextWindowSize(ImVec2(400*sx/baseX, static_cast<float>(Apps::NumApps) * ImGui::GetTextLineHeight() + 2 * ImGui::GetStyle().ItemSpacing.y + 4 * ImGui::GetStyle().FramePadding.y));
		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 400*sx/baseX) * 0.5f);
		ImGui::ListBox("##Items", &m_SelectedItem, AppNames.data(), static_cast<int>(AppNames.size()));
		float windowWidth = ImGui::GetWindowSize().x;
		float buttonWidth = 100.0f*sx/baseX; // Set your button width
		ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
		if (ImGui::Button("Run", ImVec2(buttonWidth, 30.f*sy/baseY)))
		{
			ImGui::CloseCurrentPopup();
			m_AppSelected = true;
		}

		ImGui::EndPopup();
	}
}

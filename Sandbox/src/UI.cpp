#include "UI.h"

auto InitializeDearImGui(GLFWwindow* pWindow) -> bool
{
	if (!pWindow)
		return false;

	IMGUI_CHECKVERSION();
	auto pContext = ImGui::CreateContext();
	if (!pContext)
		return false;

	ImGui::SetCurrentContext(pContext);

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Setup Platform/Renderer backends
	if (!ImGui_ImplGlfw_InitForOpenGL(pWindow, true))
		return false;

	if (!ImGui_ImplOpenGL3_Init())
		return false;

#ifdef WIN32
	if (std::filesystem::path fontFilePath("C:\\WINDOWS\\FONTS\\CASCADIAMONO.TTF"); std::filesystem::exists(fontFilePath))
#else
	if (std::filesystem::path fontFilePath("/usr/share/fonts/truetype/cascadia-code/CascadiaMono.ttf"); std::filesystem::exists(fontFilePath))
#endif
	{
		float monScaleX;
		float monScaleY;
		glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &monScaleX, &monScaleY);
		int dpiScale = std::max((int)monScaleX, (int)monScaleY);
		ImGui::GetStyle().ScaleAllSizes((float)dpiScale);
		ImGui::GetIO().FontGlobalScale = (float)dpiScale;
		ImFontConfig fontConfig;
		fontConfig.OversampleH = 2;
		fontConfig.OversampleV = 2;
		fontConfig.SizePixels = 18.0f * static_cast<float>(dpiScale);
		ImGui::GetIO().Fonts->AddFontFromFileTTF(fontFilePath.string().c_str(), 18.0f, &fontConfig);
	}

	return true;
}

auto TerminateDearImGui() -> void
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

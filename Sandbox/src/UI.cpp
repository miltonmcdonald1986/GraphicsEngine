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
		float x;
		float y;
		glfwGetWindowContentScale(pWindow, &x, &y);
		ImGui::GetIO().Fonts->AddFontFromFileTTF(fontFilePath.string().c_str(), std::max(x, y)*18.0f);
	}

	return true;
}

auto TerminateDearImGui() -> void
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

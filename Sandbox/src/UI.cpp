#include "UI.h"

#include <filesystem>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

	std::filesystem::path fontFilePath("C:\\WINDOWS\\FONTS\\CASCADIAMONO.TTF");
	if (std::filesystem::exists(fontFilePath))
		io.Fonts->AddFontFromFileTTF(fontFilePath.string().c_str(), 18);

	return true;
}

auto TerminateDearImGui() -> void
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

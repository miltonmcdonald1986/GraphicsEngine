#include "App.h"

#include "IEngine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Widget.h"

namespace
{

    auto OnKey(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) -> void
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            bool* pRunning = (bool*)glfwGetWindowUserPointer(window);
            *pRunning = false;
        }
    }

}

App::App(GLFWwindow* pWindow)
	: m_pWindow(pWindow),
	  m_spEngine(GraphicsEngine::CreateEngine())
{
    m_PrevUserPointer = glfwGetWindowUserPointer(m_pWindow);
    glfwSetWindowUserPointer(m_pWindow, GetUserDataPointer());

    m_PrevKeyCallback = glfwSetKeyCallback(m_pWindow, OnKey);
}

App::~App()
{
    glfwSetWindowUserPointer(m_pWindow, m_PrevUserPointer);
    glfwSetKeyCallback(m_pWindow, m_PrevKeyCallback);
}

auto App::GetUserDataPointer() -> void*
{
    return static_cast<void*>(&m_Running);
}

auto App::RenderDockSpace() -> void
{
    // Get the size of the full GLFW window
    int window_width, window_height;
    glfwGetWindowSize(m_pWindow, &window_width, &window_height);

    // Create a fullscreen, borderless docking space
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)window_width, (float)window_height));
    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DockSpace Window", nullptr, window_flags);

    // Create the dockspace ID and enable docking
    ImGuiID dockspace_id = ImGui::GetID("MyFullscreenDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();
}

auto App::Run() -> void
{
    while (m_Running)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderDockSpace();

        m_spEngine->Render();

        IterateWidgets();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();

        m_Running = (m_Running && !glfwWindowShouldClose(m_pWindow));
    }
}

auto App::IterateWidgets() -> void
{
	for (auto& upWidget : m_Widgets)
	{
		upWidget->Iterate();
	}
}

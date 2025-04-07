#include "ImGuiDemoWindowApp.h"

#include "GraphicsEngine/IEngine.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

ImGuiDemoWindowApp::ImGuiDemoWindowApp(GLFWwindow* pWindow)
	: App(pWindow)
{
}

auto ImGuiDemoWindowApp::GetUserDataPointer() -> void*
{
    return static_cast<void*>(&m_Running);
}

void ImGuiDemoWindowApp::Run()
{
    auto prevWindowUserPointer = glfwGetWindowUserPointer(m_pWindow);
    glfwSetWindowUserPointer(m_pWindow, GetUserDataPointer());

    auto prevKeyCallback = glfwSetKeyCallback(m_pWindow, OnKey);

    while (m_Running)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        geRender(m_spEngine.get());

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();

        m_Running = m_Running && !glfwWindowShouldClose(m_pWindow);
    }

    glfwSetWindowUserPointer(m_pWindow, prevWindowUserPointer);
    glfwSetKeyCallback(m_pWindow, prevKeyCallback);
}

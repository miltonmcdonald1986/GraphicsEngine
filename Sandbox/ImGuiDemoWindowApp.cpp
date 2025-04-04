#include "ImGuiDemoWindowApp.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ImGuiDemoWindowApp::ImGuiDemoWindowApp(GLFWwindowSharedPtr spWindow)
	: App(spWindow)
{
}

auto ImGuiDemoWindowApp::GetUserDataPointer() -> void*
{
    return static_cast<void*>(&m_Running);
}

void ImGuiDemoWindowApp::Run()
{
    glfwSetWindowUserPointer(m_spWindow.get(), GetUserDataPointer());

    auto NewKeyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                bool* pRunning= (bool*)glfwGetWindowUserPointer(window);
                *pRunning = false;
            }
        };

    glfwSetKeyCallback(m_spWindow.get(), NewKeyCallback);

    while (m_Running)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_spWindow.get());

        /* Poll for and process events */
        glfwPollEvents();

        m_Running = m_Running && !glfwWindowShouldClose(m_spWindow.get());
    }

    glfwSetWindowUserPointer(m_spWindow.get(), nullptr);
    glfwSetKeyCallback(m_spWindow.get(), nullptr);
}

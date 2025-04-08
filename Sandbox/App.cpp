#include "App.h"

#include "GraphicsEngine/IEngine.h"

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
	  m_spEngine(std::shared_ptr<GEengine>(geCreateGraphicsEngine(), [](GEengine* pEngine) { geDestroyGraphicsEngine(pEngine); }))
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

auto App::Run() -> void
{
    while (m_Running)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        geRender(m_spEngine.get());

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

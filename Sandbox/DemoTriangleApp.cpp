#include "DemoTriangleApp.h"

// ALWAYS include GraphicsEngine BEFORE GLFW.
#include "GraphicsEngine/IEngine.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "EngineLogWidget.h"
#include "ShaderWidget.h"

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

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    geGenerateEntity_Triangle3DBasic(m_spEngine.get());
}

auto DemoTriangleApp::GetUserDataPointer(void) -> void*
{
    return static_cast<void*>(&m_Running);
}

auto DemoTriangleApp::Run() -> void
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

        IterateWidgets();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();

        m_Running = (m_Running && !glfwWindowShouldClose(m_pWindow));
    }

    glfwSetWindowUserPointer(m_pWindow, prevWindowUserPointer);
    glfwSetKeyCallback(m_pWindow, prevKeyCallback);
}

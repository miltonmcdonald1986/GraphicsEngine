#include "DemoTriangleRGBApp.h"

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

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindow* spWindow)
    : App(spWindow)
{
    geGenerateEntity_Triangle3DRGB(m_spEngine.get());

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<EngineLogWidget>(new EngineLogWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<ShaderWidget>(new ShaderWidget(spWindow, m_spEngine)));
}

auto DemoTriangleRGBApp::GetUserDataPointer() -> void*
{
    return static_cast<void*>(&m_Running);
}

auto DemoTriangleRGBApp::Run() -> void
{
    glfwSetWindowUserPointer(m_pWindow, (void*)&m_Running);

    auto NewKeyCallback = [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) -> void
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                printf("Escape key pressed. Closing window...\n");
                bool* pRunning = (bool*)glfwGetWindowUserPointer(window);
                *pRunning = false;
            }
        };

    glfwSetKeyCallback(m_pWindow, NewKeyCallback);

    while (m_Running)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        geRender(m_spEngine.get());

        IterateWidgets();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_pWindow);

        /* Poll for and process events */
        glfwPollEvents();

        m_Running = m_Running && !glfwWindowShouldClose(m_pWindow);
    }

    glfwSetWindowUserPointer(m_pWindow, nullptr);
    glfwSetKeyCallback(m_pWindow, nullptr);
}

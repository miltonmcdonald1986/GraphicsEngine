#include "DemoTriangleRGBApp.h"

// ALWAYS include GraphicsEngine BEFORE GLFW.
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/EntityType.h"
#include "GraphicsEngine/Shader.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "EngineLogWidget.h"
#include "ShaderWidget.h"

using namespace GraphicsEngine;

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindowSharedPtr spWindow)
    : App(spWindow)
{
    geGenerateEntity(m_spEngine.get(), GE_ENTITY_TYPE_TRIANGLE_RGB);

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<EngineLogWidget>(new EngineLogWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<ShaderWidget>(new ShaderWidget(spWindow, m_spEngine)));
}

auto DemoTriangleRGBApp::Run() -> void
{
    bool keepGoing = true;

    glfwSetWindowUserPointer(m_spWindow.get(), (void*)&keepGoing);

    auto NewKeyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                printf("Escape key pressed. Closing window...\n");
                bool* pKeepGoing = (bool*)glfwGetWindowUserPointer(window);
                *pKeepGoing = false;
            }
        };

    glfwSetKeyCallback(m_spWindow.get(), NewKeyCallback);

    while (keepGoing)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        geRender(m_spEngine.get());

        IterateWidgets();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_spWindow.get());

        /* Poll for and process events */
        glfwPollEvents();

        keepGoing = keepGoing && !glfwWindowShouldClose(m_spWindow.get());
    }

    glfwSetWindowUserPointer(m_spWindow.get(), nullptr);
    glfwSetKeyCallback(m_spWindow.get(), nullptr);
}

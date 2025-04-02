#include "DemoTriangleApp.h"

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

namespace
{

    auto NewKeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods) -> void
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                printf("Escape key pressed. Closing window...\n");
                bool* pKeepGoing = (bool*)glfwGetWindowUserPointer(window);
                *pKeepGoing = false;
            }
        }
}

DemoTriangleApp::DemoTriangleApp(GLFWwindowSharedPtr spWindow)
    : App(spWindow)
{
    // Init some GLFW stuff
    m_Running = true;
    glfwSetWindowUserPointer(m_spWindow.get(), (void*)&m_Running);
    glfwSetKeyCallback(m_spWindow.get(), NewKeyCallback);

    // Create a triangle.
    m_spEngine->GenerateEntity(GraphicsEngine::EntityType::TriangleBasic);

    // Add an engine log widget.
    m_Widgets.push_back(std::unique_ptr<EngineLogWidget>(new EngineLogWidget(spWindow, m_spEngine)));
}

DemoTriangleApp::~DemoTriangleApp()
{
    glfwSetWindowUserPointer(m_spWindow.get(), nullptr);
    glfwSetKeyCallback(m_spWindow.get(), nullptr);
}

auto DemoTriangleApp::Run() -> void
{
    while (m_Running)
    {
        // Bring ImGui to life.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render the graphics engine
        m_spEngine->Render();

        // Make the imgui widgets do their thing.
        IterateWidgets();

        // Now actually draw the widgets.
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update the window
        glfwSwapBuffers(m_spWindow.get());
        glfwPollEvents();

        // Keep going (or not)
        m_Running = (m_Running && !glfwWindowShouldClose(m_spWindow.get()));
    }
}

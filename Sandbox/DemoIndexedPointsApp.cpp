#include "DemoIndexedPointsApp.h"

// ALWAYS include GraphicsEngine BEFORE GLFW.
#include "GraphicsEngine/GL.h"
#include "GraphicsEngine/IndexedPoints.h"
#include "GraphicsEngine/Shader.h"

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GraphicsEngine/IEngine.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "EngineLogWidget.h"

namespace
{

    auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            printf("Escape key pressed. Closing window...\n");
            bool* pKeepGoing = (bool*)glfwGetWindowUserPointer(window);
            *pKeepGoing = false;
        }
    }

}

DemoIndexedPointsApp::DemoIndexedPointsApp(GLFWwindowSharedPtr spWindow)
    : App(spWindow)
{
    glfwSetWindowUserPointer(m_spWindow.get(), GetUserDataPointer());
    glfwSetKeyCallback(m_spWindow.get(), KeyCallback);

    std::vector<glm::vec3> vertices = {
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f,  0.5f, 0.0f) 
        };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    geGenerateEntity_IndexedPoints3DBasic(m_spEngine.get(), 3*vertices.size()*sizeof(float), &vertices[0][0], indices.size()*sizeof(unsigned int), indices.data());

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<EngineLogWidget>(new EngineLogWidget(spWindow, m_spEngine)));
}

auto DemoIndexedPointsApp::GetUserDataPointer() -> void*
{
    return static_cast<void*>(&m_Running);
}

auto DemoIndexedPointsApp::Run() -> void
{
    glfwSetWindowUserPointer(m_spWindow.get(), GetUserDataPointer());

    auto NewKeyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                printf("Escape key pressed. Closing window...\n");
                bool* pRunning = (bool*)glfwGetWindowUserPointer(window);
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

        geRender(m_spEngine.get());

        IterateWidgets();

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

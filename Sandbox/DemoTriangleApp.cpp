#include "DemoTriangleApp.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "EngineLogWidget.h"

using namespace GraphicsEngine;

DemoTriangleApp::DemoTriangleApp(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<Engine> spEngine)
    : App(spWindow, spEngine)
{
    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<EngineLogWidget>(new EngineLogWidget(spWindow, spEngine)));

    auto optVertexShader = Shader::CompileVertexShader(std::string("#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0"));
    auto optFragmentShader = Shader::CompileFragmentShader(std::string("#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0"));

    if (optVertexShader && optFragmentShader)
    {
        auto optShaderProgram = Shader::LinkProgram({ *optVertexShader, *optFragmentShader });
        if (optShaderProgram)
            glUseProgram(*optShaderProgram);
    }

    GLuint vao = 0;
    if (auto optVAO = m_spEngine->AddTriangle({ glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f) , glm::vec3(0.f, 0.5f, 0.f) }); optVAO)
        m_VAO = *optVAO;
}

auto DemoTriangleApp::Run() -> void
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

        GL::ClearColorBuffers();

        Render();

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

void DemoTriangleApp::Render() const
{
    if (m_VAO == 0)
        return;

    if (!GL::BindVertexArray(m_VAO))
        return;

    GL::DrawArrays(GL::DrawMode::Triangles, 0, 3);
}

#include "DemoTriangleRGBApp.h"

// ALWAYS include GraphicsEngine BEFORE GLFW.
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

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine)
    : App(spWindow, spEngine)
{
    auto optVertexShader = Shader::CompileVertexShader(std::string("#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"

        "out vec3 ourColor;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "}\0"));

    auto optFragmentShader = Shader::CompileFragmentShader(std::string("#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec3 ourColor;\n"

        "uniform vec4 colorStrength;\n"

        "void main()\n"
        "{\n"
        "FragColor = vec4(ourColor.x*colorStrength.x, ourColor.y*colorStrength.y, ourColor.z*colorStrength.z, 1.0*colorStrength.a);\n"
        "}\0"));

    if (optVertexShader && optFragmentShader)
    {
        auto optShaderProgram = Shader::LinkProgram({ *optVertexShader, *optFragmentShader });
        if (optShaderProgram)
        {
            glUseProgram(*optShaderProgram);

            GLint res = glGetUniformLocation(*optShaderProgram, "colorStrength");
            if (GL_ERROR())
                return;

            if (res == -1)
                return;

            glUniform4f(res, 1.f, 1.f, 1.f, 1.f);
            GL_ERROR();
        }
    }

    glGenVertexArrays(1, &m_VAO);
    if (GL_ERROR())
        return;

    glBindVertexArray(m_VAO);
    if (GL_ERROR())
        return;

    std::vector<GLuint> buffers(2);
    glGenBuffers(2, buffers.data());
    if (GL_ERROR())
        return;

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    if (GL_ERROR())
        return;


    //GraphicsEngine::VertexArrayObject vao;
    //m_VAO = vao.GetId();

    std::vector<float> vertices =
    {
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices.data(), GL_STATIC_DRAW);
    if (GL_ERROR())
        return;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    if (GL_ERROR())
        return;

    glEnableVertexAttribArray(0);

    //GraphicsEngine::DataStore verticesDataStore;
    //verticesDataStore.m_NumBytes = static_cast<signed long long int>(vertices.size() * sizeof(float));
    //verticesDataStore.m_pData = vertices.data();

    //GraphicsEngine::Buffer verticesBuffer(verticesDataStore);

    //vao.DefineVertexAttribute(0, verticesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    if (GL_ERROR())
        return;

    std::vector<float> vertexRGBs =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    //GraphicsEngine::DataStore vertexRGBsDataStore;
    //vertexRGBsDataStore.m_NumBytes = static_cast<signed long long int>(vertexRGBs.size() * sizeof(float));
    //vertexRGBsDataStore.m_pData = vertexRGBs.data();

    //GraphicsEngine::Buffer vertexRGBsBuffer(vertexRGBsDataStore);

    //vao.DefineVertexAttribute(1, vertexRGBsBuffer);

    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexRGBs.data(), GL_STATIC_DRAW);
    if (GL_ERROR())
        return;

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    if (GL_ERROR())
        return;

    glEnableVertexAttribArray(1);

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<EngineLogWidget>(new EngineLogWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<ShaderWidget>(new ShaderWidget(spWindow, spEngine)));
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

        glClear(GL_COLOR_BUFFER_BIT);

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

void DemoTriangleRGBApp::Render() const
{
    if (m_VAO == 0)
        return;

    glBindVertexArray(m_VAO);
    if (GL_ERROR())
        return;

    glDrawArrays(GL_TRIANGLES, 0, 3);
    GL_ERROR();
}

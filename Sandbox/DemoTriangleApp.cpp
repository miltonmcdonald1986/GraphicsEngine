#include "DemoTriangleApp.h"

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

DemoTriangleApp::DemoTriangleApp(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine)
    : App(spWindow, spEngine)
{
    auto optVertexShader = Shader::CompileVertexShader(std::string("#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0"));
    auto optFragmentShader = Shader::CompileFragmentShader(std::string("#version 330 core\n"
        "out vec4 FragColor;\n"

        "uniform vec4 ourColor;\n"

        "void main()\n"
        "{\n"
            "FragColor = ourColor;\n"
        "}\n"));

    if (optVertexShader && optFragmentShader)
    {
        auto optShaderProgram = Shader::LinkProgram({ *optVertexShader, *optFragmentShader });
        if (optShaderProgram)
        {
            glUseProgram(*optShaderProgram);

            GLint res = glGetUniformLocation(*optShaderProgram, "ourColor");
            if (GL_ERROR())
                return;

            if (res == -1)
                return;
            
            glUniform4f(res, 1.f, 0.5f, 0.2f, 1.f);
            GL_ERROR();
        }
    }

    std::vector<float> v = {
        -0.5f, -0.5f, 0.f,
         0.5f, -0.5f, 0.f,
         0.f,   0.5f, 0.f
        };

    // Example code to get a model matrix (M) from a list of triangle vertices.
    
    //glm::mat4 A;
    //A[0] = glm::vec4(vertices[0], 1.f);
    //A[1] = glm::vec4(vertices[1], 1.f);
    //A[2] = glm::vec4(vertices[2], 1.f);
    //A[3] = glm::vec4(1.f, 1.f, 1.f, 1.f);
    //auto det = glm::determinant(A);

    //glm::mat4 B;
    //B[0] = glm::vec4(2.f, 2.f, 0.f, 1.f);
    //B[1] = glm::vec4(2.f, 3.f, 0.f, 1.f);
    //B[2] = glm::vec4(3.f, 2.f, 0.f, 1.f);
    //B[3] = glm::vec4(1.f, 1.f, 1.f, 1.f);

    //auto M = B * glm::inverse(A);

    // Local vertices for every triangle are (-0.5, -0.5, 0), (0.5, -0.5, 0), (0, 0.5, 0)
    // We build a local coordinate matrix out of these vertices.
    //glm::mat4 localCoordinates;
    //localCoordinates[0] = glm::vec4(-0.5f, -0.5f, 0.f, 1.f);
    //localCoordinates[1] = glm::vec4(0.5f, -0.5f, 0.f, 1.f);
    //localCoordinates[2] = glm::vec4(0.f, 0.5f, 0.f, 1.f);
    //localCoordinates[3] = glm::vec4(1.f, 1.f, 1.f, 1.f);

    //auto model = M;

    //auto newPositions = model * localCoordinates;

    //auto transformed = 

    GLuint vao;
    glGenVertexArrays(1, &vao);
    if (GL_ERROR())
        return;

    /*DataStore dataStore =
    {
        .m_Target	= GL::BufferBindingTarget::Array,
        .m_NumBytes = static_cast<signed long long int>(v.size()*sizeof(float)),
        .m_pData	= v.data(),
        .m_Usage	= GL::DataUsagePattern::StaticDraw
    };*/

    //Buffer buffer(dataStore);

    GLuint buffer;
    glGenBuffers(1, &buffer);

    glBindVertexArray(vao);
    if (GL_ERROR())
        return;

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), v.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    if (GL_ERROR())
        return;

    glEnableVertexAttribArray(0);
    if (GL_ERROR())
        return;

    m_VAO = vao;


    //GLuint vao = 0;
    //if (auto optVAO = m_spEngine->AddTriangle({ glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f) , glm::vec3(0.f, 0.5f, 0.f) }); optVAO)
        //m_VAO = *optVAO;

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<EngineLogWidget>(new EngineLogWidget(spWindow, spEngine)));
    m_Widgets.push_back(std::unique_ptr<ShaderWidget>(new ShaderWidget(spWindow, spEngine)));
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

void DemoTriangleApp::Render() const
{
    if (m_VAO == 0)
        return;

    glBindVertexArray(m_VAO);
    if (GL_ERROR())
        return;

    glDrawArrays(GL_TRIANGLES, 0, 3);
    GL_ERROR();
}

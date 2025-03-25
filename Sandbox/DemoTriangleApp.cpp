#include "DemoTriangleApp.h"

#include <array>

#include "glm/vec3.hpp"

#include "Engine.h"
#include "ShaderUtilities.h"

DemoTriangleApp::DemoTriangleApp(GraphicsEngine::Engine& engine)
    : m_Engine(engine)
{
    auto optVertexShader = GraphicsEngine::Utilities::CompileVertexShader(std::string("#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0"));
    auto optFragmentShader = GraphicsEngine::Utilities::CompileFragmentShader(std::string("#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0"));

    if (optVertexShader && optFragmentShader)
    {
        auto optShaderProgram = GraphicsEngine::Utilities::LinkProgram({ *optVertexShader, *optFragmentShader });
        if (optShaderProgram)
            glUseProgram(*optShaderProgram);
    }

    GLuint vao = 0;
    if (auto optVAO = m_Engine.AddTriangle({ glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f) , glm::vec3(0.f, 0.5f, 0.f) }); optVAO)
        m_VAO = *optVAO;
}

void DemoTriangleApp::Render()
{
    if (m_VAO == 0)
        return;

    if (!GraphicsEngine::Utilities::BindVertexArray(m_VAO))
        return;

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

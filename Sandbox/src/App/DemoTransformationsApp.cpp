#include "DemoTransformationsApp.h"
#include "DemoCoordinateSystemsUtilities.h"

#include "GraphicsEngine/IEngine.h"

namespace 
{

    void OnFramebufferSize(GLFWwindow* pWindow, int newWidth, int newHeight)
    {
        if (!pWindow)
            return;

		// Do not divide by zero
        if (newHeight == 0)
            return;

        const auto* pApp = static_cast<DemoTransformationsApp*>(glfwGetWindowUserPointer(pWindow));
        if (!pApp)
            return;

        auto spEngine = pApp->GetEngine();
        if (!spEngine)
            return;

        // Make the call to glViewport
        spEngine->ResizeViewport(newWidth, newHeight);

        auto fWidth = std::bit_cast<float>(newWidth);
        auto fHeight = std::bit_cast<float>(newHeight);
        auto pShader = pApp->GetEngine()->GetShaderManager()->GetCurrentShader();
        pShader->SetUniformData("projection", glm::ortho(-fWidth / fHeight, fWidth / fHeight, -1.f, 1.f, -1.f, 1.f));
    }

}

DemoTransformationsApp::DemoTransformationsApp(GLFWwindow* pWindow)
    :   App(pWindow),
        m_pPrevFramebufferSizeCallback(glfwSetFramebufferSizeCallback (pWindow, OnFramebufferSize))
{
    auto spEngine = GetEngine();
    spEngine->SetBackgroundColor(GraphicsEngine::Types::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

    std::vector<glm::vec3> vertices = {
        glm::vec3(-0.5f, -0.5f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f),
        glm::vec3(0.5f, 0.5f, 0.f),
        glm::vec3(-0.5f, 0.5f, 0.f)
    };

    std::vector<glm::vec2> texCoords = {
        glm::vec2(0.f, 0.f),
        glm::vec2(1.f, 0.f),
        glm::vec2(1.f, 1.f),
        glm::vec2(0.f, 1.f)
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    m_pEntity = spEngine->GetEntityManager()->AddEntity({ vertices, texCoords }, indices);

    auto [pShader, textures] = Utilities::PrepareShaderAndTextures(GetEngine());

    m_pEntity->pShader = pShader;
    m_pEntity->textures = textures;

    int width;
    int height;
    glfwGetWindowSize(GetWindow(), &width, &height);
    m_pEntity->pShader->SetUniformData("projection", glm::ortho(-std::bit_cast<float>(width) / std::bit_cast<float>(height), std::bit_cast<float>(width) / std::bit_cast<float>(height), -1.f, 1.f, -1.f, 1.f));
}

DemoTransformationsApp::~DemoTransformationsApp()
{
    glfwSetFramebufferSizeCallback(GetWindow(), m_pPrevFramebufferSizeCallback);
}

auto DemoTransformationsApp::Iterate() -> void
{
    static auto start = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();
    auto diff = now - start;
    auto seconds = std::chrono::duration<float>(diff).count();\

    auto trans = glm::mat4(1.f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.f));
    trans = glm::rotate(trans, seconds, glm::vec3(0.f, 0.f, 1.f));
	glfwSetWindowTitle(GetWindow(), std::format("Seconds: {}", seconds).c_str());
    m_pEntity->modelMatrix = trans;
    m_pEntity->pShader->SetUniformData("view", glm::mat4(1.f));

    App::Iterate();
}

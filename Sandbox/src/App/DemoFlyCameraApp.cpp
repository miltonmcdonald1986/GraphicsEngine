#include "DemoFlyCameraApp.h"

#include "GraphicsEngine/IEntityFactory.h"
#include "GraphicsEngine/ICameraFly.h"

#include "DemoCoordinateSystemsUtilities.h"

namespace
{

    void OnCamera(graphics_engine::IEnginePtr spEngine, const glm::mat4& view, const glm::mat4& projection)
    {
        if (!spEngine)
            return;
        
        auto shader = spEngine->GetShaderManager ()->GetCurrentShader ();
        shader->SetUniformData("view", view);
        shader->SetUniformData("projection", projection);
    }

    void OnScroll(GLFWwindow* pWindow, double xOffset, double yOffset)
    {
        if (ImGui::GetIO().WantCaptureMouse)
        {
            ImGui_ImplGlfw_ScrollCallback(pWindow, xOffset, yOffset);
            return;
        }

        if (!pWindow)
            return;

        const auto* pApp = static_cast<DemoFlyCameraApp*>(glfwGetWindowUserPointer(pWindow));
        if (!pApp)
            return;

        auto spEngine = pApp->GetEngine();
        if (!spEngine)
            return;

        auto spCamera = std::dynamic_pointer_cast<graphics_engine::ICameraFly>(spEngine->GetCamera());
        if (!spCamera)
            return;

        spCamera->Zoom(yOffset);
    }

}

DemoFlyCameraApp::DemoFlyCameraApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    GetEngine()->SetBackgroundColor(graphics_engine::Types::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

    m_pPrevScrollCallback = glfwSetScrollCallback(pWindow, OnScroll);

    // Call this before updating framebuffer stuff since this creates shaders.
    Utilities::CreateTenTexturedCubes(GetEngine());

    auto spCamera = graphics_engine::CreateCameraFly();
    spCamera->SetEye(glm::vec3(0.f, 0.f, 3.f));
    GetEngine()->SetCamera(spCamera);
    spCamera->GetObservable()->AddObserver([this](const glm::mat4& view, const glm::mat4& projection) { OnCamera(GetEngine(), view, projection); });

    int fbWidth;
    int fbHeight;
    glfwGetFramebufferSize(pWindow, &fbWidth, &fbHeight);
    AppCallbacks::OnFramebufferSize(pWindow, fbWidth, fbHeight);
}

DemoFlyCameraApp::~DemoFlyCameraApp()
{
    // Restore previous callback functions.
    glfwSetScrollCallback(GetWindow(), m_pPrevScrollCallback);
}

auto DemoFlyCameraApp::Iterate() -> void
{
    static auto lastFrameTime = glfwGetTime();
    auto thisFrameTime = glfwGetTime();
    auto deltaTime = static_cast<float>(thisFrameTime - lastFrameTime);
    lastFrameTime = thisFrameTime;

    float moveSpeed = 2.f; // inches per second
    float dist = moveSpeed * deltaTime; // inches

    float tiltSpeed = 60.f; // degrees per second
    float angle = tiltSpeed * deltaTime; // degrees

    auto spCamera = std::dynamic_pointer_cast<graphics_engine::ICameraFly>(GetEngine()->GetCamera());
    auto shiftIsPressed = (glfwGetKey(GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(GetWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
    auto ctrlIsPressed = (glfwGetKey(GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS);
    if (glfwGetKey(GetWindow(), GLFW_KEY_LEFT))
    {
        if (ctrlIsPressed)
            spCamera->SetYawIncremental(angle);
        else
            spCamera->Strafe(-1.f * dist * spCamera->GetRight());
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_RIGHT))
    {
        if (ctrlIsPressed)
            spCamera->SetYawIncremental(-1.f * angle);
        else
            spCamera->Strafe(dist * spCamera->GetRight());
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_DOWN))
    {
        if (ctrlIsPressed)
            spCamera->SetPitchIncremental(-1.f * angle);
        else if (shiftIsPressed)
            spCamera->Strafe(-1.f * dist * spCamera->GetFront());
        else
            spCamera->Strafe(-1.f * dist * spCamera->GetUp());
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_UP))
    {
        if (ctrlIsPressed)
            spCamera->SetPitchIncremental(angle);
        else if (shiftIsPressed)
            spCamera->Strafe(dist * spCamera->GetFront());
        else
            spCamera->Strafe(dist * spCamera->GetUp());
    }

    App::Iterate();
}

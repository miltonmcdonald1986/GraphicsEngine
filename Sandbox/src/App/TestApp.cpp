#include "TestApp.h"

#include "GraphicsEngine/IEntityFactory.h"
#include "GraphicsEngine/ICameraFly.h"

#include "glm/ext/matrix_clip_space.hpp"

#include "EngineLogWidget.h"
#include "DemoCoordinateSystemsUtilities.h"

namespace
{

    void OnScroll(GLFWwindow* pWindow, double /*xOffset*/, double yOffset)
    {
        if (!pWindow)
            return;

        auto pApp = static_cast<TestApp*>(glfwGetWindowUserPointer(pWindow));
        if (!pApp)
            return;

		auto spEngine = pApp->GetEngine();
        if (!spEngine)
            return;

        auto spCamera = std::dynamic_pointer_cast<GraphicsEngine::ICameraFly>(spEngine->GetCamera());
		if (!spCamera)
			return;

        spCamera->Zoom(yOffset);
    }

}

TestApp::TestApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    m_pPrevScrollCallback = glfwSetScrollCallback(pWindow, OnScroll);

    // Call this before updating framebuffer stuff since this creates shaders.
    Utilities::CreateTenTexturedCubes(GetEngine());

    auto spCamera = GraphicsEngine::CreateCameraFly();
	spCamera->SetEye(glm::vec3(0.f, 0.f, 3.f));
    GetEngine()->SetCamera(spCamera);

    int fbWidth;
    int fbHeight;
    glfwGetFramebufferSize(pWindow, &fbWidth, &fbHeight);
    AppCallbacks::OnFramebufferSize(pWindow, fbWidth, fbHeight);
}

TestApp::~TestApp()
{
    // Restore previous callback functions.
    glfwSetScrollCallback(GetWindow(), m_pPrevScrollCallback);
}

auto TestApp::Iterate() -> void
{
    static auto lastFrameTime = glfwGetTime();
    auto thisFrameTime = glfwGetTime();
    auto deltaTime = static_cast<float>(thisFrameTime - lastFrameTime);
    lastFrameTime = thisFrameTime;

    float moveSpeed = 2.f; // inches per second
    float dist = moveSpeed * deltaTime; // inches

    float tiltSpeed = 60.f; // degrees per second
    float angle = tiltSpeed * deltaTime; // degrees
    
    auto spCamera = std::dynamic_pointer_cast<GraphicsEngine::ICameraFly>(GetEngine()->GetCamera());

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
            spCamera->SetYawIncremental(-1.f*angle);
        else
            spCamera->Strafe(dist * spCamera->GetRight());
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_DOWN))
    {
        if (ctrlIsPressed)
            spCamera->SetPitchIncremental(-1.f * angle);
        else if (shiftIsPressed)
            spCamera->Strafe(-1.f*dist*spCamera->GetFront());
        else
            spCamera->Strafe(-1.f*dist*spCamera->GetUp());
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_UP))
    {
        if (ctrlIsPressed)
            spCamera->SetPitchIncremental(angle);
        else if (shiftIsPressed)
            spCamera->Strafe(dist*spCamera->GetFront());
        else
            spCamera->Strafe(dist*spCamera->GetUp());
    }

    App::Iterate();
}

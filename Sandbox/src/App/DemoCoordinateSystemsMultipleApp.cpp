#include "DemoCoordinateSystemsMultipleApp.h"
#include "DemoCoordinateSystemsUtilities.h"
#include "EngineLogWidget.h"

#include "GraphicsEngine/ICameraFly.h"
#include "GraphicsEngine/IEntityFactory.h"

#include "glm/ext/matrix_clip_space.hpp"

DemoCoordinateSystemsMultipleApp::DemoCoordinateSystemsMultipleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    GetEngine()->SetBackgroundColor(graphics_engine::Types::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

    Utilities::CreateTenTexturedCubes(GetEngine());

    auto spCamera = graphics_engine::CreateCameraFly();
    spCamera->SetEye(glm::vec3(0.f, 0.f, 3.f));

	GetEngine()->SetCamera(spCamera);
}

auto DemoCoordinateSystemsMultipleApp::Iterate() -> void
{
    int width;
    int height;
    glfwGetWindowSize(GetWindow(), &width, &height);
    auto shader = GetEngine()->GetShaderManager()->GetCurrentShader();
    shader->SetUniformData("projection", glm::perspective(glm::radians(45.f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f));

    App::Iterate();
}

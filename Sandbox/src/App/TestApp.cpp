#include "TestApp.h"

#include "GraphicsEngine/IEntityFactory.h"
#include "GraphicsEngine/ICameraFly.h"

#include "glm/ext/matrix_clip_space.hpp"

#include "EngineLogWidget.h"
#include "DemoCoordinateSystemsUtilities.h"

TestApp::TestApp(GLFWwindow* pWindow)
    :   App(pWindow)
{
}

TestApp::~TestApp()
{
}

auto TestApp::Iterate() -> void
{
    App::Iterate();
}

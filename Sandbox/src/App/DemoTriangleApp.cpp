#include "DemoTriangleApp.h"

#include <numbers>

#include "glm/gtc/matrix_access.hpp"

#include "GraphicsEngine/AttributeFactory.h"
#include "GraphicsEngine/ICameraViewport.h"
#include "GraphicsEngine/IEngine.h"

auto OnCamera(GraphicsEngine::IEnginePtr spEngine, const glm::mat4& /*view*/, const glm::mat4& projection) -> void
{
	if (!spEngine)
		return;

	spEngine->GetShaderManager()->SetUniformData(*spEngine->GetShaderManager()->GetCurrentShader(), "projection", projection);
}

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	if (!pWindow)
		return;

	// Get the engine
	auto spEngine = GetEngine();

	// Set some misc items
	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });
	spEngine->SetPolygonMode(GraphicsEngine::PolygonMode::Fill);

	// Create a triangle
	auto pEntity = spEngine->GetEntityManager()->AddEntity({ GraphicsEngine::AttributeFactory::Triangle::SSS(1.f, 1.f, 1.f) });
	
	// Create a shader
	auto shadersDir = GraphicsEngine::Path(SHADERS_DIR);
	pEntity->shaderId = *spEngine->GetShaderManager()->AddShader(shadersDir / "DemoTriangle.vert", shadersDir / "DemoTriangle.frag");
	
	// Create a camera
	spEngine->SetCamera(GraphicsEngine::CreateCameraViewport());
	spEngine->GetCamera()->GetObservable()->AddObserver([this](const glm::mat4& view, const glm::mat4& projection) { OnCamera(GetEngine(), view, projection); });

	int width;
	int height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	AppCallbacks::OnFramebufferSize(pWindow, width, height);
}

#include "DemoTriangleApp.h"

#include <numbers>

#include "glm/gtc/matrix_access.hpp"

#include "GraphicsEngine/AttributeFactory.h"
#include "GraphicsEngine/ICameraViewport.h"
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/ShaderSnippets.h"
#include "GraphicsEngine/ShaderUtilities.h"

auto OnCamera(GraphicsEngine::IEnginePtr spEngine, const glm::mat4& /*view*/, const glm::mat4& projection) -> void
{
	if (!spEngine)
		return;

	spEngine->GetShaderManager()->GetCurrentShader()->SetUniformData("transformationMatrix", projection);
}

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	if (!pWindow)
		return;

	// Get the engine
	auto spEngine = GetEngine();

	// Set some misc items
	spEngine->SetBackgroundColor(GraphicsEngine::Types::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });
	spEngine->SetPolygonMode(GraphicsEngine::Types::PolygonMode::Fill);

	// Create a triangle
	auto pEntity = spEngine->GetEntityManager()->AddEntity({ GraphicsEngine::AttributeFactory::Triangle::SSS(1.f, 1.f, 1.f) });
	
	// Create a shader
	auto shadersDir = GraphicsEngine::Types::Path(SHADERS_DIR);
	std::string vertexShader = 
		GraphicsEngine::ShaderUtilities::GetSourceFromFile (shadersDir / "DemoTriangle.vert") 
		+ GraphicsEngine::ShaderSnippets::Transformation;
	std::string fragmentShader = GraphicsEngine::ShaderUtilities::GetSourceFromFile (shadersDir / "DemoTriangle.frag");
	pEntity->pShader = spEngine->GetShaderManager ()->AddShaderFromSource (vertexShader, fragmentShader);
	
	// Create a camera
	spEngine->SetCamera(GraphicsEngine::CreateCameraViewport());
	spEngine->GetCamera()->GetObservable()->AddObserver([this](const glm::mat4& view, const glm::mat4& projection) { OnCamera(GetEngine(), view, projection); });

	int width;
	int height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	AppCallbacks::OnFramebufferSize(pWindow, width, height);
}

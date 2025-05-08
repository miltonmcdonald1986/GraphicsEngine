#include "DemoTriangleApp.h"

#include <numbers>

#include "glm/gtc/matrix_access.hpp"

#include "GraphicsEngine/AttributeFactory.h"
#include "GraphicsEngine/ICameraViewport.h"
#include "GraphicsEngine/IEngine.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	auto spEngine = GetEngine();
	if (!spEngine)
		return;

	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });
	spEngine->SetPolygonMode(GraphicsEngine::PolygonMode::Fill);

	GraphicsEngine::ShaderId shaderId = 0;
	if (auto pShaderManager = spEngine->GetShaderManager())
	{
		auto shadersDir = GraphicsEngine::Path(SHADERS_DIR);
		auto pathVS = shadersDir / "DemoTriangle.vert";
		auto pathFS = shadersDir / "DemoTriangle.frag";
		if (auto oShaderId = pShaderManager->AddShader(pathVS, pathFS))
			shaderId = *oShaderId;
	}

	auto pEntity = spEngine->GetEntityManager()->AddEntity({ GraphicsEngine::AttributeFactory::Triangle::SSS(1.f, 1.f, 1.f) });
	pEntity->shaderId = shaderId;

	if (auto spCamera = GraphicsEngine::CreateCameraViewport())
		spEngine->SetCamera(spCamera);

	int width;
	int height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	AppCallbacks::OnFramebufferSize(pWindow, width, height);
}

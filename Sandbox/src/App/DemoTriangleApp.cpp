#include "DemoTriangleApp.h"

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

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.f,   0.5f, 0.f)
	};

	GraphicsEngine::IAttributes attributes;
	auto posAttribute = GraphicsEngine::CreateAttribute(vertices);
	attributes.push_back(posAttribute);
	
	auto spEntity = spEngine->CreateNewEntity(attributes);
	spEntity->SetShaderId(shaderId);

	if (auto spCamera = GraphicsEngine::CreateCameraViewport())
		spEngine->SetCamera(spCamera);

	int width;
	int height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	AppCallbacks::OnFramebufferSize(pWindow, width, height);
}

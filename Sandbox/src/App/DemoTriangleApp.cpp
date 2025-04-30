#include "DemoTriangleApp.h"

#include "GraphicsEngine/ICameraViewport.h"
#include "GraphicsEngine/IEngine.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	auto spEngine = GetEngine();
	if (!spEngine)
		return;

	auto spCamera = GraphicsEngine::CreateCameraViewport();
	if (!spCamera)
		return;
	
	spEngine->SetCamera(spCamera);

	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3( 0.5f, -0.5f, 0.f),
		glm::vec3( 0.f,   0.5f, 0.f)
	};

	auto spEntity = spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices) });
	spEntity->SetShader(spEngine->CreateNewShaderFromFiles(std::filesystem::path(SHADERS_DIR)/"DemoTriangle.vert", "", std::filesystem::path(SHADERS_DIR)/"DemoTriangle.frag"));

	int width;
	int height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	AppCallbacks::OnFramebufferSize(pWindow, width, height);
}

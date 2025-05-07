#include "DemoTriangleApp.h"

#include <numbers>

#include "glm/gtc/matrix_access.hpp"

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

	//float root3 = std::sqrtf(3.f);
	//float y0 = root3 / 6.f;
	//float y1 = root3 / 3.f;
	//
	//const glm::vec3 v0(-0.5f, -y0, 0.f);
	//const glm::vec3 v1( 0.5f, -y0, 0.f);
	//const glm::vec3 v2( 0.f,   y1, 0.f);

	//const glm::vec3 w0(-0.5f, -y0, 0.f);
	//const glm::vec3 w1( 0.5f, -y0, 0.f);
	//const glm::vec3 w2( 0.5f,  y1, 0.f);

	//auto e1 = v1 - v0;
	//auto e2 = v2 - v0;
	//auto e3 = glm::cross(e1, e2);

	//auto f1 = w1 - w0;
	//auto f2 = w2 - w0;
	//auto f3 = glm::cross(f1, f2);

	//glm::mat3 E(e1, e2, e3);
	//glm::mat3 F(f1, f2, f3);

	//glm::mat3 M = F * glm::inverse(E);
	//auto m3 = w0 - M * v0;
	//glm::vec3 Mp0 = glm::column(M, 0);
	//glm::vec3 Mp1 = glm::column(M, 1);
	//glm::vec3 Mp2 = glm::column(M, 2);
	//
	//glm::mat4 model(glm::vec4(Mp0, 0.f), glm::vec4(Mp1, 0.f), glm::vec4(Mp2, 0.f), glm::vec4(m3, 1.f));

	auto ValidSSS = [](float a, float b, float c) -> bool
		{
			return (a + b > c) && (a + c > b) && (b + c > a);
		};

	auto SSS = [&ValidSSS](float a, float b, float c) -> GraphicsEngine::IAttributePtr
		{
			if (!ValidSSS)
				return nullptr;

			glm::vec3 v0(0.f,	0.f, 0.f);
			glm::vec3 v1(  c,	0.f, 0.f);
			
			float x = (std::powf(a, 2.f) - std::powf(b, 2.f) + std::powf(c, 2.f) / (2.f*c));
			float y = std::sqrtf(std::powf(a, 2.f) - std::powf((std::powf(a, 2.f) - std::powf(b, 2.f) + std::powf(c, 2.f)) / (2.f * c), 2.f));
			glm::vec3 v2(x, y, 0.f);

			auto centroid = (1.f / 3.f) * (v0 + v1 + v2);
			v0 -= centroid;
			v1 -= centroid;
			v2 -= centroid;

			auto spAttribute = GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{v0, v1, v2});
			return spAttribute;
		};

	GraphicsEngine::IAttributes attributes;
	auto posAttribute = SSS(1.f, 1.f, 1.f);
	attributes.push_back(posAttribute);
	
	auto pEntity = spEngine->GetEntityManager()->AddEntity(attributes);
	//pEntity->modelMatrix = model;
	pEntity->shaderId = shaderId;

	if (auto spCamera = GraphicsEngine::CreateCameraViewport())
		spEngine->SetCamera(spCamera);

	int width;
	int height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	AppCallbacks::OnFramebufferSize(pWindow, width, height);
}

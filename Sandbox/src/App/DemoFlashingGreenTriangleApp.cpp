#include "DemoFlashingGreenTriangleApp.h"

#include <cmath>
#include <numbers>

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IShader.h"
#include "GraphicsEngine/IAttribute.h"
#include "GraphicsEngine/IEntity.h"
#include "GraphicsEngine/IUniform.h"

#include "glm/vec3.hpp"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "EngineLogWidget.h"

DemoFlashingGreenTriangleApp::DemoFlashingGreenTriangleApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	m_spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.f,   0.5f, 0.f)
	};

	GraphicsEngine::IAttributes attributes = { GraphicsEngine::CreateAttribute(vertices) };
	auto spEntity = m_spEngine->CreateNewEntity(attributes);

	auto spShader = m_spEngine->CreateNewShaderFromFiles("shaders/DemoFlashingGreenTriangle.vert", "", "shaders/DemoFlashingGreenTriangle.frag");
	auto uniforms = spShader->GetActiveUniforms();
	for (auto spUniform : uniforms)
	{
		std::string name = spUniform->GetName();
		std::string uniformName = "uGreenScalar";
		if (name == uniformName)
		{
			m_spUniform = spUniform;
			m_spUniform->SetData(1.f);
		}
	}

	spEntity->SetShader(spShader);
}

auto DemoFlashingGreenTriangleApp::Iterate() -> void
{
	auto now = std::chrono::steady_clock::now();
	static auto start = now; // Initialize start time
	float elapsedTime = std::chrono::duration<float>(now - start).count();
	float period = 2.f;
	float value = 0.5f * (1.f + std::cos(2.f * std::numbers::pi_v<float> *elapsedTime / period));

	if (m_spUniform)
		m_spUniform->SetData(value);
		
	App::Iterate();
}
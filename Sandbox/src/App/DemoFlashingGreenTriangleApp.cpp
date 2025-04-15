#include "DemoFlashingGreenTriangleApp.h"

#include <numbers>

#include "IEngine.h"
#include "IShader.h"
#include "IAttribute.h"
#include "IEntity.h"
#include "IUniform.h"

#include "glm/vec3.hpp"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"

DemoFlashingGreenTriangleApp::DemoFlashingGreenTriangleApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.f,   0.5f, 0.f)
	};

	GraphicsEngine::IAttributes attributes = { GraphicsEngine::CreateAttribute(vertices) };
	auto spEntity = m_spEngine->CreateNewEntity(attributes);

	auto spShader = m_spEngine->CreateNewShaderFromFiles("shaders/A0Pos3f.vert", "", "shaders/GreenScalar.frag");
	auto uniforms = spShader->GetActiveUniforms();
	for (auto spUniform : uniforms)
	{
		auto t1 = typeid(spUniform->GetName()).name();
		auto t2 = typeid("uGreenScalar").name();
		std::string name = spUniform->GetName();
		std::string uniformName = "uGreenScalar";
		if (name == uniformName)
		{
			m_spUniform = spUniform;
			m_spUniform->SetData(1.f);
		}
	}

	spEntity->SetShader(spShader);

	m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
}

auto DemoFlashingGreenTriangleApp::Iterate() -> void
{
	auto now = std::chrono::steady_clock::now();
	static auto start = now; // Initialize start time
	float elapsedTime = std::chrono::duration<float>(now - start).count();
	float period = 2.f;
	float value = 0.5f * (1.f + std::cos(2.f * std::numbers::pi_v<float> *elapsedTime / period));

	m_spUniform->SetData(value);
	App::Iterate();
}
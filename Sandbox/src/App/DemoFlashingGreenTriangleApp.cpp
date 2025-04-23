#include "DemoFlashingGreenTriangleApp.h"

#include "GraphicsEngine/IEngine.h"

DemoFlashingGreenTriangleApp::DemoFlashingGreenTriangleApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	auto spEngine = GetEngine();

	spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.f,   0.5f, 0.f)
	};

	GraphicsEngine::IAttributes attributes = { GraphicsEngine::CreateAttribute(vertices) };
	auto spEntity = spEngine->CreateNewEntity(attributes);

	auto spShader = spEngine->CreateNewShaderFromFiles("shaders/DemoFlashingGreenTriangle.vert", "", "shaders/DemoFlashingGreenTriangle.frag");
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
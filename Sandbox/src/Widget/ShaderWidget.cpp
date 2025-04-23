#include "ShaderWidget.h"

#include "GraphicsEngine/IEngine.h"

ShaderWidget::ShaderWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
	: Widget(pWindow, spEngine)
{
}

auto ShaderWidget::Iterate() -> void
{
	auto spShader = m_spEngine->GetCurrentShader();
	if (!spShader)
		return;

	ImGui::Begin("Shader", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	auto uniforms = spShader->GetActiveUniforms();
	for (auto spUniform : uniforms)
	{
		auto data = spUniform->GetData();
		if (std::holds_alternative<float>(data))
		{
			struct ScalarData
			{
				float f = 0.f;
				float fMin = 0.f;
				float fMax = 0.f;
			};

			if (ScalarData sd { .f = std::get<float>(data), .fMin = 0.f, .fMax = 1.f }; ImGui::DragScalar(spUniform->GetName().c_str(), ImGuiDataType_Float, &sd.f, 0.002f, &sd.fMin, &sd.fMax))
				spUniform->SetData(sd.f);
		}
		else if (std::holds_alternative<int>(data))
		{
			if (int v = std::get<int>(data); ImGui::InputInt(spUniform->GetName().c_str(), &v))
				spUniform->SetData(v);
		}
		else
			m_spEngine->GetLog()->Warn("Type is not handled by shader widget.");
	}
	ImGui::End();
}

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
		//case GraphicsEngine::DataType::Vec4:
		//{
		//	// The convention for this shader widget is
		//	// 1) If the uniform's name contains the substring "color", then we bound the DragFloat4 values between 0 and 1.
		//	// 2) Otherwise, we leave them unbounded.

		//	std::string lower = uniform.m_Name;
		//	std::transform(lower.begin(), lower.end(), lower.begin(), [](char c) { return std::tolower(c); });
		//	bool bound = lower.find("color") != std::string::npos;

		//	float *v = uniform.m_Data.u_vec4;
		//	if (ImGui::DragFloat4(uniform.m_Name, v, bound ? 1.0f / 255.0f : 1.0F, 0.0F, bound ? 1.0F : 0.0F))
		//		geSetUniform(pShader, &uniform);

		//	break; 
		//}
		//default:
		//	break;
	}
	ImGui::End();
}

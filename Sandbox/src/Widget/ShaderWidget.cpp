#include "ShaderWidget.h"

#pragma warning(push)
#pragma warning(disable : 4244)
#include <algorithm>
#pragma warning(pop)
#include <functional>

#include "imgui.h"

#include "IEngine.h"
#include "IShader.h"
#include "IUniform.h"

ShaderWidget::ShaderWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
	: Widget(pWindow, spEngine)
{
}

auto ShaderWidget::Iterate() -> void
{
	auto spShader = m_spEngine->GetCurrentShader();
	auto uniforms = spShader->GetActiveUniforms();
	for (int i = 0; i < uniforms.size(); ++i)
	{
		GraphicsEngine::IUniformPtr spUniform = uniforms[i];
		auto data = spUniform->GetData();
		if (std::holds_alternative<float>(data))
		{
			float& f = std::get<float>(data);
			if (ImGui::DragFloat(spUniform->GetName().c_str(), &f))
				spUniform->SetData(data);
			break;
		}
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
}


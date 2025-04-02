#include "ShaderWidget.h"

#include <algorithm>
#include <functional>

#include "imgui.h"

#include "GraphicsEngine/GL.h"

ShaderWidget::ShaderWidget(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine)
	: Widget(spWindow, spEngine)
{
	auto prog = GraphicsEngine::GL::GetCurrentProgram();
	auto count = GraphicsEngine::GL::GetNumActiveUniformVariables(prog);

	for (int i = 0; i < count; ++i)
	{
		m_Uniforms.push_back(GraphicsEngine::GL::GetActiveUniform(prog, i));	
	}
}

auto ShaderWidget::Iterate() -> void
{
	auto prog = GraphicsEngine::GL::GetCurrentProgram();
	for (auto& uniform : GraphicsEngine::GL::GetActiveUniforms(prog))
	{
		if (std::holds_alternative<glm::vec4>(uniform.m_Value))
		{
			// The convention for this shader widget is
			// 1) If the uniform's name contains the substring "color", then we bound the DragFloat4 values between 0 and 1.
			// 2) Otherwise, we leave them unbounded.

			auto lower = uniform.m_Name;
			std::transform(lower.begin(), lower.end(), lower.begin(), [](char c) { return std::tolower(c); });
			bool bound = lower.find("color") != std::string::npos;

			auto& vec4 = std::get<glm::vec4>(uniform.m_Value);
			float v[4] = { vec4[0], vec4[1], vec4[2], vec4[3] };
			if (ImGui::DragFloat4(uniform.m_Name.data(), v, bound ? 1.0f / 255.0f : 1.0F, 0.0F, bound ? 1.0F : 0.0F))
			{
				vec4 = glm::vec4(v[0], v[1], v[2], v[3]);

				GraphicsEngine::GL::SetUniform(uniform);
			}
		}
	}
}


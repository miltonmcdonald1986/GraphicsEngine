#include "ShaderWidget.h"

#include <algorithm>
#include <functional>

#include "imgui.h"

#include "GraphicsEngine/GL.h"

ShaderWidget::ShaderWidget(GLFWwindowSharedPtr spWindow, GEengineSharedPtr spEngine)
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
		switch (uniform.m_Type)
		{
		case GE_UNIFORM_TYPE_VEC4:
		{
			// The convention for this shader widget is
			// 1) If the uniform's name contains the substring "color", then we bound the DragFloat4 values between 0 and 1.
			// 2) Otherwise, we leave them unbounded.

			std::string lower = uniform.m_Name;
			std::transform(lower.begin(), lower.end(), lower.begin(), [](char c) { return std::tolower(c); });
			bool bound = lower.find("color") != std::string::npos;

			float *v = uniform.m_Data.vec4;
			if (ImGui::DragFloat4(uniform.m_Name, v, bound ? 1.0f / 255.0f : 1.0F, 0.0F, bound ? 1.0F : 0.0F))
			{
				GraphicsEngine::GL::SetUniform(uniform);
			}

			break; 
		}
		}
	}
}


#include "ShaderWidget.h"

#include <algorithm>

#include "Windows.h"

#include "imgui.h"

ShaderWidget::ShaderWidget(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine)
	: Widget(spWindow, spEngine)
{
	GLint prog = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

	GLint count;
	glGetProgramiv(prog, GL_ACTIVE_UNIFORMS, &count);

	const GLsizei bufSize = 16; // maximum name length
	GLint size;
	GLenum type;
	std::string name(bufSize, '\0');
	//GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	for (int i = 0; i < count; ++i)
	{
		glGetActiveUniform(prog, i, bufSize, &length, &size, &type, name.data());
		m_Uniforms.push_back(Uniform { .type = type, .name = name });
	}
}

auto ShaderWidget::Iterate() -> void
{
	GLint prog = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

	for (const auto& uniform : m_Uniforms)
	{
		switch (uniform.type)
		{
		case GL_FLOAT_VEC4:
		{

			// The convention for this shader widget is
			// 1) If the uniform's name contains the substring "color", then we bound the DragFloat4 values between 0 and 1.
			// 2) Otherwise, we leave them unbounded.

			auto lower = uniform.name;
			std::transform(lower.begin(), lower.end(), lower.begin(), [](char c) { return std::tolower(c); });
			bool bound = lower.find("color") != std::string::npos;
			float v[4];
			GLint location = glGetUniformLocation(prog, uniform.name.data());
			glGetUniformfv(prog, location, v);
			if (ImGui::DragFloat4(uniform.name.data(), v, bound ? 1.0f / 255.0f : 1.0F, 0.0F, bound ? 1.0 : 0.0F))
			{
				glUniform4f(location, v[0], v[1], v[2], v[3]);
			}

			break;
		}
		default:
			break;
		}
	}
}


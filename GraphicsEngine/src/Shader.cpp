#include "pch.h"
#include "Shader.h"

#include "glm/vec4.hpp"

#include "SafeGL.h"
#include "Debug.h"
#include "Uniform.h"
#include "Log.h"

namespace Helpers
{

	auto CompileShader(GLenum shaderType, const char *source) -> GLuint
	{
		using namespace GraphicsEngine;

		if (source == nullptr)
			return 0;

		GLuint shader = GL::CreateShader(shaderType);
		GL::ShaderSource(shader, 1, &source, nullptr);
		GL::CompileShader(shader);

		auto spLog = GetLog();

		GLint success;
		GL::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			if (spLog)
				spLog->Error("Error when compiling shader.");

			GLint infoLogLength;
			GL::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog(infoLogLength, '\0');
			GL::GetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());
			if (spLog)
				spLog->Info(infoLog);

			return 0;
		}

		return shader;
	}

	auto LinkProgram(const std::vector<GLuint> &shaders) -> GLuint
	{
		using namespace GraphicsEngine;

		GLuint shaderProgram = GL::CreateProgram();
		for (auto shader : shaders)
		{
			if (shader != 0)
				GL::AttachShader(shaderProgram, shader);
		}

		GL::LinkProgram(shaderProgram);

		GLint success;
		GL::GetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLint infoLogLength;
			GL::GetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog(infoLogLength, '\0');
			GL::GetProgramInfoLog(shaderProgram, infoLogLength, nullptr, infoLog.data());

			return 0;
		}

		for (auto shader : shaders)
		{
			GL::DeleteShader(shader);
		}

		return shaderProgram;
	}

}

namespace GraphicsEngine
{

	IShaderPtr CreateShaderFromSourceCode(const std::string &vert, const std::string &geom, const std::string &frag)
	{
		return std::make_shared<Shader>(vert, geom, frag);
	}

	Shader::Shader(const std::string &vertSource, const std::string &geomSource, const std::string &fragSource)
	{

		auto vertShaderId = Helpers::CompileShader(GL_VERTEX_SHADER, vertSource.empty() ? nullptr : vertSource.c_str());
		auto geomShaderId = Helpers::CompileShader(GL_GEOMETRY_SHADER, geomSource.empty() ? nullptr : geomSource.c_str());
		auto fragShaderId = Helpers::CompileShader(GL_FRAGMENT_SHADER, fragSource.empty() ? nullptr : fragSource.c_str());
		m_Id = Helpers::LinkProgram({vertShaderId, geomShaderId, fragShaderId});

		// Grab the list of uniforms from the shader.
		GLint count;
		GL::GetProgramiv(m_Id, GL_ACTIVE_UNIFORMS, &count);

		GLint maxLength;
		GL::GetProgramiv(m_Id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

		m_Uniforms.clear();
		for (int i = 0; i < count; ++i)
		{
			GLint size;
			GLenum type;
			std::string name(maxLength, '\0');
			GLsizei length; // name length
			GL::GetActiveUniform(m_Id, i, maxLength, &length, &size, &type, name.data());
			name.pop_back();

			GLint location = GL::GetUniformLocation(m_Id, name.data());

			UniformPtr spUniform = CreateUniform(m_Id);
			spUniform->SetName(name);
			spUniform->SetLocation(location);
			switch (type)
			{
			case GL_FLOAT:
			{
				float data;
				GL::GetUniformfv(m_Id, location, &data);
				spUniform->SetData(data);
				break;
			}
			case GL_FLOAT_VEC4:
			{
				std::array<float, 4> v;
				GL::GetUniformfv(m_Id, location, v.data());
				glm::vec4 data(v[0], v[1], v[2], v[3]);
				break;
			}
			default:
			{
				GetLog()->Warn(std::format("Shader uniform type not handled: {}", type));
				m_Uniforms.push_back(nullptr);
				break;
			}
			}

			m_Uniforms.push_back(std::dynamic_pointer_cast<IUniform>(spUniform));
		}
	}

	auto Shader::GetId() const -> unsigned int
	{
		return m_Id;
	}

	auto Shader::GetActiveUniforms() const -> IUniforms
	{
		return m_Uniforms;
	}

	auto Shader::Use() const -> void
	{
		GL::UseProgram(m_Id);
	}

}

#include "pch.h"
#include "Shader.h"

#include "glm/vec4.hpp"

#include "SafeGL.h"
#include "Debug.h"
#include "Uniform.h"

//GEshader* geCreateShaderFromFiles(const char* vert, const char* geom, const char* frag)
//{
//	auto vertSource = ReadFile(vert);
//	auto geomSource = geom ? ReadFile(geom) : "";
//	auto fragSource = ReadFile(frag);
//	return geCreateShaderFromStrings(vertSource.c_str(), geomSource.empty() ? nullptr : geomSource.c_str(), fragSource.c_str());
//}

//GEshader* geCreateShaderFromStrings(const char* vert, const char* geom, const char* frag)
//{
//	return new GEshader(vert, geom, frag);
//}
//
//void geDestroyShader(GEshader* pShader)
//{
//	delete pShader;
//}
//
//unsigned int geGetActiveProgram()
//{
//	GLint prog;
//	GL::GetIntegerv(GL_CURRENT_PROGRAM, &prog);
//
//	return prog;
//}
//
//void geGetActiveUniforms(GEshader* pShader, GEuniform* uniforms)
//{
//}
//
//int geGetNumActiveUniforms(GEshader* pShader)
//{
//	return pShader->GetNumActiveUniforms();
//}
//
//bool geSetUniform(GEshader* pShader, const GEuniform* uniform)
//{
//	unsigned int activeProgram = geGetActiveProgram();
//	auto Cleanup = [&activeProgram]()
//		{
//			GL::UseProgram(activeProgram);
//		};
//
//	unsigned int givenProgram = pShader->GetId();
//	GL::UseProgram(givenProgram);
//
//	switch (uniform->m_Type)
//	{
//	case GE_UNIFORM_TYPE_FLOAT:
//	{
//		float v = uniform->m_Data.u_float;
//		GL::Uniform1f(uniform->m_Location, v);
//	}
//	case GE_UNIFORM_TYPE_VEC4:
//	{
//		const float* v = uniform->m_Data.u_vec4;
//		GL::Uniform4f(uniform->m_Location, v[0], v[1], v[2], v[3]);
//		break;
//	}
//	default:
//		BREAKPOINT; // We need to handle whatever type was provided.
//		Cleanup();
//		return false;
//	}
//
//	Cleanup();
//	return true;
//}
//
//GEshader::GEshader(const char* vertSource, const char* geomSource, const char* fragSource)
//{
//	auto CompileShader = [](GLenum shaderType, const char* source) -> GLuint
//		{
//			if (source == nullptr)
//				return 0;
//
//			GLuint shader = GL::CreateShader(shaderType);
//			GL::ShaderSource(shader, 1, &source, nullptr);
//			GL::CompileShader(shader);
//			
//			GLint success;
//			GL::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
//			if (!success)
//			{
//				GLint infoLogLength;
//				GL::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
//				
//				std::string infoLog(infoLogLength, '\0');
//				GL::GetShaderInfoLog(shader, infoLogLength, NULL, infoLog.data());
//				//spdlog::get("Engine")->info(infoLog);
//				
//				return 0;
//			}
//
//			return shader;
//		};
//
//	auto LinkProgram = [](const std::vector<GLuint>& shaders) -> GLuint
//		{
//			GLuint shaderProgram = GL::CreateProgram();
//			for (auto shader : shaders)
//			{
//				if (shader != 0)
//					GL::AttachShader(shaderProgram, shader);
//			}
//
//			GL::LinkProgram(shaderProgram);
//
//			GLint success;
//			GL::GetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//			if (!success)
//			{
//				GLint infoLogLength;
//				GL::GetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
//
//				std::string infoLog(infoLogLength, '\0');
//				GL::GetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog.data());
//
//				return 0;
//			}
//
//			for (auto shader : shaders)
//			{
//				GL::DeleteShader(shader);
//			}
//
//			return shaderProgram;
//		};
//
//	auto vertShaderId = CompileShader(GL_VERTEX_SHADER, vertSource);
//	auto geomShaderId = CompileShader(GL_GEOMETRY_SHADER, geomSource);
//	auto fragShaderId = CompileShader(GL_FRAGMENT_SHADER, fragSource);
//	m_ProgramId = LinkProgram({ vertShaderId, geomShaderId, fragShaderId });
//
//	// Grab the list of uniforms from the shader.
//	GLint count;
//	GL::GetProgramiv(m_ProgramId, GL_ACTIVE_UNIFORMS, &count);
//
//	GLint maxLength;
//	GL::GetProgramiv(m_ProgramId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
//
//	m_Uniforms.clear();
//	for (int i = 0; i < count; ++i)
//	{
//		GLint size;
//		GLenum type;
//		std::string name(maxLength, '\0');
//		GLsizei length; // name length
//		GL::GetActiveUniform(m_ProgramId, i, maxLength, &length, &size, &type, name.data());
//		GLint location = GL::GetUniformLocation(m_ProgramId, name.data());
//
//		GEuniform uniform;
//		uniform.m_Name = name.c_str();
//		uniform.m_Location = location;
//		switch (type)
//		{
//		case GL_FLOAT:
//		{
//			float data;
//			GL::GetUniformfv(m_ProgramId, location, &data);
//
//			uniform.m_Type = GE_UNIFORM_TYPE_FLOAT;
//			uniform.m_Data.u_float = data;
//
//			m_Uniforms.push_back(uniform);
//			break;
//		}
//		case GL_FLOAT_VEC4:
//		{
//			float v[4];
//			GL::GetUniformfv(m_ProgramId, location, v);
//
//			uniform.m_Type = GE_UNIFORM_TYPE_VEC4;
//			uniform.m_Name = name.c_str();
//			uniform.m_Location = location;
//			std::copy(uniform.m_Data.u_vec4, uniform.m_Data.u_vec4 + 4, v);
//
//			m_Uniforms.push_back(uniform);
//			break;
//		}
//		default:
//		{
//			// Apparently we're not handling a type that we need to be.
//			BREAKPOINT;
//			m_Uniforms.push_back(GEuniform{ .m_Type = GE_UNIFORM_TYPE_EMPTY });
//			break;
//		}
//		}
//	}
//}
//
//auto GEshader::GetId() const -> GLuint
//{
//	return m_ProgramId;
//}
//
//auto GEshader::GetActiveUniforms() const -> std::vector<GEuniform>
//{
//	return m_Uniforms;
//}
//
//auto GEshader::GetNumActiveUniforms() const -> int
//{
//	return static_cast<int>(m_Uniforms.size());
//}

namespace GraphicsEngine
{

	IShaderPtr GraphicsEngine::CreateShaderFromSourceCode(const std::string& vert, const std::string& geom, const std::string& frag)
	{
		return IShaderPtr(new Shader(vert, geom, frag));
	}

	GraphicsEngine::Shader::Shader(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource)
	{
		auto CompileShader = [](GLenum shaderType, const char* source) -> GLuint
			{
				if (source == nullptr)
					return 0;

				GLuint shader = GL::CreateShader(shaderType);
				GL::ShaderSource(shader, 1, &source, nullptr);
				GL::CompileShader(shader);

				GLint success;
				GL::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					GLint infoLogLength;
					GL::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

					std::string infoLog(infoLogLength, '\0');
					GL::GetShaderInfoLog(shader, infoLogLength, NULL, infoLog.data());
					//spdlog::get("Engine")->info(infoLog);

					return 0;
				}

				return shader;
			};

		auto LinkProgram = [](const std::vector<GLuint>& shaders) -> GLuint
			{
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
					GL::GetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog.data());

					return 0;
				}

				for (auto shader : shaders)
				{
					GL::DeleteShader(shader);
				}

				return shaderProgram;
			};

		auto vertShaderId = CompileShader(GL_VERTEX_SHADER, vertSource.empty() ? nullptr : vertSource.c_str());
		auto geomShaderId = CompileShader(GL_GEOMETRY_SHADER, geomSource.empty() ? nullptr : geomSource.c_str());
		auto fragShaderId = CompileShader(GL_FRAGMENT_SHADER, fragSource.empty() ? nullptr : fragSource.c_str());
		m_Id = LinkProgram({ vertShaderId, geomShaderId, fragShaderId });

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
				float v[4];
				GL::GetUniformfv(m_Id, location, v);
				glm::vec4 data(v[0], v[1], v[2], v[3]);
				break;
			}
			default:
			{
				// Apparently we're not handling a type that we need to be.
				BREAKPOINT;
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

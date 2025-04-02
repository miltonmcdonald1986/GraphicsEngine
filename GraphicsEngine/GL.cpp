#include "pch.h"
#include "GraphicsEngine/GL.h"

#include "glm/vec4.hpp"

#include "Error.h"

namespace GLHelpers
{

	const std::map<GraphicsEngine::GL::StateVariable, GLenum> MapStateVariableToGLenum =
	{
		std::make_pair(GraphicsEngine::GL::StateVariable::ColorClearValue, GL_COLOR_CLEAR_VALUE),
		std::make_pair(GraphicsEngine::GL::StateVariable::PolygonMode, GL_POLYGON_MODE)
	};

	const std::map<GraphicsEngine::GL::PolygonMode, GLenum> MapRasterizeModeToGLenum =
	{
		std::make_pair(GraphicsEngine::GL::PolygonMode::Point, GL_POINT),
		std::make_pair(GraphicsEngine::GL::PolygonMode::Line, GL_LINE),
		std::make_pair(GraphicsEngine::GL::PolygonMode::Fill, GL_FILL)
	};

	auto GetFloatv(GLenum pname, GLfloat* data) -> void
	{
		glGetFloatv(pname, data);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto GetIntegerv(GLenum pname, GLint* data) -> void
	{
		glGetIntegerv(pname, data);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto GetProgramiv(GLuint program, GLenum pname, GLint* params) -> void
	{
		glGetProgramiv(program, pname, params);
		GraphicsEngine::HandleError(__FUNCTION__);
	}


	auto PolygonMode(GLenum face, GLenum mode) -> void
	{
		glPolygonMode(face, mode);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

}

namespace GraphicsEngine::GL
{

	auto AttachShader(GLuint program, GLuint shader) -> void
	{
		glAttachShader(program, shader);
		HandleError(__FUNCTION__);
	}

	auto BindBuffer(GLenum target, GLuint buffer) -> void
	{
		glBindBuffer(target, buffer);
		HandleError(__FUNCTION__);
	}

	auto BindVertexArray(GLuint array) -> void
	{
		glBindVertexArray(array);
		HandleError(__FUNCTION__);
	}

	auto BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) -> void
	{
		glBufferData(target, size, data, usage);
		HandleError(__FUNCTION__);
	}

	auto ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) -> void
	{
		glClearColor(red, green, blue, alpha);
	}

	auto CompileShader(GLuint shader) -> void
	{
		glCompileShader(shader);
		HandleError(__FUNCTION__);
	}

	auto CreateProgram() -> GLuint
	{
		GLuint result = glCreateProgram();
		HandleError(__FUNCTION__);

		return result;
	}

	auto CreateShader(GLenum shaderType) -> GLuint
	{
		GLuint result = glCreateShader(shaderType);
		HandleError(__FUNCTION__);

		return result;
	}

	auto GenVertexArrays(GLsizei n, GLuint* arrays) -> void
	{
		glGenVertexArrays(n, arrays);
		HandleError(__FUNCTION__);
	}

	auto GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void
	{
		glGetActiveUniform(program, index, bufSize, length, size, type, name);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto GetFloatv(StateVariable pname, GLfloat* data) -> void
	{
		GLHelpers::GetFloatv(GLHelpers::MapStateVariableToGLenum.at(pname), data);
	}

	auto GetIntegerv(StateVariable pname, GLint* data) -> void
	{
		GLHelpers::GetIntegerv(GLHelpers::MapStateVariableToGLenum.at(pname), data);
	}

	auto GetActiveUniform(GLuint programId, GLuint index) -> Uniform
	{
		const GLsizei bufSize = 16; // maximum name length
		GLint size;
		GLenum type;
		std::string name(bufSize, '\0');
		GLsizei length; // name length
		GL::GetActiveUniform(programId, index, bufSize, &length, &size, &type, name.data());

		Uniform uniform;
		uniform.m_Name = name;
		switch (type)
		{
		case GL_FLOAT_VEC4:
		{
			float v[4];
			GLint location = GL::GetUniformLocation(programId, name.data());
			uniform.m_Location = location;
			GL::GetUniformfv(programId, location, v);
			uniform.m_Value = glm::vec4(v[0], v[1], v[2], v[3]);
			return uniform;
		}
		}

		// Apparently we're not handling a type that we need to be.
		DebugBreak();
		return Uniform{ .m_Name = "", .m_Value = std::monostate() };
	}

	auto GetActiveUniforms(GLuint programId) -> std::vector<Uniform>
	{
		std::vector<Uniform> uniforms;
		auto count = GraphicsEngine::GL::GetNumActiveUniformVariables(programId);
		for (int i = 0; i < count; ++i)
		{
			uniforms.push_back(GraphicsEngine::GL::GetActiveUniform(programId, i));
		}

		return uniforms;
	}

	auto GetPolygonMode() -> PolygonMode
	{
		std::vector<GLint> param(2);
		GetIntegerv(StateVariable::PolygonMode, param.data());

		switch (param[0])
		{
		case GL_POINT:
			return PolygonMode::Point;
		case GL_LINE:
			return PolygonMode::Line;
		default:
			return PolygonMode::Fill;
		}
	}

	auto SetPolygonMode(PolygonMode mode) -> void
	{
		GLHelpers::PolygonMode(GL_FRONT_AND_BACK, GLHelpers::MapRasterizeModeToGLenum.at(mode));
	}

	auto SetUniform(const Uniform& uniform) -> void
	{
		const auto& value = uniform.m_Value;
		if (std::holds_alternative<glm::vec4>(value))
		{
			auto vec4 = std::get<glm::vec4>(value);
			GL::Uniform4f(uniform.m_Location, vec4[0], vec4[1], vec4[2], vec4[3]);
		}
	}

	auto ClearColorBuffer() -> void
	{
		glClear(GL_COLOR_BUFFER_BIT);
		HandleError(__FUNCTION__);
	}

	auto GetCurrentProgram() -> GLuint
	{
		GLint prog = 0;
		GLHelpers::GetIntegerv(GL_CURRENT_PROGRAM, &prog);
		
		return prog;
	}

	auto GetLinkStatus(GLuint program) -> bool
	{
		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		HandleError(__FUNCTION__);

		return (success == 0) ? false : true;
	}

	auto GetNumActiveUniformVariables(GLuint programId) -> GLint
	{
		GLint count;
		GLHelpers::GetProgramiv(programId, GL_ACTIVE_UNIFORMS, &count);

		return count;
	}

	auto GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void
	{
		glGetShaderInfoLog(shader, maxLength, length, infoLog);
		HandleError(__FUNCTION__);
	}

	auto GetShaderiv(GLuint shader, GLenum pname, GLint* params) -> void
	{
		glGetShaderiv(shader, pname, params);
		HandleError(__FUNCTION__);
	}

	auto GetUniformfv(GLuint program, GLint location, GLfloat* params) -> void
	{
		glGetUniformfv(program, location, params);
		HandleError(__FUNCTION__);
	}

	auto GetUniformLocation(GLuint program, const GLchar* name) -> GLint
	{
		GLint result = glGetUniformLocation(program, name);
		HandleError(__FUNCTION__);

		return result;
	}

	auto LinkProgram(GLuint program) -> void
	{
		glLinkProgram(program);
		HandleError(__FUNCTION__);
	}

	auto ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) -> void
	{
		glShaderSource(shader, count, string, length);
		HandleError(__FUNCTION__);
	}

	auto Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) -> void
	{
		glUniform4f(location, v0, v1, v2, v3);
		HandleError(__FUNCTION__);
	}

	auto UseProgram(GLuint program) -> void
	{
		glUseProgram(program);
		HandleError(__FUNCTION__);
	}

}

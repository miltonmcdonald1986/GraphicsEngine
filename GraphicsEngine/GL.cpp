#include "pch.h"
#include "GraphicsEngine/GL.h"

#include "glm/vec4.hpp"

#include "Error.h"
#include "SafeGL.h"

namespace GLHelpers
{

	const std::map<GraphicsEngine::GL::PolygonMode, GLenum> MapRasterizeModeToGLenum =
	{
		std::make_pair(GraphicsEngine::GL::PolygonMode::Point, GL_POINT),
		std::make_pair(GraphicsEngine::GL::PolygonMode::Line, GL_LINE),
		std::make_pair(GraphicsEngine::GL::PolygonMode::Fill, GL_FILL)
	};

	auto BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) -> void
	{
		glBufferData(target, size, data, usage);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto CreateShader(GLenum shaderType) -> GLuint
	{
		GLuint result = glCreateShader(shaderType);
		GraphicsEngine::HandleError(__FUNCTION__);

		return result;
	}

	auto DrawArrays(GLenum mode, GLint first, GLsizei count) -> void
	{
		glDrawArrays(mode, first, count);
		GraphicsEngine::HandleError(__FUNCTION__);
	}


	auto GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void
	{
		glGetActiveUniform(program, index, bufSize, length, size, type, name);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

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

	auto PolygonMode(GLenum face, GLenum mode) -> void
	{
		glPolygonMode(face, mode);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) -> void
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
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

	auto BindVertexArray(GLuint array) -> void
	{
		glBindVertexArray(array);
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

	auto EnableVertexAttribArray(unsigned int index) -> void
	{
		glEnableVertexAttribArray(index);
		HandleError(__FUNCTION__);
	}

	auto GenBuffers(int n, unsigned int* buffers) -> void
	{
		glGenBuffers(n, buffers);
		HandleError(__FUNCTION__);
	}

	auto GenVertexArrays(GLsizei n, GLuint* arrays) -> void
	{
		glGenVertexArrays(n, arrays);
		HandleError(__FUNCTION__);
	}

	auto GetActiveUniform(GLuint programId, GLuint index) -> Uniform
	{
		const GLsizei bufSize = 16; // maximum name length
		GLint size;
		GLenum type;
		std::string name(bufSize, '\0');
		GLsizei length; // name length
		GLHelpers::GetActiveUniform(programId, index, bufSize, &length, &size, &type, name.data());

		Uniform uniform;
		switch (type)
		{
		case GL_FLOAT_VEC4:
		{
			GLint location = GL::GetUniformLocation(programId, name.data());

			float v[4];
			GL::GetUniformfv(programId, location, v);

			uniform.m_Type = UNIFORM_TYPE_VEC4;
			uniform.m_Name = name.c_str();
			uniform.m_Location = location;
			std::copy(uniform.m_Data.vec4, uniform.m_Data.vec4 + 4, v);

			return uniform;
		}
		}

		// Apparently we're not handling a type that we need to be.
		DebugBreak();
		return Uniform{ .m_Type = UNIFORM_TYPE_EMPTY };
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

	auto GetColorClearValue() -> glm::vec4
	{
		float data[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, data);
		HandleError(__FUNCTION__);

		return glm::vec4(data[0], data[1], data[2], data[3]);
	}

	auto GetPolygonMode() -> PolygonMode
	{
		std::vector<GLint> param(2);
		GLHelpers::GetIntegerv(GL_POLYGON_MODE, param.data());

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

	auto ArrayBufferDataStaticDraw(GLsizeiptr size, const void* data) -> void
	{
		GLHelpers::BufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	auto ElementArrayBufferDataStaticDraw(GLsizeiptr size, const void* data) -> void
	{
		GLHelpers::BufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	auto SetPolygonMode(PolygonMode mode) -> void
	{
		GLHelpers::PolygonMode(GL_FRONT_AND_BACK, GLHelpers::MapRasterizeModeToGLenum.at(mode));
	}

	auto SetUniform(const Uniform& uniform) -> void
	{
		switch (uniform.m_Type)
		{
		case UNIFORM_TYPE_VEC4:
		{
			const float* v = uniform.m_Data.vec4;
			GL::Uniform4f(uniform.m_Location, v[0], v[1], v[2], v[3]);
			break;
		}
		}
	}

	auto VertexAttribFloatPointer(unsigned int index, int size, bool normalized, int stride, const void* pointer) -> void
	{
		GLHelpers::VertexAttribPointer(index, size, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE, stride, pointer);
	}

	auto ClearColorBuffer() -> void
	{
		glClear(GL_COLOR_BUFFER_BIT);
		HandleError(__FUNCTION__);
	}

	auto CreateFragmentShader() -> GLuint
	{
		return GLHelpers::CreateShader(GL_FRAGMENT_SHADER);
	}

	auto CreateGeometryShader() -> GLuint
	{
		return GLHelpers::CreateShader(GL_GEOMETRY_SHADER);
	}

	auto CreateVertexShader() -> GLuint
	{
		return GLHelpers::CreateShader(GL_VERTEX_SHADER);
	}

	auto DrawArraysAsTriangles(int first, int count) -> void
	{
		GLHelpers::DrawArrays(GL_TRIANGLES, first, count);
	}

	auto GetCurrentProgram() -> GLuint
	{
		GLint prog = 0;
		GLHelpers::GetIntegerv(GL_CURRENT_PROGRAM, &prog);
		
		return prog;
	}

	auto GetNumActiveUniformVariables(GLuint programId) -> GLint
	{
		if (programId == 0)
			return 0;

		GLint count;
		GL::GetProgramiv(programId, GL_ACTIVE_UNIFORMS, &count);

		return count;
	}

	auto GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void
	{
		glGetShaderInfoLog(shader, maxLength, length, infoLog);
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

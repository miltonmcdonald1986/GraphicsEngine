#include "pch.h"
#include "SafeGL.h"

#include "Error.h"

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

	auto Clear(GLbitfield mask) -> void
	{
		glClear(mask);
		HandleError(__FUNCTION__);
	}

	auto ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) -> void
	{
		glClearColor(red, green, blue, alpha);
		HandleError(__FUNCTION__);
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

	auto DeleteShader(GLuint shader) -> void
	{
		glDeleteShader(shader);
		HandleError(__FUNCTION__);
	}

	auto DrawArrays(GLenum mode, GLint first, GLsizei count) -> void
	{
		glDrawArrays(mode, first, count);
		HandleError(__FUNCTION__);
	}

	auto EnableVertexAttribArray(GLuint index) -> void
	{
		glEnableVertexAttribArray(index);
		HandleError(__FUNCTION__);
	}

	auto GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void
	{
		glGetActiveUniform(program, index, bufSize, length, size, type, name);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto GenBuffers(GLsizei n, GLuint* buffers) -> void
	{
		glGenBuffers(n, buffers);
		HandleError(__FUNCTION__);
	}

	auto GenVertexArrays(GLsizei n, GLuint* arrays) -> void
	{
		glGenVertexArrays(n, arrays);
		HandleError(__FUNCTION__);
	}

	auto GetFloatv(GLenum pname, GLfloat* data) -> void
	{
		glGetFloatv(pname, data);
		HandleError(__FUNCTION__);
	}

	auto GetIntegerv(GLenum pname, GLint* data) -> void
	{
		glGetIntegerv(pname, data);
		HandleError(__FUNCTION__);
	}

	auto GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void
	{
		glGetProgramInfoLog(program, maxLength, length, infoLog);
		HandleError(__FUNCTION__);
	}

	auto GetProgramiv(GLuint program, GLenum pname, GLint* params) -> void
	{
		glGetProgramiv(program, pname, params);
		HandleError(__FUNCTION__);
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

	auto PolygonMode(GLenum face, GLenum mode) -> void
	{
		glPolygonMode(face, mode);
		GraphicsEngine::HandleError(__FUNCTION__);
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

	auto VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) -> void
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		HandleError(__FUNCTION__);
	}

}

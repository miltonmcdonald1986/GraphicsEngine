#include "pch.h"
#include "SafeGL.h"

#include "Error.h"

namespace GraphicsEngine::GL
{

	auto AttachShader(GLuint program, GLuint shader) -> void
	{
		glAttachShader(program, shader);
		HandleError();
	}

	auto BindBuffer(GLenum target, GLuint buffer) -> void
	{
		glBindBuffer(target, buffer);
		HandleError();
	}

	auto BindVertexArray(GLuint array) -> void
	{
		glBindVertexArray(array);
		HandleError();
	}

	auto BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) -> void	// NOSONAR
	{
		glBufferData(target, size, data, usage);
		HandleError();
	}

	auto Clear(GLbitfield mask) -> void
	{
		glClear(mask);
		HandleError();
	}

	auto ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) -> void
	{
		glClearColor(red, green, blue, alpha);
		HandleError();
	}

	auto CompileShader(GLuint shader) -> void
	{
		glCompileShader(shader);
		HandleError();
	}

	auto CreateProgram() -> GLuint
	{
		GLuint result = glCreateProgram();
		HandleError();

		return result;
	}

	auto CreateShader(GLenum shaderType) -> GLuint
	{
		GLuint result = glCreateShader(shaderType);
		HandleError();

		return result;
	}

	auto DeleteShader(GLuint shader) -> void
	{
		glDeleteShader(shader);
		HandleError();
	}

	auto DrawArrays(GLenum mode, GLint first, GLsizei count) -> void
	{
		glDrawArrays(mode, first, count);
		HandleError();
	}

	auto DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) -> void	// NOSONAR
	{
		glDrawElements(mode, count, type, indices);
		HandleError();
	}

	auto EnableVertexAttribArray(GLuint index) -> void
	{
		glEnableVertexAttribArray(index);
		HandleError();
	}

	auto GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void
	{
		glGetActiveUniform(program, index, bufSize, length, size, type, name);
		GraphicsEngine::HandleError();
	}

	auto GenBuffers(GLsizei n, GLuint* buffers) -> void
	{
		glGenBuffers(n, buffers);
		HandleError();
	}

	auto GenVertexArrays(GLsizei n, GLuint* arrays) -> void
	{
		glGenVertexArrays(n, arrays);
		HandleError();
	}

	auto GetFloatv(GLenum pname, GLfloat* data) -> void
	{
		glGetFloatv(pname, data);
		HandleError();
	}

	auto GetIntegerv(GLenum pname, GLint* data) -> void
	{
		glGetIntegerv(pname, data);
		HandleError();
	}

	auto GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void
	{
		glGetProgramInfoLog(program, maxLength, length, infoLog);
		HandleError();
	}

	auto GetProgramiv(GLuint program, GLenum pname, GLint* params) -> void
	{
		glGetProgramiv(program, pname, params);
		HandleError();
	}

	auto GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void
	{
		glGetShaderInfoLog(shader, maxLength, length, infoLog);
		HandleError();
	}

	auto GetShaderiv(GLuint shader, GLenum pname, GLint* params) -> void
	{
		glGetShaderiv(shader, pname, params);
		HandleError();
	}

	auto GetUniformfv(GLuint program, GLint location, GLfloat* params) -> void
	{
		glGetUniformfv(program, location, params);
		HandleError();
	}

	auto GetUniformLocation(GLuint program, const GLchar* name) -> GLint
	{
		GLint result = glGetUniformLocation(program, name);
		HandleError();

		return result;
	}

	auto LinkProgram(GLuint program) -> void
	{
		glLinkProgram(program);
		HandleError();
	}

	auto PolygonMode(GLenum face, GLenum mode) -> void
	{
		glPolygonMode(face, mode);
		GraphicsEngine::HandleError();
	}

	auto ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) -> void
	{
		glShaderSource(shader, count, string, length);
		HandleError();
	}

	auto Uniform1f(GLint location, GLfloat v) -> void
	{
		glUniform1f(location, v);
		HandleError();
	}

	auto Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) -> void
	{
		glUniform4f(location, v0, v1, v2, v3);
		HandleError();
	}

	auto UseProgram(GLuint program) -> void
	{
		glUseProgram(program);
		HandleError();
	}

	auto VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) -> void	// NOSONAR
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		HandleError();
	}

}

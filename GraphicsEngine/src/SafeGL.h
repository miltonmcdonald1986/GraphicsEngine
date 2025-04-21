#pragma once

#include "glad/glad.h"

namespace GraphicsEngine::GL
{

	auto ActiveTexture(GLenum texture) -> void;
	auto AttachShader(GLuint program, GLuint shader) -> void;
	auto BindBuffer(GLenum target, GLuint buffer) -> void;
	auto BindTexture(GLenum target, GLuint texture) -> void;
	auto BindVertexArray(GLuint array) -> void;
	auto BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) -> void;
	auto Clear(GLbitfield mask) -> void;
	auto ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) -> void;
	auto CompileShader(GLuint shader) -> void;
	auto CreateProgram() -> GLuint;
	auto CreateShader(GLenum shaderType) -> GLuint;
	auto DeleteShader(GLuint shader) -> void;
	auto DrawArrays(GLenum mode, GLint first, GLsizei count) -> void;
	auto DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) -> void;
	auto EnableVertexAttribArray(GLuint index) -> void;
	auto GenTextures(GLsizei n, GLuint* textures) -> void;
	auto GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void;
	auto GenBuffers(GLsizei n, GLuint* buffers) -> void;
	auto GenerateMipmap(GLenum target) -> void;
	auto GenVertexArrays(GLsizei n, GLuint* arrays) -> void;
	auto GetFloatv(GLenum pname, GLfloat* data) -> void;
	auto GetIntegerv(GLenum pname, GLint* data) -> void;
	auto GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void;
	auto GetProgramiv(GLuint program, GLenum pname, GLint* params) -> void;
	auto GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void;
	auto GetShaderiv(GLuint shader, GLenum pname, GLint* params) -> void;
	auto GetUniformfv(GLuint program, GLint location, GLfloat* params) -> void;
	auto GetUniformiv(GLuint program, GLint location, GLint* params) -> void;
	auto GetUniformLocation(GLuint program, const GLchar* name) -> GLint;
	auto LinkProgram(GLuint program) -> void;
	auto PolygonMode(GLenum face, GLenum mode) -> void;
	auto ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) -> void;
	auto TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data) -> void;
	auto TexParameteri(GLenum target, GLenum pname, GLint param) -> void;
	auto Uniform1f(GLint location, GLfloat v) -> void;
	auto Uniform1i(GLint location, GLint v0) -> void;
	auto Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) -> void;
	auto UseProgram(GLuint program) -> void;
	auto VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) -> void;

}

#pragma once

#include <string>
#include <variant>
#include <vector>

#include "glm/vec4.hpp"

#include "GraphicsEngine/fwd.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::GL
{

	enum class StateVariable
	{
		ColorClearValue,
		PolygonMode
	};

	enum class PolygonMode
	{
		Point,
		Line,
		Fill
	};

	using UniformVariant = std::variant<
		std::monostate, 
		glm::vec4>;

	struct Uniform
	{
		std::string m_Name;
		GLint m_Location;
		UniformVariant m_Value;
	};

	// Get data
	GRAPHICSENGINE_API auto GetActiveUniform(GLuint programId, GLuint index) -> Uniform;
	GRAPHICSENGINE_API auto GetActiveUniforms(GLuint programId) -> std::vector<Uniform>;
	GRAPHICSENGINE_API auto GetPolygonMode() -> PolygonMode;
	GRAPHICSENGINE_API auto GetCurrentProgram() -> GLuint;
	GRAPHICSENGINE_API auto GetLinkStatus(GLuint program) -> bool;
	GRAPHICSENGINE_API auto GetNumActiveUniformVariables(GLuint programId) -> GLint;

	// Set data
	GRAPHICSENGINE_API auto SetPolygonMode(PolygonMode mode) -> void;
	GRAPHICSENGINE_API auto SetUniform(const Uniform& uniform) -> void;

	// Do things
	GRAPHICSENGINE_API auto ClearColorBuffer() -> void;

	// OpenGL wrappers with error handling and logging built in
	GRAPHICSENGINE_API auto AttachShader(GLuint program, GLuint shader) -> void;
	GRAPHICSENGINE_API auto BindBuffer(GLenum target, GLuint buffer) -> void;
	GRAPHICSENGINE_API auto BindVertexArray(GLuint array) -> void;
	GRAPHICSENGINE_API auto BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) -> void;
	GRAPHICSENGINE_API auto ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) -> void;
	GRAPHICSENGINE_API auto CompileShader(GLuint shader) -> void;
	GRAPHICSENGINE_API auto CreateProgram() -> GLuint;
	GRAPHICSENGINE_API auto CreateShader(GLenum shaderType) -> GLuint;
	GRAPHICSENGINE_API auto GenVertexArrays(GLsizei n, GLuint* arrays) -> void;
	GRAPHICSENGINE_API auto GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void;
	GRAPHICSENGINE_API auto GetFloatv(StateVariable pname, GLfloat* data) -> void;
	GRAPHICSENGINE_API auto GetIntegerv(StateVariable pname, GLint* data) -> void;
	GRAPHICSENGINE_API auto GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) -> void;
	GRAPHICSENGINE_API auto GetShaderiv(GLuint shader, GLenum pname, GLint* params) -> void;
	GRAPHICSENGINE_API auto GetUniformfv(GLuint program, GLint location, GLfloat* params) -> void;
	GRAPHICSENGINE_API auto GetUniformLocation(GLuint program, const GLchar* name) -> GLint;
	GRAPHICSENGINE_API auto LinkProgram(GLuint program) -> void;
	GRAPHICSENGINE_API auto ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) -> void;
	GRAPHICSENGINE_API auto Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) -> void;
	GRAPHICSENGINE_API auto UseProgram(GLuint program) -> void;

}

#pragma once

#include <vector>

#include "glm/vec4.hpp"

#include "GraphicsEngine/Uniform.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::GL
{

	enum class PolygonMode
	{
		Point,
		Line,
		Fill
	};

	// Get data
	GRAPHICSENGINE_API auto GetActiveUniform(unsigned int programId, unsigned int index) -> Uniform;
	GRAPHICSENGINE_API auto GetActiveUniforms(unsigned int programId) -> std::vector<Uniform>;
	GRAPHICSENGINE_API auto GetColorClearValue() -> glm::vec4;
	GRAPHICSENGINE_API auto GetPolygonMode() -> PolygonMode;
	GRAPHICSENGINE_API auto GetCompileStatus(unsigned int shaderId) -> bool;
	GRAPHICSENGINE_API auto GetDeleteStatus(unsigned int shaderId) -> bool;
	GRAPHICSENGINE_API auto GetCurrentProgram() -> unsigned int;
	GRAPHICSENGINE_API auto GetLinkStatus(unsigned int program) -> bool;
	GRAPHICSENGINE_API auto GetNumActiveUniformVariables(unsigned int programId) -> int;

	// Set data
	GRAPHICSENGINE_API auto ArrayBufferDataStaticDraw(long long int size, const void* data) -> void;
	GRAPHICSENGINE_API auto ElementArrayBufferDataStaticDraw(long long int size, const void* data) -> void;
	GRAPHICSENGINE_API auto SetPolygonMode(PolygonMode mode) -> void;
	GRAPHICSENGINE_API auto SetUniform(const Uniform& uniform) -> void;

	// Do things
	GRAPHICSENGINE_API auto BindArrayBuffer(unsigned int buffer) -> void;
	GRAPHICSENGINE_API auto BindElementArrayBuffer(unsigned int buffer) -> void;
	GRAPHICSENGINE_API auto ClearColorBuffer() -> void;
	GRAPHICSENGINE_API auto CreateFragmentShader() -> unsigned int;
	GRAPHICSENGINE_API auto CreateGeometryShader() -> unsigned int;
	GRAPHICSENGINE_API auto CreateVertexShader() -> unsigned int;

	// OpenGL wrappers with error handling and logging built in
	GRAPHICSENGINE_API auto AttachShader(unsigned int program, unsigned int shader) -> void;
	GRAPHICSENGINE_API auto BindVertexArray(unsigned int array) -> void;
	GRAPHICSENGINE_API auto ClearColor(float red, float green, float blue, float alpha) -> void;
	GRAPHICSENGINE_API auto CompileShader(unsigned int shader) -> void;
	GRAPHICSENGINE_API auto CreateProgram() -> unsigned int;
	GRAPHICSENGINE_API auto GenVertexArrays(int n, unsigned int* arrays) -> void;
	GRAPHICSENGINE_API auto GetShaderInfoLog(unsigned int shader, int maxLength, int* length, char* infoLog) -> void;
	GRAPHICSENGINE_API auto GetUniformfv(unsigned int program, int location, float* params) -> void;
	GRAPHICSENGINE_API auto GetUniformLocation(unsigned int program, const char* name) -> int;
	GRAPHICSENGINE_API auto LinkProgram(unsigned int program) -> void;
	GRAPHICSENGINE_API auto ShaderSource(unsigned int shader, int count, const char** string, const int* length) -> void;
	GRAPHICSENGINE_API auto Uniform4f(int location, float v0, float v1, float v2, float v3) -> void;
	GRAPHICSENGINE_API auto UseProgram(unsigned int program) -> void;

}

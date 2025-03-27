#pragma once

#include <filesystem>
#include <optional>

#include "glad/glad.h"

#include "GL.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::Shader
{

	/// <summary>
	/// Compile a fragment shader from a file containing the source code.
	/// </summary>
	/// <param name="path"> A path to the fragment shader source code. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileFragmentShader(const std::filesystem::path& path) -> std::optional<GLuint>;

	/// <summary>
	/// Compile a fragment shader from a string containing the source code.
	/// </summary>
	/// <param name="source"> The source code for the fragment shader. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileFragmentShader(const std::string& source) -> std::optional<GLuint>;

	/// <summary>
	/// Compile a shader.
	/// </summary>
	/// <param name="shaderType"> Specifies the type of shader to be created. </param>
	/// <param name="source"> The source code for the shader. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileShader(GL::ShaderType shaderType, const std::string& source) -> std::optional<GLuint>;

	/// <summary>
	/// Compile a vertex shader from a file containing the source code.
	/// </summary>
	/// <param name="path"> A path to the vertex shader source code. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileVertexShader(const std::filesystem::path& path) -> std::optional<GLuint>;

	/// <summary>
	/// Compile a vertex shader from a string containing the source code.
	/// </summary>
	/// <param name="source"> The source code for the vertex shader. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileVertexShader(const std::string& source) -> std::optional<GLuint>;

	/// <summary>
	/// Link a program object.
	/// </summary>
	/// <param name="shaders"> A vector of identifiers for the shader objects to be attached to this program. </param>
	/// <returns> An identifier for the program object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto LinkProgram(const std::vector<GLuint>& shaders) -> std::optional<GLuint>;

	/// <summary>
	/// Check the delete status parameter for a shader object.
	/// </summary>
	/// <param name="shader"> An identifier for the shader object to check. </param>
	/// <returns> true, if the shader is deleted; false if it is not; nullopt if there was an error checking the status. </returns>
	GRAPHICSENGINE_API auto ShaderIsDeleted(GLuint shader) -> std::optional<bool>;

}

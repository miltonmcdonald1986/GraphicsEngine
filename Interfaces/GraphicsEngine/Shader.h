#pragma once

#include <filesystem>

#include "GraphicsEngineImpExp.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct GEshader GEshader;

	GRAPHICSENGINE_API GEshader*	geCreateShaderFromFiles(const char* vert, const char* geom, const char* frag);
	GRAPHICSENGINE_API GEshader*	geCreateShaderFromStrings(const char* vert, const char* geom, const char* frag);
	GRAPHICSENGINE_API void			geDestroyShader(GEshader* pShader);

#ifdef __cplusplus
}
#endif

namespace GraphicsEngine::Shader
{

	/// <summary>
	/// Compile a fragment shader from a file containing the source code.
	/// </summary>
	/// <param name="path"> A path to the fragment shader source code. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileFragmentShader(const std::filesystem::path& path) -> std::optional<unsigned int>;

	/// <summary>
	/// Compile a fragment shader from a string containing the source code.
	/// </summary>
	/// <param name="source"> The source code for the fragment shader. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileFragmentShader(const std::string& source) -> std::optional<unsigned int>;

	/// <summary>
	/// Compile a vertex shader from a file containing the source code.
	/// </summary>
	/// <param name="path"> A path to the vertex shader source code. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileVertexShader(const std::filesystem::path& path) -> std::optional<unsigned int>;

	/// <summary>
	/// Compile a vertex shader from a string containing the source code.
	/// </summary>
	/// <param name="source"> The source code for the vertex shader. </param>
	/// <returns> An identifier for the shader object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto CompileVertexShader(const std::string& source) -> std::optional<unsigned int>;

	/// <summary>
	/// Link a program object.
	/// </summary>
	/// <param name="shaders"> A vector of identifiers for the shader objects to be attached to this program. </param>
	/// <returns> An identifier for the program object, if successful; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto LinkProgram(const std::vector<unsigned int>& shaders) -> std::optional<unsigned int>;

}

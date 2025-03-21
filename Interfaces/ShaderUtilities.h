#pragma once

#include <filesystem>
#include <optional>

#include "glad/glad.h"

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::ShaderUtilities
{

	GRAPHICSENGINE_API std::optional<GLuint> CompileFragmentShader(const std::filesystem::path& path);
	GRAPHICSENGINE_API std::optional<GLuint> CompileFragmentShader(const std::string& source);
	GRAPHICSENGINE_API std::optional<GLuint> CompileVertexShader(const std::filesystem::path& path);
	GRAPHICSENGINE_API std::optional<GLuint> CompileVertexShader(const std::string& source);
	GRAPHICSENGINE_API std::optional<GLuint> LinkProgram(const std::vector<GLuint>& shaders);
	GRAPHICSENGINE_API std::optional<bool> ShaderIsDeleted(GLuint shader);

}

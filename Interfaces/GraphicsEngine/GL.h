#pragma once

#include <vector>

#include "glm/vec4.hpp"

#include "GraphicsEngine/Uniform.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::GL
{

	// Get data
	GRAPHICSENGINE_API auto GetActiveUniform(unsigned int programId, unsigned int index) -> GEuniform;
	GRAPHICSENGINE_API auto GetActiveUniforms(unsigned int programId) -> std::vector<GEuniform>;
	GRAPHICSENGINE_API auto GetCurrentProgram() -> unsigned int;
	GRAPHICSENGINE_API auto GetNumActiveUniformVariables(unsigned int programId) -> int;

	// Set data
	GRAPHICSENGINE_API auto SetUniform(const GEuniform& uniform) -> void;

}

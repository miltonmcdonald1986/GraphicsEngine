#pragma once

#include <optional>
#include <vector>

#include "glad/glad.h"

#include "glm/vec3.hpp"

#include "GraphicsEngine/GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	/// <summary>
	/// 
	/// </summary>
	/// <param name="vertices"></param>
	/// <param name="indices"></param>
	/// <returns></returns>
	GRAPHICSENGINE_API auto AddIndexedPoints(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices) -> std::optional<GLuint>;

}

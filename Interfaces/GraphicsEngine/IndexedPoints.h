#pragma once

#include <optional>

#include "glm/fwd.hpp"

#include "GraphicsEngine/fwd.h"
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

#pragma once

#include "GraphicsEngineFwd.h"
#include "GraphicsEngineImpExp.h"

#include "glm/fwd.hpp"

namespace GraphicsEngine
{

	class IAttribute
	{
	public:
		virtual ~IAttribute() = default;
	};

	GRAPHICSENGINE_API auto CreateAttribute(const std::vector<glm::vec3>& data) -> IAttributePtr;

}

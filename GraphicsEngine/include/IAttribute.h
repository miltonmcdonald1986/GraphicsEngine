#pragma once

#include "glm/fwd.hpp"

#include "GraphicsEngineFwd.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	class IAttribute
	{
	public:
		virtual ~IAttribute() = default;
	};

	GRAPHICSENGINE_API auto CreateAttribute(const std::vector<glm::vec3>& data) -> IAttributePtr;

}

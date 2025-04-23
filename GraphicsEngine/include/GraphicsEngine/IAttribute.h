#pragma once

#include <memory>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "GraphicsEngine/DllImpExp.h"

namespace GraphicsEngine
{

	class IAttribute
	{
	public:
		virtual ~IAttribute() = default;
	};

	using IAttributePtr = std::shared_ptr<IAttribute>;
	using IAttributes = std::vector<IAttributePtr>;

	GRAPHICSENGINE_API auto CreateAttribute(const std::vector<glm::vec2>& data) -> IAttributePtr;
	GRAPHICSENGINE_API auto CreateAttribute(const std::vector<glm::vec3>& data) -> IAttributePtr;

}

/// @file IAttribute.h
/// @brief Interface for an array of generic vertex attribute data.
/// @author Milton McDonald
/// @date 2025-04-29
/// @copyright MIT License

#pragma once

#include <vector>

#include "GraphicsEngine/DllImpExp.h"

namespace GraphicsEngine
{

	/// @brief This interface represents a generic vertex attribute.
	class IAttribute
	{
	public:
		virtual ~IAttribute() = default;
	};

	using IAttributePtr = std::shared_ptr<IAttribute>;
	using IAttributes = std::vector<IAttributePtr>;

	/// @brief Creates a new attribute object of type GL_FLOAT having two components.
	/// @param data The data which will be copied into the buffer bound to GL_ARRAY_BUFFER.
	/// @return A shared pointer to the new attribute object.
	GRAPHICSENGINE_API auto CreateAttribute(const std::vector<glm::vec2>& data) -> IAttributePtr;

	/// @brief Creates a new attribute object of type GL_FLOAT having three components.
	/// @param data The data which will be copied into the buffer bound to GL_ARRAY_BUFFER.
	/// @return A shared pointer to the new attribute object.
	GRAPHICSENGINE_API auto CreateAttribute(const std::vector<glm::vec3>& data) -> IAttributePtr;

}

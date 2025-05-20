#pragma once

#include "IEngine.h"
#include "dll_export.h"

namespace graphics_engine::entities
{

	/// @brief Interface for creating entity objects.
	class IEntityFactory
	{
	public:

		/// @brief Virtual destructor for IEntityFactory.
		virtual ~IEntityFactory() = default;

		/// @brief Adds a cube entity with the given attributes.
		/// @param[in] attributes The attributes to apply to the cube.
		/// @return A pointer to the created entity.
		/// 
		/// @note	Each attribute must contain **24 vertices** due to the underlying **Element Buffer Object (EBO)**
		///			in the generated cube.
		/// @note	Attribute factory functions for **Pos, TexCoords**, etc., which generate **24-vertex attributes**,
		///			can be found in @ref attribute_factory.h.
		virtual auto AddCube(const attributes::Attributes& attributes) -> Entity* = 0;
	};
	
	/// @brief Alias for a shared pointer to IEntityFactory.
	using IEntityFactoryPtr = std::shared_ptr<IEntityFactory>;

	/// @brief Creates an IEntityFactory instance.
	/// @param spEngine Shared pointer to the IEngine instance.
	/// @return A shared pointer to the created IEntityFactory.
	DLLEXPORT auto CreateEntityFactory(IEnginePtr spEngine) -> IEntityFactoryPtr;

}

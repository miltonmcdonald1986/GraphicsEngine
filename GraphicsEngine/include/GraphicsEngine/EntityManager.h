#pragma once

#include "Entity.h"
#include "IAttribute.h"
#include "Types.h"

namespace GraphicsEngine
{

	/// @brief Manages the lifecycle and retrieval of Entity objects within the graphics engine.
	///
	/// Provides functionality for adding entities, accessing individual entities by ID, 
	/// and retrieving a list of all registered entity IDs.
	class EntityManager
	{
	public:

		/// @brief Virtual destructor for proper cleanup of derived classes.
		virtual ~EntityManager() = default;

		/// @brief Adds a new entity to the manager.
		/// @param attributes Vertex attributes defining the entity's geometry.
		/// @param indices Optional index buffer specifying the order in which vertices are drawn.
		/// @return Pointer to the newly created Entity.
		virtual auto AddEntity(
			const IAttributes& attributes, 
			const Indices& indices = {}
		) -> Entity* = 0;

		/// @brief Retrieves an entity by its unique ID.
		/// @param id The identifier of the entity.
		/// @return Pointer to the requested Entity, or `nullptr` if not found.
		virtual auto GetEntity(
			EntityId id
		) -> Entity* = 0;
		
		/// @brief Gets a collection of all registered entity IDs.
		/// @return A list of entity IDs currently managed by the EntityManager.
		virtual auto GetEntityIds(
		) const -> EntityIds = 0;
	};

}

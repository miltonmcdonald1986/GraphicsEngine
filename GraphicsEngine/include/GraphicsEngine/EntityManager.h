#pragma once

#include "Entity.h"
#include "IAttribute.h"
#include "Types.h"

namespace GraphicsEngine
{

	class EntityManager
	{
	public:
		virtual ~EntityManager() = default;

		virtual auto AddEntity(
			const IAttributes& attributes, 
			const Indices& indices = {}
		) -> Entity* = 0;

		virtual auto GetEntity(
			EntityId id
		) -> Entity* = 0;
		
		virtual auto GetEntityIds(
		) const -> EntityIds = 0;
	};

}

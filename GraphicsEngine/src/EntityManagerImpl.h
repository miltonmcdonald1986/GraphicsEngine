#pragma once

#include "EntityManager.h"

#include <memory>
#include <unordered_map>

#include "Entity.h"

namespace GraphicsEngine
{

	class IEngine;

	class EntityManagerImpl : public EntityManager
	{
	public:
		
		explicit EntityManagerImpl(IEngine* pEngine);

		~EntityManagerImpl() override = default;

		auto AddEntity(
			const Types::VertexAttributes& attributes, 
			const Types::Indices& indices
		) -> Entity* override;

		auto GetEntity(
			Types::EntityId id
		) -> Entity* override;

		auto GetEntityIds(
		) const ->Types::EntityIds override;

	private:

		[[maybe_unused]] IEngine* m_pEngine;
		std::unordered_map<Types::EntityId, Entity> m_Entities;

	};

	using EntityManagerImplPtr = std::unique_ptr<EntityManagerImpl>;
	auto CreateEntityManagerImpl(IEngine* pEngine) -> EntityManagerImplPtr;

}

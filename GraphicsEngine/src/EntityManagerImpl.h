#pragma once

#include "EntityManager.h"

#include <memory>
#include <unordered_map>

#include "Entity.h"

namespace GraphicsEngine
{

	class EntityManagerImpl : public EntityManager
	{
	public:
		
		explicit EntityManagerImpl(IEngine* pEngine);

		~EntityManagerImpl() override = default;

		auto AddEntity(
			const IAttributes& attributes, 
			const Indices& indices
		) -> Entity* override;

		auto GetEntity(
			EntityId id
		) -> Entity* override;

		auto GetEntityIds(
		) const -> EntityIds override;

	private:

		IEngine* m_pEngine;
		std::unordered_map<EntityId, Entity> m_Entities;

	};

	using EntityManagerImplPtr = std::unique_ptr<EntityManagerImpl>;
	auto CreateEntityManagerImpl(IEngine* pEngine) -> EntityManagerImplPtr;

}



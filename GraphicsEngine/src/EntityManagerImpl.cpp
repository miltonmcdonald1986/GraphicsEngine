#include "EntityManagerImpl.h"

#include "IEngine.h"

namespace graphics_engine::entities
{

	auto CreateEntityManagerImpl(
		IEngine* pEngine
	) -> EntityManagerImplPtr
	{
		return std::make_unique<EntityManagerImpl>(pEngine);
	}

	EntityManagerImpl::EntityManagerImpl(
		IEngine* pEngine
	)
		: m_pEngine(pEngine)
	{
	}

	auto EntityManagerImpl::AddEntity(
		const attributes::Attributes& attributes, 
		const Types::Indices& indices
	) -> Entity*
	{
		Entity entity(attributes, indices);
		m_Entities.try_emplace(entity.kEntityId, entity);
		return &m_Entities.at(entity.kEntityId);
	}

	auto EntityManagerImpl::GetEntity(
		Types::EntityId id
	) -> Entity*
	{
		if (m_Entities.contains(id))
			return &m_Entities.at(id);
		else
			return nullptr;
	}

	auto EntityManagerImpl::GetEntityIds(
	) const -> Types::EntityIds
	{
		return Types::EntityIds(std::views::keys(m_Entities).begin(), std::views::keys(m_Entities).end());
	}

}

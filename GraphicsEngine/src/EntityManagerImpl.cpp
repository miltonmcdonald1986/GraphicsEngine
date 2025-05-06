#include "EntityManagerImpl.h"

#include "IEngine.h"

namespace GraphicsEngine
{

	auto GraphicsEngine::CreateEntityManagerImpl(
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
		const IAttributes& attributes, 
		const Indices& indices
	) -> Entity*
	{
		Entity entity(attributes, indices);
		m_Entities.try_emplace(entity.ENTITY_ID, entity);
		return &m_Entities.at(entity.ENTITY_ID);
	}

	auto EntityManagerImpl::GetEntity(
		EntityId id
	) -> Entity*
	{
		if (m_Entities.contains(id))
			return &m_Entities.at(id);
		else
			return nullptr;
	}

	auto EntityManagerImpl::GetEntityIds(
	) const -> EntityIds
	{
		return EntityIds(std::views::keys(m_Entities).begin(), std::views::keys(m_Entities).end());
	}

}

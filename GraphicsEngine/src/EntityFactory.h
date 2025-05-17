#pragma once

#include "IEntityFactory.h"

namespace graphics_engine::entities
{

	class EntityFactory : public IEntityFactory
	{
	public:
		explicit EntityFactory(IEnginePtr spEngine);
		~EntityFactory() override = default;

		auto AddCube(const attributes::Attributes& attributes) -> Entity* override;

	private:
		IEnginePtr m_spEngine = nullptr;
	};

}

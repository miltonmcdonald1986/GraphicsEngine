#pragma once

#include "IEntityFactory.h"

namespace graphics_engine
{

	class EntityFactory : public IEntityFactory
	{
	public:
		explicit EntityFactory(IEnginePtr spEngine);
		~EntityFactory() override = default;

		auto AddCube(const Attributes& attributes) -> Entity* override;

	private:
		IEnginePtr m_spEngine = nullptr;
	};

}

#pragma once

#include "IEntityFactory.h"

namespace GraphicsEngine
{

	class EntityFactory : public IEntityFactory
	{
	public:
		explicit EntityFactory(IEnginePtr spEngine);
		~EntityFactory() override = default;

		auto AddCube(const IAttributes& attributes) -> Entity* override;

	private:
		IEnginePtr m_spEngine = nullptr;
	};

}

#pragma once

#include "IEntityFactory.h"

namespace GraphicsEngine
{

	class EntityFactory : public IEntityFactory
	{
	public:
		EntityFactory(IEnginePtr spEngine);
		~EntityFactory() override = default;

		auto CreateCubeTextured(IShaderPtr spShader, ITextures textures) -> IEntityPtr override;

	private:
		IEnginePtr m_spEngine = nullptr;
	};

}

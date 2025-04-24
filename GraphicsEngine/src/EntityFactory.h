#pragma once

#include "IEntityFactory.h"

namespace GraphicsEngine
{

	class EntityFactory : public IEntityFactory
	{
	public:
		explicit EntityFactory(IEnginePtr spEngine);
		~EntityFactory() override = default;

		auto CreateCubeTextured(IShaderPtr spShader, const ITextures& textures) -> IEntityPtr override;

	private:
		IEnginePtr m_spEngine = nullptr;
	};

}

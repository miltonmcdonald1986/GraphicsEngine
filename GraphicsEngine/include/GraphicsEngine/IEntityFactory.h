#pragma once

#include "IEngine.h"
#include "IEntity.h"
#include "ITexture.h"
#include "DllImpExp.h"

namespace GraphicsEngine
{

	class IEntityFactory
	{
	public:
		virtual ~IEntityFactory() = default;

		virtual auto CreateCubeTextured(Id shaderId, const ITextures& textures) -> IEntityPtr = 0;
	};

	using IEntityFactoryPtr = std::shared_ptr<IEntityFactory>;
	GRAPHICSENGINE_API auto CreateEntityFactory(IEnginePtr spEngine) -> IEntityFactoryPtr;

}

#pragma once

#include <vector>
#include "GraphicsEngine/Entity.h"
#include "GraphicsEngine/Types.h"

namespace GraphicsEngine
{

	struct Entity;

	class IEngine;
	using IEnginePtr = std::shared_ptr<IEngine>;

	class ITexture;
	using ITexturePtr = std::shared_ptr<ITexture>;
	using ITextures = std::vector<ITexturePtr>;

}

namespace Utilities
{

	auto CreateTenTexturedCubes(GraphicsEngine::IEnginePtr spEngine) -> std::vector<GraphicsEngine::Entity*>;
	auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::Types::ShaderId, GraphicsEngine::ITextures>;

}

#pragma once

#include <vector>
#include "GraphicsEngine/Entity.h"
#include "GraphicsEngine/Types.h"

namespace Utilities
{

	auto CreateTenTexturedCubes(GraphicsEngine::IEnginePtr spEngine) -> std::vector<GraphicsEngine::Entity*>;
	auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::ShaderId, GraphicsEngine::ITextures>;

}

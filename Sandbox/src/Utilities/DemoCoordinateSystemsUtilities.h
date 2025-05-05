#pragma once

#include <vector>
#include "GraphicsEngine/Types.h"

namespace Utilities
{

	auto CreateTenTexturedCubes(GraphicsEngine::IEnginePtr spEngine) -> GraphicsEngine::IEntities;
	auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::ShaderId, GraphicsEngine::ITextures>;

}

#pragma once

#include <vector>

namespace GraphicsEngine
{

	class IEngine;
	using IEnginePtr = std::shared_ptr<IEngine>;

	class IEntity;
	using IEntityPtr = std::shared_ptr<IEntity>;
	using IEntities = std::vector<IEntityPtr>;

	class IShader;
	using IShaderPtr = std::shared_ptr<IShader>;

	class ITexture;
	using ITexturePtr = std::shared_ptr<ITexture>;
	using ITextures = std::vector<ITexturePtr>;

}

namespace Utilities
{

	auto CreateTenTexturedCubes(GraphicsEngine::IEnginePtr spEngine) -> GraphicsEngine::IEntities;
	auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::IShaderPtr, GraphicsEngine::ITextures>;

}

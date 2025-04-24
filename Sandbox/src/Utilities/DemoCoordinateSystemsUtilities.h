#pragma once

#include <vector>

namespace GraphicsEngine
{

	class IEngine;
	using IEnginePtr = std::shared_ptr<IEngine>;

	class IShader;
	using IShaderPtr = std::shared_ptr<IShader>;

	class ITexture;
	using ITexturePtr = std::shared_ptr<ITexture>;
	using ITextures = std::vector<ITexturePtr>;

}

namespace Utilities
{

	auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::IShaderPtr, GraphicsEngine::ITextures>;

}

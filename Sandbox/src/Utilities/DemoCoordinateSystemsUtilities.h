#pragma once

#include <vector>
#include "GraphicsEngine/Entity.h"
#include "GraphicsEngine/Types.h"

namespace graphics_engine
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

	auto CreateTenTexturedCubes(graphics_engine::IEnginePtr spEngine) -> std::vector<graphics_engine::Entity*>;
	auto PrepareShaderAndTextures(graphics_engine::IEnginePtr spEngine) -> std::pair<graphics_engine::Shader*, graphics_engine::ITextures>;

}

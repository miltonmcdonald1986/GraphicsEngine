#pragma once

#include "GraphicsEngine/GraphicsEngineFwd.h"

namespace GraphicsEngine
{

	class IEntity
	{
	public:
		virtual ~IEntity() = default;

		virtual auto GetId() const -> EntityId = 0;
		virtual auto GetNumIndices() const -> Count = 0;
		virtual auto GetNumVertices() const -> Count = 0;
		virtual auto GetShader() const -> IShaderPtr = 0;
		virtual auto GetTextures() const -> ITextures = 0;
		virtual auto GetVAO() const -> VAO = 0;
		virtual auto SetShader(IShaderPtr spShader) -> void = 0;
		virtual auto SetTextures(const ITextures& textures) -> void = 0;
	};

}

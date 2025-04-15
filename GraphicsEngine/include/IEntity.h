#pragma once

#include "GraphicsEngineFwd.h"

namespace GraphicsEngine
{

	class IEntity
	{
	public:
		virtual ~IEntity() = default;

		virtual auto GetId() const -> unsigned int = 0;
		virtual auto GetNumIndices() const -> unsigned int = 0;
		virtual auto GetNumVertices() const -> unsigned int = 0;
		virtual auto GetShader() const -> IShaderPtr = 0;
		virtual auto GetVAO() const -> unsigned int = 0;
		virtual auto SetShader(IShaderPtr spShader) -> void = 0;
	};

}

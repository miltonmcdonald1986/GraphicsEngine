#pragma once

#include "GraphicsEngineFwd.h"

namespace GraphicsEngine
{

	class IShader
	{
	public:
		virtual ~IShader() = default;

		virtual auto GetId() const -> ShaderId = 0;
		virtual auto GetActiveUniforms() const -> IUniforms = 0;
		virtual auto Use() const -> void = 0;
	};

}

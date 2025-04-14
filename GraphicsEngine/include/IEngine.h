#pragma once

#include "GraphicsEngineFwd.h"
#include "Color.h"
#include "IShader.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	enum class PolygonMode
	{
		Fill,
		Line,
		Point
	};

	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual auto GetBackgroundColor() const -> Color = 0;
		virtual auto GetCurrentShader() const -> IShaderPtr = 0;
		virtual auto GetPolygonMode() const -> PolygonMode = 0;
		virtual auto Render() const -> void = 0;
		virtual auto SetBackgroundColor(const Color& color) -> void = 0;
		virtual auto SetPolygonMode(PolygonMode mode) -> void = 0;
	};

	GRAPHICSENGINE_API auto CreateEngine() -> IEnginePtr;
}

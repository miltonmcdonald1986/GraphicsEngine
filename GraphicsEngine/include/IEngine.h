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

		virtual auto CreateNewEntity(const IAttributes& attributes, const std::optional<Indices>& oIndices = std::nullopt) -> IEntityPtr = 0;
		virtual auto CreateNewShaderFromFiles(const Path& vert, const Path& geom, const Path& frag) -> IShaderPtr = 0;
		virtual auto CreateNewShaderFromSource(const std::string& vert, const std::string& geom, const std::string& frag) -> IShaderPtr = 0;
		virtual auto GetBackgroundColor() const -> Color = 0;
		virtual auto GetCurrentShader() const -> IShaderPtr = 0;
		virtual auto GetPolygonMode() const -> PolygonMode = 0;
		virtual auto Render() const -> void = 0;
		virtual auto SetBackgroundColor(const Color& color) -> void = 0;
		virtual auto SetPolygonMode(PolygonMode mode) -> void = 0;
	};

	GRAPHICSENGINE_API auto CreateEngine() -> IEnginePtr;
}

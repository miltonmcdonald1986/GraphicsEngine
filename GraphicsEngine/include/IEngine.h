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

		virtual auto CreateNewShaderFromFiles(const std::filesystem::path& vert, const std::filesystem::path& geom, const std::filesystem::path& frag) -> IShaderPtr = 0;
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

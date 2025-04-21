#pragma once

#include <optional>

#include "GraphicsEngine/GraphicsEngineFwd.h"
#include "GraphicsEngineImpExp.h"
#include "Types.h"

namespace GraphicsEngine
{

	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual auto CreateNewEntity(const IAttributes& attributes, const std::optional<Indices>& oIndices = std::nullopt) -> IEntityPtr = 0;
		virtual auto CreateNewShaderFromFiles(const Path& vert, const Path& geom, const Path& frag) -> IShaderPtr = 0;
		virtual auto CreateNewShaderFromSource(const String& vert, const String& geom, const String& frag) -> IShaderPtr = 0;
		virtual auto CreateNewTextureFromFile(const String& textureName, const Path& path) -> ITexturePtr = 0;
		virtual auto GetBackgroundColor() const -> Color = 0;
		virtual auto GetCurrentShader() const -> IShaderPtr = 0;
		virtual auto GetLog() const -> ILogPtr = 0;
		virtual auto GetPolygonMode() const -> PolygonMode = 0;
		virtual auto Render() const -> void = 0;
		virtual auto SetBackgroundColor(const Color& color) -> void = 0;
		virtual auto SetPolygonMode(PolygonMode mode) -> void = 0;
	};

	GRAPHICSENGINE_API auto CreateEngine() -> IEnginePtr;

}

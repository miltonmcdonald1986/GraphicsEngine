#pragma once

#include <filesystem>
#include <optional>

#include "IAttribute.h"
#include "ICamera.h"
#include "IEntity.h"
#include "ILog.h"
#include "Types.h"

namespace GraphicsEngine
{

	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual auto CreateNewEntity(const IAttributes& attributes, const std::vector<unsigned int>& indices = {}) -> IEntityPtr = 0;
		virtual auto CreateNewShaderFromFiles(const std::filesystem::path& vert, const std::filesystem::path& geom, const std::filesystem::path& frag) -> IShaderPtr = 0;
		virtual auto CreateNewShaderFromSource(std::string_view vert, std::string_view geom, std::string_view frag) -> IShaderPtr = 0;
		virtual auto CreateNewTextureFromFile(std::string_view textureName, const std::filesystem::path& path) -> ITexturePtr = 0;
		virtual auto GetBackgroundColor() const -> Color = 0;
		virtual auto GetCamera() const -> ICameraPtr = 0;
		virtual auto GetCurrentShader() const -> IShaderPtr = 0;
		virtual auto GetLog() const -> ILogPtr = 0;
		virtual auto GetPolygonMode() const -> PolygonMode = 0;
		virtual auto Render() const -> void = 0;
		virtual auto ResizeViewport(int width, int height) -> void = 0;
		virtual auto SetBackgroundColor(const Color& color) -> void = 0;
		virtual auto SetCamera(ICameraPtr spCamera) -> void = 0;
		virtual auto SetPolygonMode(PolygonMode mode) -> void = 0;
	};

	using IEnginePtr = std::shared_ptr<IEngine>;

	GRAPHICSENGINE_API auto CreateEngine() -> IEnginePtr;

}

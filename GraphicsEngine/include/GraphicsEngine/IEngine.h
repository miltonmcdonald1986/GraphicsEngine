#pragma once

#include <filesystem>
#include <optional>

#include "IAttribute.h"
#include "ICamera.h"
#include "IEntity.h"
#include "ILog.h"
#include "ShaderManager.h"
#include "Types.h"

/// @brief The GraphicsEngine namespace contains all the classes and functions for the graphics engine.
namespace GraphicsEngine
{

	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual auto CreateNewEntity(const IAttributes& attributes, const std::vector<unsigned int>& indices = {}) -> IEntityPtr = 0;
		virtual auto CreateNewTextureFromFile(std::string_view textureName, const std::filesystem::path& path) -> ITexturePtr = 0;
		virtual auto GetBackgroundColor() const -> Color = 0;
		virtual auto GetCamera() const -> ICameraPtr = 0;
		virtual auto GetLog() const -> ILogPtr = 0;
		virtual auto GetShaderManager() -> ShaderManager* = 0;
		virtual auto GetPolygonMode() const -> PolygonMode = 0;
		virtual auto Render() -> void = 0;
		virtual auto ResizeViewport(int width, int height) -> void = 0;
		virtual auto SetBackgroundColor(const Color& color) -> void = 0;
		virtual auto SetCamera(ICameraPtr spCamera) -> void = 0;
		virtual auto SetPolygonMode(PolygonMode mode) -> void = 0;
	};

	GRAPHICSENGINE_API auto CreateEngine() -> IEnginePtr;

}

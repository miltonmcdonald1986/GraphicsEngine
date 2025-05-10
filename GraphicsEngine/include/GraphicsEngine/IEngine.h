#pragma once

#include <filesystem>
#include <optional>

#include "EntityManager.h"
#include "ICamera.h"
#include "ILog.h"
#include "ShaderManager.h"
#include "Types.h"

namespace GraphicsEngine
{

	class IEngine
	{
	public:
		virtual ~IEngine() = default;

		virtual auto CreateNewTextureFromFile(std::string_view textureName, const std::filesystem::path& path) -> ITexturePtr = 0;
		virtual auto GetBackgroundColor() const ->Types::Color = 0;
		virtual auto GetCamera() const -> ICameraPtr = 0;
		virtual auto GetEntityManager() -> EntityManager* = 0;
		virtual auto GetLog() const -> ILogPtr = 0;

		/// @brief Retrieves the shader manager associated with the engine.
		/// @return A pointer to the ShaderManager instance.
		/// @note The ShaderManager is responsible for managing and compiling shaders used in the graphics engine.
		virtual auto GetShaderManager() -> ShaderManager* = 0;

		virtual auto GetPolygonMode() const ->Types::PolygonMode = 0;
		virtual auto Render() -> void = 0;
		virtual auto ResizeViewport(int width, int height) -> void = 0;
		virtual auto SetBackgroundColor(const Types::Color& color) -> void = 0;
		virtual auto SetCamera(ICameraPtr spCamera) -> void = 0;
		virtual auto SetPolygonMode(Types::PolygonMode mode) -> void = 0;
	};

	using IEnginePtr = std::shared_ptr<IEngine>;
	GRAPHICSENGINE_API auto CreateEngine() -> IEnginePtr;

}

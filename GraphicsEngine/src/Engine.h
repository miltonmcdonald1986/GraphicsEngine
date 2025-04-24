#pragma once

#include "IEngine.h"

namespace GraphicsEngine
{

	class Engine : public IEngine
	{
	public:
		Engine();
		~Engine() override;

		auto CreateNewEntity(const IAttributes& attributes, const std::vector<unsigned int>& indices) -> IEntityPtr override;
		auto CreateNewShaderFromFiles(const std::filesystem::path& vert, const std::filesystem::path& geom, const std::filesystem::path& frag) -> IShaderPtr override;
		auto CreateNewShaderFromSource(std::string_view vert, std::string_view geom, std::string_view frag) -> IShaderPtr override;
		auto CreateNewTextureFromFile(std::string_view textureName, const std::filesystem::path& path) -> ITexturePtr override;
		auto GetBackgroundColor() const -> Color override;
		auto GetCamera() const -> ICameraPtr override;
		auto GetCurrentShader() const -> IShaderPtr override;
		auto GetLog() const -> ILogPtr override;
		auto GetPolygonMode() const -> PolygonMode override;
		auto Render() const -> void override;
		auto ResizeViewport(int width, int height) -> void override;
		auto SetBackgroundColor(const Color& color) -> void override;
		auto SetCamera(ICameraPtr spCamera) -> void override;
		auto SetPolygonMode(PolygonMode polygonMode) -> void override;

	private:
		auto GetNextAvailableEntityId() const -> unsigned int;

		Color m_BackgroundColor{};
		PolygonMode m_PolygonMode = PolygonMode::Fill;
		IShaders m_Shaders;
		IEntities m_Entities;
		ITextures m_Textures;
		ILogPtr m_spLog = nullptr;
		ICameraPtr m_spCamera = nullptr;
	};

}

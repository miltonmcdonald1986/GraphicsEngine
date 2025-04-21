#pragma once

#include "IEngine.h"

#include <map>
#include <set>

#include "GraphicsEngineFwd.h"
#include "Shader.h"

namespace GraphicsEngine
{

	class Engine : public IEngine
	{
	public:
		Engine();
		~Engine() override;

		auto CreateNewEntity(const IAttributes& attributes, const std::optional<Indices>& oIndices) -> IEntityPtr override;
		auto CreateNewShaderFromFiles(const Path& vert, const Path& geom, const Path& frag) -> IShaderPtr override;
		auto CreateNewShaderFromSource(const String& vert, const String& geom, const String& frag) -> IShaderPtr override;
		auto CreateNewTextureFromFile(const String& textureName, const Path& path) -> ITexturePtr override;
		auto GetBackgroundColor() const -> Color override;
		auto GetCurrentShader() const -> IShaderPtr override;
		auto GetLog() const -> ILogPtr override;
		auto GetPolygonMode() const -> PolygonMode override;
		auto Render() const -> void override;
		auto SetBackgroundColor(const Color& color) -> void override;
		auto SetPolygonMode(PolygonMode polygonMode) -> void override;

	private:
		auto GetNextAvailableEntityId() const -> unsigned int;

		Color m_BackgroundColor{};
		PolygonMode m_PolygonMode = PolygonMode::Fill;
		IShaders m_Shaders;
		IEntities m_Entities;
		ITextures m_Textures;
		ILogPtr m_spLog = nullptr;
	};

}

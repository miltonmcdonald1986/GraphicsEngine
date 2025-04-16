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
		~Engine() override = default;

		auto CreateNewEntity(const IAttributes& attributes, const std::optional<Indices>& oIndices) -> IEntityPtr override;
		auto CreateNewShaderFromFiles(const Path& vert, const Path& geom, const Path& frag) -> IShaderPtr override;
		auto CreateNewShaderFromSource(const std::string& vert, const std::string& geom, const std::string& frag) -> IShaderPtr override;
		auto GetBackgroundColor() const -> Color override;
		auto GetCurrentShader() const -> IShaderPtr override;
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
	};

}

#pragma region Forward declarations

namespace spdlog
{

	class logger;

}

#pragma endregion

using LoggerSharedPtr = std::shared_ptr<spdlog::logger>;

//struct GEengine
//{
//public:
//
//	GEengine();
//
//	~GEengine();
//
//	auto AddEntity() -> GraphicsEngine::EntityPtr;
//	auto GenerateEntity_IndexedPoints3DBasic(unsigned long long numVertexBytes, float* vertices, unsigned long long numIndexBytes, unsigned int* indices) -> unsigned int;
//	auto GetCurrentShaderProgram() -> GEshader*;
//	auto GetRecentLogMessages(int* numMessages, const char*** messages) -> void;
//	auto GetShader(const std::string& name) -> GEshader*;
//	auto GetVAO(const std::string& name) -> GLuint;
//	auto Render() const -> void;
//	auto SetEntityShader(unsigned int entId, GEshader* pShader) -> void;
//
//private:
//
//	//auto InitializeShaderTriangleBasic() -> bool;
//	//auto InitializeShaderTriangleRGB() -> bool;
//	auto InitializeShaders() -> bool;
//	auto InitializeLogging() -> bool;
//	auto InitializeOpenGL() -> bool;
//	auto NextAvailableEntityId() const -> unsigned int;
//
//	std::vector<const char*> m_LogMessages;
//	std::map<std::string, GLuint> m_VAOs;
//	std::map<std::string, GEshader*> m_Shaders;
//	//LoggerSharedPtr m_spLogger = nullptr;
//	std::set<GraphicsEngine::EntityPtr> m_Entities;
//};

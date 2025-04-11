#pragma once

#include "IEngine.h"

#include <map>
#include <set>

#include "Fwd.h"
#include "Shader.h"

#pragma region Forward declarations

namespace spdlog
{

	class logger;

}

#pragma endregion

using LoggerSharedPtr = std::shared_ptr<spdlog::logger>;

struct GEengine
{
public:

	GEengine();

	~GEengine();

	auto AddEntity() -> GraphicsEngine::EntityPtr;
	auto GenerateEntity_IndexedPoints3DBasic(unsigned long long numVertexBytes, float* vertices, unsigned long long numIndexBytes, unsigned int* indices) -> unsigned int;
	auto GetCurrentShaderProgram() -> GEshader*;
	auto GetRecentLogMessages(int* numMessages, const char*** messages) -> void;
	auto GetShader(const std::string& name) -> GEshader*;
	auto GetVAO(const std::string& name) -> GLuint;
	auto Render() const -> void;

private:

	auto InitializeShaderTriangleBasic() -> bool;
	auto InitializeShaderTriangleRGB() -> bool;
	auto InitializeShaders() -> bool;
	auto InitializeLogging() -> bool;
	auto InitializeOpenGL() -> bool;
	auto NextAvailableEntityId() const -> unsigned int;

	std::vector<const char*> m_LogMessages;
	std::map<std::string, GLuint> m_VAOs;
	std::map<std::string, GEshader*> m_Shaders;
	//LoggerSharedPtr m_spLogger = nullptr;
	std::set<GraphicsEngine::EntityPtr> m_Entities;
};

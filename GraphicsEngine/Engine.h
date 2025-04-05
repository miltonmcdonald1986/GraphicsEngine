#pragma once

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/EntityType.h"

#include <set>

#pragma region Forward declarations

namespace GraphicsEngine
{

	struct Entity;

}

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

	auto GenerateEntity_IndexedPoints3DBasic(unsigned long long numVertexBytes, float* vertices, unsigned long long numIndexBytes, unsigned int* indices) -> unsigned int;
	auto GenerateEntity_Triangle3DBasic() -> unsigned int;
	auto GenerateEntity_Triangle3DRGB() -> unsigned int;
	auto Render() const -> void;

private:

	auto InitializeVAOs() -> bool;
	auto InitializeShaders() -> bool;
	auto InitializeLogging() -> bool;
	auto InitializeOpenGL() -> bool;
	auto NextAvailableEntityId() const -> unsigned int;

	std::map<std::string, GLuint> m_VAOs;
	std::map<std::string, GLuint> m_Shaders;
	LoggerSharedPtr m_spLogger = nullptr;
	std::set<GraphicsEngine::Entity> m_Entities;
};

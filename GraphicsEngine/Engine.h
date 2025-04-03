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

struct GEengine/* : public IEngine*/
{
public:

	GEengine();

	~GEengine();

	auto GenerateEntity(GEentityType type) -> unsigned int;
	auto Render() const -> void;

	operator bool() const;

private:

	auto InitializeVAOs() -> bool;
	auto InitializeShaders() -> bool;
	auto InitializeLogging() -> bool;
	auto InitializeOpenGL() -> bool;
	auto NextAvailableEntityId() const -> unsigned int;

	bool m_Initialized = false;
	std::map<std::string, GLuint> m_VAOs;
	std::map<std::string, GLuint> m_Shaders;
	LoggerSharedPtr m_spLogger = nullptr;
	std::set<GraphicsEngine::Entity> m_Entities;
};

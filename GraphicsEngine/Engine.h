#pragma once

#include "GraphicsEngine/IEngine.h"

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

namespace GraphicsEngine
{

	class Engine : public IEngine
	{
	public:

		Engine();

		virtual ~Engine() override;

		virtual auto GenerateEntity(EntityType type) -> unsigned int override;
		virtual auto Render() const -> void override;

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
		std::set<Entity> m_Entities;
	};

}

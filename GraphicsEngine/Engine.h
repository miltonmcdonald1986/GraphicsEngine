#pragma once

#include "GraphicsEngine/IEngine.h"

#pragma region Forward declarations

namespace spdlog
{

	class logger;

}

#pragma endregion

// Aliases

using LoggerSharedPtr = std::shared_ptr<spdlog::logger>;

namespace GraphicsEngine
{

	class Engine : public IEngine
	{
	public:

		Engine();

		operator bool() const;

	private:

		auto InitializeLogging() -> bool;
		auto InitializeOpenGL() -> bool;

		bool m_Initialized = false;
		LoggerSharedPtr m_spLogger = nullptr;
	};

}

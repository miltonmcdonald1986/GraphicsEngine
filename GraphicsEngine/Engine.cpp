#include "pch.h"
#include "Engine.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/ringbuffer_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include "glad/glad.h"

namespace GraphicsEngine
{

	Engine::Engine()
	{
		m_Initialized = false;

		if (!InitializeLogging())
			return;

		if (!InitializeOpenGL())
			return;
		
		gladLoadGL();

		m_Initialized = true;
	}

	Engine::operator bool() const
	{
		return m_Initialized;
	}

	auto Engine::InitializeLogging() -> bool
	{
		std::vector<spdlog::sink_ptr> sinks;

		// A rotating file sink provides logging that can be viewed in a text editor after the engine shuts down.

		auto spRotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs\\GraphicsEngine.log", 1024 * 1024 * 5, 3);
		if (!spRotatingFileSink)
			return false;

		sinks.push_back(spRotatingFileSink);

		// A ringbuffer sink keeps 128 messages in memory to be accessed by any client of the engine during runtime.

		auto spRingbufferSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(128);
		if (!spRingbufferSink)
			return false;

		sinks.push_back(spRingbufferSink);

		// Create a logger with our sinks.

		m_spLogger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
		if (!m_spLogger)
			return false;

		m_spLogger->set_level(spdlog::level::debug);
		spdlog::register_logger(m_spLogger);

		return true;
	}

	auto Engine::InitializeOpenGL() -> bool
	{
		return (gladLoadGL() != 0);
	}

	auto CreateEngine() -> IEngineSharedPtr
	{
		Engine engine;
		if (!engine)
			return nullptr;
		else
			return IEngineSharedPtr(new Engine(engine));
	}

}

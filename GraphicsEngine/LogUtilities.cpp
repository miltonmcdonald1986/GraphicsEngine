#include "pch.h"
#include "GraphicsEngine/LogUtilities.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/ringbuffer_sink.h"

namespace GraphicsEngine::Log::Utilities
{
	
	auto SetMaxNumItems(size_t maxNumItems) -> bool
	{
		auto logger = spdlog::get("Engine");
		if (!logger)
			return false;

		bool foundSink = false;
		auto sinks = logger->sinks();
		for (auto sink : sinks)
		{
			if (auto spSink = std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink))
			{
				foundSink = true;
				spSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(maxNumItems);
			}
		}
		
		return foundSink;
	}

	auto GetLevel() -> std::optional<LogLevel>
	{
		auto logger = spdlog::get("Engine");
		if (!logger)
			return std::nullopt;

		auto level = logger->level();
		switch (level)
		{
		case spdlog::level::trace:
			return LogLevel::Trace;
		case spdlog::level::debug:
			return LogLevel::Debug;
		case spdlog::level::info:
			return LogLevel::Info;
		case spdlog::level::warn:
			return LogLevel::Warn;
		case spdlog::level::err:
			return LogLevel::Error;
		case spdlog::level::critical:
			return LogLevel::Critical;
		case spdlog::level::off:
			return LogLevel::Off;
		default:
			return std::nullopt;
		}
	}

	auto GetRecentLogMessages() -> std::vector<std::string>
	{
		auto sinks = spdlog::get("Engine")->sinks();
		for (auto sink : sinks)
		{
			if (auto spRingbuffer = std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink))
				return spRingbuffer->last_formatted();
		}

		return {};
	}

	auto SetLevel(LogLevel level) -> bool
	{
		auto logger = spdlog::get("Engine");
		if (!logger)
			return false;

		switch (level)
		{
		case GraphicsEngine::Log::Utilities::LogLevel::Trace:
			logger->set_level(spdlog::level::trace);
			break;
		case GraphicsEngine::Log::Utilities::LogLevel::Debug:
			logger->set_level(spdlog::level::debug);
			break;
		case GraphicsEngine::Log::Utilities::LogLevel::Info:
			logger->set_level(spdlog::level::info);
			break;
		case GraphicsEngine::Log::Utilities::LogLevel::Warn:
			logger->set_level(spdlog::level::warn);
			break;
		case GraphicsEngine::Log::Utilities::LogLevel::Error:
			logger->set_level(spdlog::level::err);
			break;
		case GraphicsEngine::Log::Utilities::LogLevel::Critical:
			logger->set_level(spdlog::level::critical);
			break;
		case GraphicsEngine::Log::Utilities::LogLevel::Off:
			logger->set_level(spdlog::level::off);
			break;
		default:
			return false;
		}

		return true;
	}

}

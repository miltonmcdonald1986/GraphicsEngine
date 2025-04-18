#include "pch.h"
#include "Log.h"

#include <queue>

#include "Debug.h"

namespace Helpers
{

	auto CreateLog(loggerPtr spLogger) -> GraphicsEngine::LogPtr
	{
		return std::make_shared<GraphicsEngine::Log>(spLogger);
	}

}

namespace GraphicsEngine
{

	auto GetLog() -> LogPtr
	{
		return Helpers::CreateLog(spdlog::get("Engine"));
	}

	auto CreateLog() -> LogPtr
	{
		return std::make_shared<Log>();
	}

Log::Log()
{
	if (spdlog::get("Engine"))
		spdlog::drop("Engine");

	std::vector<spdlog::sink_ptr> sinks;

	// A rotating file sink provides logging that can be viewed in a text editor after the engine shuts down.

	m_spRotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs\\GraphicsEngine.log", 1024 * 1024 * 5, 3);
	if (m_spRotatingFileSink)
		sinks.push_back(m_spRotatingFileSink);

	m_spQueueSink = std::make_shared<queue_sink>(m_QueueSize);
	if (m_spQueueSink)
		sinks.push_back(m_spQueueSink);

	// Create a logger with our sinks.

	m_spLogger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));
	if (!m_spLogger)
		return;

	spdlog::flush_every(std::chrono::seconds(3));
	spdlog::register_logger(m_spLogger);
	m_spLogger->set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%l] %v");

#ifdef _DEBUG
	m_spLogger->set_level(spdlog::level::debug);
#else
	m_spLogger->set_level(spdlog::level::info);
#endif

	return;
}

Log::Log(loggerPtr spLogger)
	: m_spLogger(spLogger)
{
}

auto Log::ClearMessages() -> void
{
	m_spQueueSink->clear();
}

auto Log::GetLatestMessages() const -> Strings
{
	return m_spQueueSink->get_messages();
}

auto Log::GetLevel() const -> LogLevel
{
	switch (m_spLogger->level())
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
		BREAKPOINT;
		return LogLevel::Off;
	}
}

auto Log::Trace(const String& message, const std::source_location& loc) -> void
{
	LogMessage(GraphicsEngine::LogLevel::Trace, loc, message);
}

auto Log::Debug(const String& message, const std::source_location& loc) -> void
{
	LogMessage(GraphicsEngine::LogLevel::Debug, loc, message);
}

auto Log::Info(const String& message, const std::source_location& loc) -> void
{
	LogMessage(GraphicsEngine::LogLevel::Info, loc, message);
}

auto Log::Warn(const String& message, const std::source_location& loc) -> void
{
	LogMessage(GraphicsEngine::LogLevel::Warn, loc, message);
}

auto Log::Error(const String& message, const std::source_location& loc) -> void
{
	LogMessage(GraphicsEngine::LogLevel::Error, loc, message);
}

auto Log::Critical(const String& message, const std::source_location& loc) -> void
{
	LogMessage(GraphicsEngine::LogLevel::Critical, loc, message);
}

auto Log::LogMessage(LogLevel level, const std::source_location& loc, const String& message) const -> void
{
	auto file = loc.file_name();
	auto func = loc.function_name();
	auto line = loc.line();
	switch (level)
	{
	case GraphicsEngine::LogLevel::Trace:
		m_spLogger->trace(std::format("{}\t{}\t{}\t{}", file, func, line, message));
		break;
	case GraphicsEngine::LogLevel::Debug:
		m_spLogger->debug(std::format("{}\t{}\t{}\t{}", file, func, line, message));
		break;
	case GraphicsEngine::LogLevel::Info:
		m_spLogger->info(std::format("{}\t{}\t{}\t{}", file, func, line, message));
		break;
	case GraphicsEngine::LogLevel::Warn:
		m_spLogger->warn(std::format("{}\t{}\t{}\t{}", file, func, line, message));
		break;
	case GraphicsEngine::LogLevel::Error:
		m_spLogger->error(std::format("{}\t{}\t{}\t{}", file, func, line, message));
		break;
	case GraphicsEngine::LogLevel::Critical:
		m_spLogger->critical(std::format("{}\t{}\t{}\t{}", file, func, line, message));
		break;
	default:
		break;
	}
}

auto Log::SetLevel(LogLevel level) -> void
{
	switch (level)
	{
	case GraphicsEngine::LogLevel::Trace:
		m_spLogger->set_level(spdlog::level::trace);
		break;
	case GraphicsEngine::LogLevel::Debug:
		m_spLogger->set_level(spdlog::level::debug);
		break;
	case GraphicsEngine::LogLevel::Info:
		m_spLogger->set_level(spdlog::level::info);
		break;
	case GraphicsEngine::LogLevel::Warn:
		m_spLogger->set_level(spdlog::level::warn);
		break;
	case GraphicsEngine::LogLevel::Error:
		m_spLogger->set_level(spdlog::level::err);
		break;
	case GraphicsEngine::LogLevel::Critical:
		m_spLogger->set_level(spdlog::level::critical);
		break;
	case GraphicsEngine::LogLevel::Off:
		m_spLogger->set_level(spdlog::level::off);
		break;
	default:
		BREAKPOINT;
		break;
	}
}

}

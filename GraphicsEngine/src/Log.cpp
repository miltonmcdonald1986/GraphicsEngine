#include "pch.h"
#include "Log.h"

#include <queue>

#include "Debug.h"

namespace GraphicsEngine
{

	auto GetLog() -> LogPtr
	{
		return CreateLog(spdlog::get("Engine"));
	}

	auto CreateLog() -> LogPtr
	{
		return std::make_shared<Log>();
	}

	auto CreateLog(loggerPtr spLogger) -> LogPtr
	{
		return std::make_shared<Log>(spLogger);
	}
	
	//GRAPHICSENGINE_API auto LogMessage(LogLevel level, const char* file, const char* func, int line, const char* message) -> void
	//{
	//	auto logger = spdlog::get("Engine");

	//	switch (level)
	//	{
	//	case GraphicsEngine::Log::LogLevel::Trace:
	//		logger->trace(std::format("{}\t{}\t{}\t{}", file, func, line, message));
	//		break;
	//	case GraphicsEngine::Log::LogLevel::Debug:
	//		logger->debug(std::format("{}\t{}\t{}\t{}", file, func, line, message));
	//		break;
	//	case GraphicsEngine::Log::LogLevel::Info:
	//		logger->info(std::format("{}\t{}\t{}\t{}", file, func, line, message));
	//		break;
	//	case GraphicsEngine::Log::LogLevel::Warn:
	//		logger->warn(std::format("{}\t{}\t{}\t{}", file, func, line, message));
	//		break;
	//	case GraphicsEngine::Log::LogLevel::Error:
	//		logger->error(std::format("{}\t{}\t{}\t{}", file, func, line, message));
	//		break;
	//	case GraphicsEngine::Log::LogLevel::Critical:
	//		logger->critical(std::format("{}\t{}\t{}\t{}", file, func, line, message));
	//		break;
	//	}
	//}

	//auto SetMaxNumItems(size_t maxNumItems) -> bool
	//{
	//	auto logger = spdlog::get("Engine");
	//	if (!logger)
	//		return false;

	//	bool foundSink = false;
	//	auto sinks = logger->sinks();
	//	for (auto sink : sinks)
	//	{
	//		if (auto spSink = std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink))
	//		{
	//			foundSink = true;
	//			spSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(maxNumItems);
	//		}
	//	}
	//	
	//	return foundSink;
	//}

	//auto GetLevel() -> std::optional<LogLevel>
	//{
	//	auto logger = spdlog::get("Engine");
	//	if (!logger)
	//		return std::nullopt;

	//	auto level = logger->level();
	//	switch (level)
	//	{
	//	case spdlog::level::trace:
	//		return LogLevel::Trace;
	//	case spdlog::level::debug:
	//		return LogLevel::Debug;
	//	case spdlog::level::info:
	//		return LogLevel::Info;
	//	case spdlog::level::warn:
	//		return LogLevel::Warn;
	//	case spdlog::level::err:
	//		return LogLevel::Error;
	//	case spdlog::level::critical:
	//		return LogLevel::Critical;
	//	case spdlog::level::off:
	//		return LogLevel::Off;
	//	default:
	//		return std::nullopt;
	//	}
	//}

	//auto GetRecentLogMessages() -> std::vector<std::string>
	//{
	//	auto sinks = spdlog::get("Engine")->sinks();
	//	for (auto sink : sinks)
	//	{
	//		if (auto spRingbuffer = std::dynamic_pointer_cast<spdlog::sinks::ringbuffer_sink_mt>(sink))
	//			return spRingbuffer->last_formatted();
	//	}

	//	return {};
	//}

	//auto SetLevel(LogLevel level) -> bool
	//{
	//	auto logger = spdlog::get("Engine");
	//	if (!logger)
	//		return false;

	//	switch (level)
	//	{
	//	case LogLevel::Trace:
	//		logger->set_level(spdlog::level::trace);
	//		break;
	//	case LogLevel::Debug:
	//		logger->set_level(spdlog::level::debug);
	//		break;
	//	case LogLevel::Info:
	//		logger->set_level(spdlog::level::info);
	//		break;
	//	case LogLevel::Warn:
	//		logger->set_level(spdlog::level::warn);
	//		break;
	//	case LogLevel::Error:
	//		logger->set_level(spdlog::level::err);
	//		break;
	//	case LogLevel::Critical:
	//		logger->set_level(spdlog::level::critical);
	//		break;
	//	case LogLevel::Off:
	//		logger->set_level(spdlog::level::off);
	//		break;
	//	default:
	//		return false;
	//	}

	//	return true;
	//}

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

Log::~Log()
{
}

auto Log::ClearMessages() -> void
{
	m_spQueueSink->clear();
}

auto Log::GetLatestMessages() const -> Strings
{
	Strings messages = m_spQueueSink->get_messages();
	std::erase_if(messages, [](const String& str) { return str.empty() || str == "\n" || str == "\r\n"; });
	return messages;
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

auto Log::LogMessage(LogLevel level, const String& file, const String& func, int line, const String& message) -> void
{
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

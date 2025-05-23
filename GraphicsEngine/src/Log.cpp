#include "Log.h"

#include "Debug.h"

namespace graphics_engine
{

namespace
{

auto CreateLog(std::shared_ptr<spdlog::logger> spLogger) -> ILogPtr
{
	return std::make_shared<Log>(spLogger);
}

}

	auto GetLog() -> ILogPtr
	{
		return CreateLog(spdlog::get("Engine"));
	}

	auto CreateLog() -> ILogPtr
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
	sinks.push_back(m_spRotatingFileSink);

	m_spQueueSink = std::make_shared<queue_sink>(m_QueueSize);
	sinks.push_back(m_spQueueSink);

	m_spLogger = std::make_shared<spdlog::logger>("Engine", std::begin(sinks), std::end(sinks));

	spdlog::flush_every(std::chrono::seconds(3));
	spdlog::register_logger(m_spLogger);
	m_spLogger->set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%l] %v");

#ifndef NDEBUG
	m_spLogger->set_level(spdlog::level::debug);
#else
	m_spLogger->set_level(spdlog::level::info);
#endif

	return;
}

Log::Log(std::shared_ptr<spdlog::logger> spLogger)
	: m_spLogger(std::move(spLogger))
{
}

auto Log::ClearMessages() -> void
{
	m_spQueueSink->clear();
}

auto Log::GetLatestMessages() const -> std::vector<std::string>
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

auto Log::Trace(std::string_view message, const std::source_location& loc) const -> void
{
	LogMessage(LogLevel::Trace, loc, message);
}

auto Log::Debug(std::string_view message, const std::source_location& loc) const -> void
{
	LogMessage(LogLevel::Debug, loc, message);
}

auto Log::Info(std::string_view message, const std::source_location& loc) const -> void
{
	LogMessage(LogLevel::Info, loc, message);
}

auto Log::Warn(std::string_view message, const std::source_location& loc) const -> void
{
	LogMessage(LogLevel::Warn, loc, message);
}

auto Log::Error(std::string_view message, const std::source_location& loc) const -> void
{
	LogMessage(LogLevel::Error, loc, message);
}

auto Log::Critical(std::string_view message, const std::source_location& loc) const -> void
{
	LogMessage(LogLevel::Critical, loc, message);
}

auto Log::LogMessage(LogLevel level, const std::source_location& loc, std::string_view message) const -> void
{
	std::stringstream loggerOutputStream;
	loggerOutputStream << "\nFile: " << loc.file_name() << '\n';
	loggerOutputStream << "Function: " << loc.function_name() << '\n';
	loggerOutputStream << "Line: " << loc.line() << '\n';
	loggerOutputStream << "Column: " << loc.column() << '\n';
	loggerOutputStream << message;
	std::string output = loggerOutputStream.str();
	switch (level)
	{
	case LogLevel::Trace:
		m_spLogger->trace(output);
		break;
	case LogLevel::Debug:
		m_spLogger->debug(output);
		break;
	case LogLevel::Info:
		m_spLogger->info(output);
		break;
	case LogLevel::Warn:
		m_spLogger->warn(output);
		break;
	case LogLevel::Error:
		m_spLogger->error(output);
		break;
	case LogLevel::Critical:
		m_spLogger->critical(output);
		break;
	default:
		break;
	}
}

auto Log::SetLevel(LogLevel level) -> void
{
	switch (level)
	{
	case LogLevel::Trace:
		m_spLogger->set_level(spdlog::level::trace);
		break;
	case LogLevel::Debug:
		m_spLogger->set_level(spdlog::level::debug);
		break;
	case LogLevel::Info:
		m_spLogger->set_level(spdlog::level::info);
		break;
	case LogLevel::Warn:
		m_spLogger->set_level(spdlog::level::warn);
		break;
	case LogLevel::Error:
		m_spLogger->set_level(spdlog::level::err);
		break;
	case LogLevel::Critical:
		m_spLogger->set_level(spdlog::level::critical);
		break;
	case LogLevel::Off:
		m_spLogger->set_level(spdlog::level::off);
		break;
	default:
		BREAKPOINT;
		break;
	}
}

}

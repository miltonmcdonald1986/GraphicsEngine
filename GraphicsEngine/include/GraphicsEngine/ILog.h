#pragma once

#include <source_location>

namespace GraphicsEngine
{

	enum class LogLevel
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Critical,
		Off
	};

	class ILog
	{
	public:
		virtual ~ILog() = default;

		virtual auto ClearMessages() -> void = 0;
		virtual auto GetLatestMessages() const -> std::vector<std::string_view> = 0;
		virtual auto GetLevel() const -> LogLevel = 0;
		virtual auto SetLevel(LogLevel level) -> void = 0;

		// Write warnings.
		virtual auto Trace(std::string_view message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Debug(std::string_view message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Info(std::string_view message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Warn(std::string_view message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Error(std::string_view message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Critical(std::string_view message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
	};

	using ILogPtr = std::shared_ptr<ILog>;

}

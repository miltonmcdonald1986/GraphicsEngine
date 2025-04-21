#pragma once

#include "GraphicsEngine/GraphicsEngineFwd.h"
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
		virtual auto GetLatestMessages() const -> Strings = 0;
		virtual auto GetLevel() const -> LogLevel = 0;
		virtual auto SetLevel(LogLevel level) -> void = 0;

		// Write warnings.
		virtual auto Trace(const String& message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Debug(const String& message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Info(const String& message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Warn(const String& message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Error(const String& message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
		virtual auto Critical(const String& message, const std::source_location& loc = std::source_location::current()) const -> void = 0;
	};

}

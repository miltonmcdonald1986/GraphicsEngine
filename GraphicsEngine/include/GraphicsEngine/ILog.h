#pragma once

#include "GraphicsEngine/GraphicsEngineFwd.h"

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
	};

}

#pragma once

#include <optional>
#include <string>
#include <vector>

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::Log::Utilities
{

	enum class LogLevel : int
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Critical,
		Off
	};

	/// <summary>
	/// The engine log contains a ringbuffer sink that contains
	/// up to a specified number of messages in memory. We can
	/// change the max number of items with this function.
	/// </summary>
	/// <param name="maxNumItems"> The max number of items in the sink. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto SetMaxNumItems(size_t maxNumItems) -> bool;

	/// <summary>
	/// Gets the log level.
	/// </summary>
	/// <returns> the log level if it succeeded; nullopt otherwise. </returns>
	GRAPHICSENGINE_API auto GetLevel() -> std::optional<LogLevel>;

	/// <summary>
	/// Gets all the messages from the ringbuffer sink.
	/// </summary>
	/// <returns> The messages. </returns>
	GRAPHICSENGINE_API auto GetRecentLogMessages() -> std::vector<std::string>;

	/// <summary>
	/// Sets the log level.
	/// </summary>
	/// <param name="level"> The desired log level. </param>
	/// <returns> true if it succeeded; false otherwise. </returns>
	GRAPHICSENGINE_API auto SetLevel(LogLevel level) -> bool;

}

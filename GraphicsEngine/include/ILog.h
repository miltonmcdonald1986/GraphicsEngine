#pragma once

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

//#include <optional>
//#include <string>
//#include <vector>
//
//#include "GraphicsEngineImpExp.h"
//
//namespace GraphicsEngine::Log
//{
//
//	enum class LogLevel : int
//	{
//		Trace,
//		Debug,
//		Info,
//		Warn,
//		Error,
//		Critical,
//		Off
//	};
//
//	GRAPHICSENGINE_API auto LogMessage(LogLevel level, const char* file, const char* func, int line, const char* message) -> void;
//
//	/// <summary>
//	/// The engine log contains a ringbuffer sink that contains
//	/// up to a specified number of messages in memory. We can
//	/// change the max number of items with this function.
//	/// </summary>
//	/// <param name="maxNumItems"> The max number of items in the sink. </param>
//	/// <returns> true if it succeeded; false otherwise. </returns>
//	GRAPHICSENGINE_API auto SetMaxNumItems(size_t maxNumItems) -> bool;
//
//	/// <summary>
//	/// Gets the log level.
//	/// </summary>
//	/// <returns> the log level if it succeeded; nullopt otherwise. </returns>
//	GRAPHICSENGINE_API auto GetLevel() -> std::optional<LogLevel>;
//
//	/// <summary>
//	/// Gets all the messages from the ringbuffer sink.
//	/// </summary>
//	/// <returns> The messages. </returns>
//	GRAPHICSENGINE_API auto GetRecentLogMessages() -> std::vector<std::string>;
//
//	/// <summary>
//	/// Sets the log level.
//	/// </summary>
//	/// <param name="level"> The desired log level. </param>
//	/// <returns> true if it succeeded; false otherwise. </returns>
//	GRAPHICSENGINE_API auto SetLevel(LogLevel level) -> bool;
//
//}
//
//#define LOG_ERROR(msg)	GraphicsEngine::Log::LogMessage(GraphicsEngine::Log::LogLevel::Error,	__FILE__, __func__, __LINE__, msg)
//#define LOG_WARNING(msg)	GraphicsEngine::Log::LogMessage(GraphicsEngine::Log::LogLevel::Warning,	__FILE__, __func__, __LINE__, msg)

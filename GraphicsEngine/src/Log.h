#pragma once

#include <queue>
#include <source_location>

#include "GraphicsEngineFwd.h"
#include "ILog.h"
#include "Fwd.h"

namespace GraphicsEngine
{

	class queue_sink : public spdlog::sinks::base_sink<std::mutex> {
	private:
		int m_MaxNumMessages = 0;
		std::queue<std::string> messages_;

	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override {
			// Format the log message
			spdlog::memory_buf_t formatted;
			formatter_->format(msg, formatted);

			// Add the formatted message to the vector
			messages_.push(fmt::to_string(formatted));
			if (messages_.size() > m_MaxNumMessages)
				messages_.pop();
		}

		void flush_() override {
			// No-op for this custom sink
		}

	public:

		queue_sink(int maxNumMessages)
			: spdlog::sinks::base_sink<std::mutex>(),
			  m_MaxNumMessages(maxNumMessages)
		{
		}

		void clear()
		{
			while (!messages_.empty()) {
				messages_.pop();
			}
		}

		Strings get_messages() const {
			Strings output;
			std::queue<std::string> q_copy = messages_;
			while (!q_copy.empty())
			{
				output.push_back(q_copy.front());
				q_copy.pop();
			}
			return output;
		}
	};

	class Log : public ILog
	{
	public:
		Log();
		Log(loggerPtr spLogger);
		~Log() override;
		
		auto ClearMessages() -> void override;
		auto GetLatestMessages() const->Strings override;
		auto GetLevel() const->LogLevel override;
		auto Trace(const String& message, const std::source_location& loc = std::source_location::current()) -> void;
		auto Debug(const String& message, const std::source_location& loc = std::source_location::current()) -> void;
		auto Info(const String& message, const std::source_location& loc = std::source_location::current()) -> void;
		auto Warn(const String& message, const std::source_location& loc = std::source_location::current()) -> void;
		auto Error(const String& message, const std::source_location& loc = std::source_location::current()) -> void;
		auto Critical(const String& message, const std::source_location& loc = std::source_location::current()) -> void;
		auto SetLevel(LogLevel level) -> void override;

	private:
		auto LogMessage(LogLevel level, const std::source_location& loc, const String& message) -> void;

		loggerPtr m_spLogger = nullptr;
		std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_spRotatingFileSink = nullptr;
		std::shared_ptr<queue_sink> m_spQueueSink = nullptr;
		static const int m_QueueSize = 128;
	};

	auto GetLog() -> LogPtr;

	auto CreateLog() -> LogPtr;
	auto CreateLog(loggerPtr spLogger) -> LogPtr;

}

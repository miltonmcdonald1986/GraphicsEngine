#pragma once

#include <queue>

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
		auto LogMessage(LogLevel level, const String& file, const String& func, int line, const String& message) -> void;
		auto SetLevel(LogLevel level) -> void override;

	private:
		loggerPtr m_spLogger = nullptr;
		std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_spRotatingFileSink = nullptr;
		std::shared_ptr<queue_sink> m_spQueueSink = nullptr;
		static const int m_QueueSize = 128;
	};

	auto GetLog() -> LogPtr;

	auto CreateLog() -> LogPtr;
	auto CreateLog(loggerPtr spLogger) -> LogPtr;

}

#define LOG_TRACE(msg)		GraphicsEngine::GetLog()->LogMessage(GraphicsEngine::LogLevel::Trace,		std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, msg)
#define LOG_DEBUG(msg)		GraphicsEngine::GetLog()->LogMessage(GraphicsEngine::LogLevel::Debug,		std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, msg)
#define LOG_INFO(msg)		GraphicsEngine::GetLog()->LogMessage(GraphicsEngine::LogLevel::Info,		std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, msg)
#define LOG_WARN(msg)		GraphicsEngine::GetLog()->LogMessage(GraphicsEngine::LogLevel::Warn,		std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, msg)
#define LOG_ERROR(msg)		GraphicsEngine::GetLog()->LogMessage(GraphicsEngine::LogLevel::Error,		std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, msg)
#define LOG_CRITICAL(msg)	GraphicsEngine::GetLog()->LogMessage(GraphicsEngine::LogLevel::Critical,	std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, msg)

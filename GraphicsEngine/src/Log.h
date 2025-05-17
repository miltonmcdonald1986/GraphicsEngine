#pragma once

#include <queue>

#include "ILog.h"

#include "spdlog/sinks/base_sink.h"

namespace spdlog
{
	class logger; 

	namespace sinks
	{
		template <typename Mutex> class rotating_file_sink;
		using rotating_file_sink_mt = rotating_file_sink<std::mutex>;
	}
}

namespace graphics_engine
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
			if (static_cast<int>(messages_.size()) > m_MaxNumMessages)
				messages_.pop();
		}

		void flush_() override {
			// No-op for this custom sink
		}

	public:

		explicit queue_sink(int maxNumMessages)
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

		std::vector<std::string> get_messages() const 
		{
			std::vector<std::string> output;
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
		explicit Log(std::shared_ptr<spdlog::logger> spLogger);
		~Log() override = default;
		
		auto ClearMessages() -> void override;
		auto GetLatestMessages() const -> std::vector<std::string> override;
		auto GetLevel() const->LogLevel override;
		auto Trace(std::string_view message, const std::source_location& loc) const -> void override;
		auto Debug(std::string_view message, const std::source_location& loc) const -> void override;
		auto Info(std::string_view message, const std::source_location& loc) const -> void override;
		auto Warn(std::string_view message, const std::source_location& loc) const -> void override;
		auto Error(std::string_view message, const std::source_location& loc) const -> void override;
		auto Critical(std::string_view message, const std::source_location& loc) const -> void override;
		auto SetLevel(LogLevel level) -> void override;

	private:
		auto LogMessage(LogLevel level, const std::source_location& loc, std::string_view message) const -> void;

		std::shared_ptr<spdlog::logger> m_spLogger = nullptr;
		std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_spRotatingFileSink = nullptr;
		std::shared_ptr<queue_sink> m_spQueueSink = nullptr;
		static constexpr int m_QueueSize = 128;
	};

	auto GetLog() -> ILogPtr;
	auto CreateLog() -> ILogPtr;

}

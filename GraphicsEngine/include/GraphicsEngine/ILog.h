#pragma once

#include <source_location>

namespace graphics_engine {

enum class LogLevel : std::uint8_t {
  Trace,
  Debug,
  Info,
  Warn,
  Error,
  Critical,
  Off
};

class ILog {
 public:
  ILog(const ILog&) = delete;
  ILog& operator=(const ILog&) = delete;
  ILog(ILog&&) = delete;
  ILog& operator=(ILog&&) = delete;

  virtual auto ClearMessages() -> void = 0;
  [[nodiscard]] virtual auto GetLatestMessages() const
      -> std::vector<std::string> = 0;
  [[nodiscard]] virtual auto GetLevel() const -> LogLevel = 0;
  virtual auto SetLevel(LogLevel level) -> void = 0;

  // Write warnings.
  virtual auto Trace(std::string_view message,
                     const std::source_location& loc =
                         std::source_location::current()) const -> void = 0;
  virtual auto Debug(std::string_view message,
                     const std::source_location& loc =
                         std::source_location::current()) const -> void = 0;
  virtual auto Info(std::string_view message,
                    const std::source_location& loc =
                        std::source_location::current()) const -> void = 0;
  virtual auto Warn(std::string_view message,
                    const std::source_location& loc =
                        std::source_location::current()) const -> void = 0;
  virtual auto Error(std::string_view message,
                     const std::source_location& loc =
                         std::source_location::current()) const -> void = 0;
  virtual auto Critical(std::string_view message,
                        const std::source_location& loc =
                            std::source_location::current()) const -> void = 0;

 protected:
  ILog() = default;
  // NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
  virtual ~ILog() = default;
};

using ILogPtr = std::shared_ptr<ILog>;

}  // namespace graphics_engine

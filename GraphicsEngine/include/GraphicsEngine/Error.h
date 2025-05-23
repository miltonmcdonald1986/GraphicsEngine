#pragma once

#include "Types.h"

namespace graphics_engine {

enum class ErrorCode : std::uint8_t {
  kAngleSumExceeded,
  kInvalidAngle,
  kInvalidInput,
  kInvalidSideLength,
  kInvalidTriangle
};

class Error {
 public:
  Error(ErrorCode code, std::string msg) : code_(code), msg_(std::move(msg)) {}

  [[nodiscard]] auto GetCode() const -> ErrorCode { return code_; };
  [[nodiscard]] auto GetMsg() const -> Types::String { return msg_; };

 private:
  ErrorCode code_;
  std::string msg_;
};

}  // namespace graphics_engine

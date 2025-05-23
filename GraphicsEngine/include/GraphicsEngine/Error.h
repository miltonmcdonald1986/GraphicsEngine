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
  Error(ErrorCode code, const std::string& msg) : code_(code), msg_(msg) {}

  ErrorCode GetCode() const { return code_; };
  Types::String GetMsg() const { return msg_; };

 private:
  ErrorCode code_;
  std::string msg_;
};

}  // namespace graphics_engine

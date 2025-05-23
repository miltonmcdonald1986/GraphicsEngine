#pragma once

#include "Types.h"

namespace graphics_engine {

class Uniform {
 public:
  Uniform(Types::StringView name, int location);

  [[nodiscard]] auto GetData() const -> Types::UniformData;
  auto SetData(const Types::UniformData& data) -> void;

  [[nodiscard]] auto GetName() const -> Types::String;
  [[nodiscard]] auto GetLocation() const -> int;

 private:
  Types::String name_{};
  int location_{};
  Types::UniformData data_{};
};

using Uniforms = std::unordered_map<Types::String, Uniform, Types::StringHash,
                                    std::equal_to<>>;

}  // namespace graphics_engine

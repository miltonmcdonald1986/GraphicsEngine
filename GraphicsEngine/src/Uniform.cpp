#include "Uniform.h"

namespace graphics_engine {

Uniform::Uniform(Types::StringView name, int location)
    : name_(std::string(name)), location_(location) {}

auto Uniform::GetData() const -> Types::UniformData { return data_; }

auto Uniform::SetData(const Types::UniformData& data) -> void { data_ = data; }

auto Uniform::GetName() const -> Types::String { return name_; }

auto Uniform::GetLocation() const -> int { return location_; }

}  // namespace graphics_engine

#pragma once

#include <memory>
#include <vector>

namespace graphics_engine {

class ITexture {
 public:
  ITexture(const ITexture&) = delete;
  auto operator=(const ITexture&) -> ITexture& = delete;
  ITexture(ITexture&&) = delete;
  auto operator=(ITexture&&) -> ITexture& = delete;

 protected:
  ITexture() = default;
  virtual ~ITexture() = default;
};

using ITexturePtr = std::shared_ptr<ITexture>;
using ITextures = std::vector<ITexturePtr>;

}  // namespace graphics_engine

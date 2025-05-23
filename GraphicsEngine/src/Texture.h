#pragma once

#include <filesystem>

#include "ITexture.h"
#include "Types.h"

namespace graphics_engine {

class Texture : public ITexture {
 public:
  Texture() = delete;
  ~Texture() override = default;
  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;
  Texture(Texture&&) = delete;
  Texture& operator=(Texture&&) = delete;

  /// @brief Create a texture
  /// @param textureName the name should be the same name as in the shader
  /// @param path the image file for this texture
  Texture(std::string_view textureName, const std::filesystem::path& path);

  [[nodiscard]] auto GetId() const -> GLuint;
  [[nodiscard]] auto GetName() const -> std::string_view;

 private:
  GLuint m_Texture = 0;
  std::string m_Name;
};

auto CreateTextureFromFile(std::string_view textureName,
                           const std::filesystem::path& path) -> ITexturePtr;

}  // namespace graphics_engine

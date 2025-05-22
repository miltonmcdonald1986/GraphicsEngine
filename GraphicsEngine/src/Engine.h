#pragma once

#include "EntityManagerImpl.h"
#include "IEngine.h"
#include "ShaderManagerImpl.h"

namespace graphics_engine {

class Engine : public IEngine {
 public:
  explicit Engine(const MaybeGLLoadProc& proc_address_func);
  ~Engine() override;

  auto CreateNewTextureFromFile(std::string_view textureName,
                                const std::filesystem::path& path)
      -> ITexturePtr override;
  auto GetBackgroundColor() const -> Types::Color override;
  auto GetCamera() const -> ICameraPtr override;
  auto GetEntityManager() -> entities::EntityManager* override;
  auto GetLog() const -> ILogPtr override;
  auto GetPolygonMode() const -> Types::PolygonMode override;
  auto GetShaderManager() -> ShaderManager* override;
  auto Render() -> void override;
  auto ResizeViewport(int width, int height) -> void override;
  auto SetBackgroundColor(const Types::Color& color) -> void override;
  auto SetCamera(ICameraPtr spCamera) -> void override;
  auto SetPolygonMode(Types::PolygonMode polygonMode) -> void override;

 private:
  Types::Color m_BackgroundColor{};
  entities::EntityManagerImplPtr m_upEntityManagerImpl = nullptr;
  Types::PolygonMode m_PolygonMode = Types::PolygonMode::Fill;
  ShaderManagerImplPtr m_upShaderManagerImpl = nullptr;
  ITextures m_Textures;
  ILogPtr m_spLog = nullptr;
  ICameraPtr m_spCamera = nullptr;
};

}  // namespace graphics_engine

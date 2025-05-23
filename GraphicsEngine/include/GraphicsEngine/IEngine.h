#pragma once

#include <filesystem>
#include <optional>

#include "EntityManager.h"
#include "ICamera.h"
#include "ILog.h"
#include "ShaderManager.h"
#include "Types.h"

namespace graphics_engine {

class IEngine {
 public:
  IEngine(const IEngine&) = delete;
  auto operator=(const IEngine&) -> IEngine& = delete;
  IEngine(IEngine&&) = delete;
  auto operator=(IEngine&&) -> IEngine& = delete;

  virtual auto CreateNewTextureFromFile(std::string_view textureName,
                                        const std::filesystem::path& path)
      -> ITexturePtr = 0;
  [[nodiscard]] virtual auto GetBackgroundColor() const -> Types::Color = 0;
  [[nodiscard]] virtual auto GetCamera() const -> ICameraPtr = 0;
  virtual auto GetEntityManager() -> entities::EntityManager* = 0;
  [[nodiscard]] virtual auto GetLog() const -> ILogPtr = 0;

  /// @brief Retrieves the shader manager associated with the engine.
  /// @return A pointer to the ShaderManager instance.
  /// @note The ShaderManager is responsible for managing and compiling shaders
  /// used in the graphics engine.
  virtual auto GetShaderManager() -> ShaderManager* = 0;

  [[nodiscard]] virtual auto GetPolygonMode() const -> Types::PolygonMode = 0;
  virtual auto Render() -> void = 0;
  virtual auto ResizeViewport(int width, int height) -> void = 0;
  virtual auto SetBackgroundColor(const Types::Color& color) -> void = 0;
  virtual auto SetCamera(ICameraPtr spCamera) -> void = 0;
  virtual auto SetPolygonMode(Types::PolygonMode mode) -> void = 0;

 protected:
  IEngine() = default;
  // NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
  virtual ~IEngine() = default;
};

/// @typedef GLLoadProc
/// @brief Function pointer type for resolving OpenGL function addresses.
///
/// This type represents a function pointer that takes a function name as a
/// `const char*` and returns a pointer to the corresponding OpenGL function. It
/// enables flexibility in selecting the appropriate OpenGL function loader,
/// whether it's `eglGetProcAddress`, `wglGetProcAddress`, or another
/// platform-specific resolver.
using GLLoadProc = void* (*)(const char*);
using MaybeGLLoadProc = std::optional<GLLoadProc>;

/// @brief Alias for shared_ptr to IEngine.
using IEnginePtr = std::shared_ptr<IEngine>;

// Creates an engine instance, optionally accepting a custom OpenGL function
// resolver. If `proc_address_func` is not provided, a default resolver will be
// used.
DLLEXPORT auto CreateEngine(
    const MaybeGLLoadProc& proc_address_func = std::nullopt) -> IEnginePtr;

}  // namespace graphics_engine

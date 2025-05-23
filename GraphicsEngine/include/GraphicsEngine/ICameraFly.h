#pragma once

#include "ICamera.h"
#include "dll_export.h"

namespace graphics_engine {

/// @brief A first-person style camera; can strafe, and adjust pitch and yaw.
class ICameraFly : public ICamera {
 public:
  ICameraFly(const ICameraFly&) = delete;
  auto operator=(const ICameraFly&) -> ICameraFly& = delete;
  ICameraFly(ICameraFly&&) = delete;
  auto operator=(ICameraFly&&) -> ICameraFly& = delete;

  virtual auto SetPitchIncremental(float degrees) -> void = 0;
  virtual auto SetYawIncremental(float degrees) -> void = 0;
  virtual auto Strafe(const glm::vec3& direction) -> void = 0;
  virtual auto Zoom(double offset) -> void = 0;

 protected:
  ICameraFly() = default;

  // NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
  ~ICameraFly() override = default;
};

using ICameraFlyPtr = std::shared_ptr<ICameraFly>;
DLLEXPORT auto CreateCameraFly() -> ICameraFlyPtr;

}  // namespace graphics_engine

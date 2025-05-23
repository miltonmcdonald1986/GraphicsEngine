#pragma once

#include "ICamera.h"
#include "dll_export.h"

namespace graphics_engine {

/// @brief A static camera that simply adjusts for window-resizing.
class ICameraViewport : public ICamera {
 public:
  ICameraViewport(const ICameraViewport&) = delete;
  auto operator=(const ICameraViewport&) -> ICameraViewport& = delete;
  ICameraViewport(ICameraViewport&&) = delete;
  auto operator=(ICameraViewport&&) -> ICameraViewport& = delete;

 protected:
  ICameraViewport() = default;
  ~ICameraViewport() override = default;
};

using ICameraViewportPtr = std::shared_ptr<ICameraViewport>;
DLLEXPORT auto CreateCameraViewport() -> ICameraViewportPtr;

}  // namespace graphics_engine

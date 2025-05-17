#pragma once

#include "ICamera.h"
#include "DllImpExp.h"

namespace graphics_engine
{

	/// @brief A first-person style camera; can strafe, and adjust pitch and yaw.
	class ICameraFly : public ICamera
	{
	public:
		~ICameraFly() override = default;
		
		virtual auto SetPitchIncremental(float degrees) -> void = 0;
		virtual auto SetYawIncremental(float degrees) -> void = 0;
		virtual auto Strafe(const glm::vec3& direction) -> void = 0;
		virtual auto Zoom(double offset) -> void = 0;
	};

	using ICameraFlyPtr = std::shared_ptr<ICameraFly>;
	DLLEXPORT auto CreateCameraFly() -> ICameraFlyPtr;

}

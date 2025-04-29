#pragma once

#include "ICamera.h"
#include "DllImpExp.h"

namespace GraphicsEngine
{

	class ICameraFly : public ICamera
	{
	public:
		~ICameraFly() override = default;

		virtual auto GetEye() const -> glm::vec3 = 0;
		virtual auto SetEye(const glm::vec3& eye) -> void = 0;

		virtual auto GetFront() const -> glm::vec3 = 0;

		virtual auto GetRight() const->glm::vec3 = 0;

		virtual auto GetUp() const -> glm::vec3 = 0;
		virtual auto SetUp(const glm::vec3& up) -> void = 0;
		
		virtual auto SetPitchIncremental(float degrees) -> void = 0;
		virtual auto SetYawIncremental(float degrees) -> void = 0;

		virtual auto Strafe(const glm::vec3& direction) -> void = 0;
	};

	using ICameraFlyPtr = std::shared_ptr<ICameraFly>;
	GRAPHICSENGINE_API auto CreateCameraFly() -> ICameraFlyPtr;

}

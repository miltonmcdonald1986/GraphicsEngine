#pragma once

#include "ICameraFly.h"

namespace GraphicsEngine
{

	class CameraFly : public ICameraFly
	{
	public:
		CameraFly();
		~CameraFly() override = default;

		// Directions that can be set manually.

		auto GetEye() const -> glm::vec3 override;
		auto SetEye(const glm::vec3& eye) -> void override;

		auto GetUp() const->glm::vec3 override;
		auto SetUp(const glm::vec3& up) -> void override;

		// Directions that cannot be set manually.

		auto GetFront() const->glm::vec3 override;
		auto GetRight() const -> glm::vec3 override;

		auto GetViewMatrix() const -> glm::mat4 override;

		auto SetPitchIncremental(float degrees) -> void override;
		auto SetYawIncremental(float degrees) -> void override;

		auto Strafe(const glm::vec3& direction) -> void override;

	private:
		auto UpdateViewMatrix() -> void;

		glm::vec3 m_Eye = glm::vec3(0.f, 0.f, 1.f);
		glm::vec3 m_Center = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 m_Up = glm::vec3(0.f, 1.f, 0.f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
	};

}

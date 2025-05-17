#pragma once

#include "ICameraFly.h"
#include "Camera.h"

namespace graphics_engine
{

	class CameraFly : public ICameraFly
	{
	public:
		explicit CameraFly(CameraPtr spCamera);
		~CameraFly() override = default;

		auto GetFront()							const	-> glm::vec3							override;
		auto GetObservable()					const	-> Observable<glm::mat4, glm::mat4>*	override;
		auto GetProjectionMatrix()				const	-> glm::mat4							override;
		auto GetRight()							const	-> glm::vec3							override;
		auto GetUp()							const	-> glm::vec3							override;
		auto GetViewMatrix()					const	-> glm::mat4							override;
		auto SetAspectRatio(float aspectRatio)			-> void									override;
		auto SetEye(const glm::vec3& eye)				-> void									override;
		auto SetPitchIncremental(float degrees)			-> void									override;
		auto SetYawIncremental(float degrees)			-> void									override;
		auto Strafe(const glm::vec3& direction)			-> void									override;
		auto Zoom(double offset)						-> void									override;

	private:
		auto UpdateProjectionMatrix() -> void;

		CameraPtr m_spCamera;

		float m_Fov = 45.f;
	};

}

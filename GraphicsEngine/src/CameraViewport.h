#pragma once

#include "ICameraViewport.h"
#include "Camera.h"

namespace GraphicsEngine
{

	class CameraViewport : public ICameraViewport
	{
	public:
		explicit CameraViewport(CameraPtr spCamera);
		~CameraViewport() override = default;

		auto GetFront()							const	-> glm::vec3	override;
		auto GetProjectionMatrix()				const	-> glm::mat4	override;
		auto GetRight()							const	-> glm::vec3	override;
		auto GetUp()							const	-> glm::vec3	override;
		auto GetViewMatrix()					const	-> glm::mat4	override;
		auto SetAspectRatio(float aspectRatio)			-> void			override;
		auto SetEye(const glm::vec3& eye)				-> void			override;

	private:
		auto UpdateProjectionMatrix() -> void;

		CameraPtr m_spCamera = nullptr;
	};

}

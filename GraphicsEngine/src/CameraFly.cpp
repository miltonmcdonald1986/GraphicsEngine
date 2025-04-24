#include "CameraFly.h"

namespace GraphicsEngine
{

	auto CreateCameraFly() -> ICameraFlyPtr
	{
		return std::make_shared<CameraFly>();
	}

	CameraFly::CameraFly()
		: m_ViewMatrix(glm::lookAt(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)))
	{
	}

	auto CameraFly::GetViewMatrix() const -> glm::mat4
	{
		return m_ViewMatrix;
	}

}

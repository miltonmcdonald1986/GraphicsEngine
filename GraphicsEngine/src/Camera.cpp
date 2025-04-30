#include "Camera.h"

namespace GraphicsEngine
{

	Camera::Camera()
	{
		UpdateViewMatrix();
	}

	auto Camera::GetAspectRatio() const -> float
	{
		return m_AspectRatio;
	}

	auto Camera::GetCenter() const -> glm::vec3
	{
		return m_Center;
	}

	auto Camera::GetEye() const -> glm::vec3
	{
		return m_Eye;
	}

	auto Camera::GetFront() const -> glm::vec3
	{
		return glm::normalize(GetViewDir());
	}

	auto Camera::GetProjectionMatrix() const -> glm::mat4
	{
		return m_ProjectionMatrix;
	}

	auto Camera::GetRight() const -> glm::vec3
	{
		return glm::normalize(glm::cross(GetFront(), GetUp()));
	}

	auto Camera::GetUp() const -> glm::vec3
	{
		return glm::normalize(m_Up);
	}

	auto Camera::GetViewDir() const -> glm::vec3
	{
		return m_Center - m_Eye;
	}

	auto Camera::GetViewMatrix() const -> glm::mat4
	{
		return m_ViewMatrix;
	}

	auto Camera::SetAspectRatio(float aspectRatio) -> void
	{
		m_AspectRatio = aspectRatio;
	}

	auto Camera::SetCenter(const glm::vec3& center) -> void
	{
		m_Center = center;
		UpdateViewMatrix();
	}

	auto Camera::SetEye(const glm::vec3& eye) -> void
	{
		m_Eye = eye;
		UpdateViewMatrix();
	}

	auto Camera::SetProjectionMatrix(const glm::mat4& proj) -> void
	{
		m_ProjectionMatrix = proj;
	}

	auto Camera::SetUp(const glm::vec3& up) -> void
	{
		m_Up = up;
		UpdateViewMatrix();
	}

	auto Camera::UpdateViewMatrix() -> void
	{
		m_ViewMatrix = glm::lookAt(m_Eye, m_Center, m_Up);
	}

	CameraPtr CreateCamera()
	{
		return std::make_shared<Camera>();
	}

}

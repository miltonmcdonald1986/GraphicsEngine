#include "CameraFly.h"

namespace GraphicsEngine
{

	auto CreateCameraFly() -> ICameraFlyPtr
	{
		return std::make_shared<CameraFly>();
	}

	CameraFly::CameraFly()
	{
		UpdateViewMatrix();
	}

	auto CameraFly::GetEye() const -> glm::vec3
	{
		return m_Eye;
	}

	auto CameraFly::SetEye(const glm::vec3& eye) -> void
	{
		m_Eye = eye;
		UpdateViewMatrix();
	}

	auto CameraFly::GetFront() const -> glm::vec3
	{
		return glm::normalize(m_Center - m_Eye);
	}

	auto CameraFly::GetRight() const -> glm::vec3
	{
		return glm::normalize(glm::cross(glm::normalize(m_Center - m_Eye), glm::normalize(m_Up)));
	}

	auto CameraFly::GetUp() const -> glm::vec3
	{
		return m_Up;
	}

	auto CameraFly::SetUp(const glm::vec3& up) -> void
	{
		m_Up = up;
		UpdateViewMatrix();
	}

	auto CameraFly::GetViewMatrix() const -> glm::mat4
	{
		return m_ViewMatrix;
	}

	auto CameraFly::SetPitchIncremental(float degrees) -> void
	{
		static float pitch = 0.f;
		float oldPitch = pitch;
		pitch += degrees;
		pitch = glm::clamp(pitch, -89.f, 89.f);
		degrees = pitch - oldPitch;

		glm::vec3 front = GetFront();
		auto rotMat = glm::rotate(glm::mat4(1.f), glm::radians(degrees), GetRight());
		front = glm::normalize(glm::vec3(rotMat * glm::vec4(GetFront(), 1.f)));
		m_Up = glm::normalize(glm::vec3(rotMat * glm::vec4(m_Up, 1.f)));

		auto dist = glm::length(m_Center - m_Eye);
		m_Center = m_Eye + dist * front;
		UpdateViewMatrix();
	}

	auto CameraFly::SetYawIncremental(float degrees) -> void
	{
		auto rotMat = glm::rotate(glm::mat4(1.f), glm::radians(degrees), m_Up);
		
		auto front = glm::normalize(glm::vec3(rotMat * glm::vec4(GetFront(), 1.f)));
		m_Up = glm::normalize(glm::vec3(rotMat * glm::vec4(m_Up, 1.f)));
		auto dist = glm::length(m_Center - m_Eye);
		m_Center = m_Eye + dist*front;
		UpdateViewMatrix();
	}

	auto CameraFly::Strafe(const glm::vec3& direction) -> void
	{
		m_Center += direction;
		m_Eye += direction;
		UpdateViewMatrix();
	}

	auto CameraFly::UpdateViewMatrix() -> void
	{
		m_ViewMatrix = glm::lookAt(m_Eye, m_Center, m_Up);
	}

}

#include "CameraFly.h"

namespace graphics_engine
{

	auto CreateCameraFly() -> ICameraFlyPtr
	{
		return std::make_shared<CameraFly>(CreateCamera());
	}

	CameraFly::CameraFly(CameraPtr spCamera)
		: m_spCamera(spCamera)
	{
		UpdateProjectionMatrix();
	}

	auto CameraFly::GetFront() const -> glm::vec3
	{
		return m_spCamera->GetFront();
	}

	auto CameraFly::GetObservable() const -> Observable<glm::mat4, glm::mat4>*
	{
		return m_spCamera->GetObservable();
	}

	auto CameraFly::GetProjectionMatrix() const -> glm::mat4
	{
		return m_spCamera->GetProjectionMatrix();
	}

	auto CameraFly::GetRight() const -> glm::vec3
	{
		return m_spCamera->GetRight();
	}

	auto CameraFly::GetUp() const -> glm::vec3
	{
		return m_spCamera->GetUp();
	}

	auto CameraFly::GetViewMatrix() const -> glm::mat4
	{
		return m_spCamera->GetViewMatrix();
	}

	auto CameraFly::SetPitchIncremental(float degrees) -> void
	{
		static float pitch = 0.f;
		float oldPitch = pitch;
		pitch += degrees;
		pitch = glm::clamp(pitch, -89.f, 89.f);
		degrees = pitch - oldPitch;

		auto rotMat = glm::rotate(glm::mat4(1.f), glm::radians(degrees), GetRight());
		auto front = glm::normalize(glm::vec3(rotMat * glm::vec4(GetFront(), 1.f)));
		m_spCamera->SetUp(glm::normalize(glm::vec3(rotMat * glm::vec4(m_spCamera->GetUp(), 1.f))));

		auto dist = glm::length(m_spCamera->GetViewDir());
		m_spCamera->SetCenter(m_spCamera->GetEye() + dist*front);
	}

	auto CameraFly::SetYawIncremental(float degrees) -> void
	{
		auto rotMat = glm::rotate(glm::mat4(1.f), glm::radians(degrees), m_spCamera->GetUp());
		
		auto front = glm::normalize(glm::vec3(rotMat * glm::vec4(GetFront(), 1.f)));
		m_spCamera->SetUp(glm::normalize(glm::vec3(rotMat * glm::vec4(m_spCamera->GetUp(), 1.f))));
		auto dist = glm::length(m_spCamera->GetViewDir());
		m_spCamera->SetCenter(m_spCamera->GetEye() + dist*front);
	}

	auto CameraFly::Strafe(const glm::vec3& direction) -> void
	{
		m_spCamera->SetCenter(m_spCamera->GetCenter() + direction);
		m_spCamera->SetEye(m_spCamera->GetEye() + direction);
	}

	auto CameraFly::SetAspectRatio(float aspectRatio) -> void
	{
		m_spCamera->SetAspectRatio(aspectRatio);
		UpdateProjectionMatrix();
	}

	auto CameraFly::SetEye(const glm::vec3& eye) -> void
	{
		return m_spCamera->SetEye(eye);
	}

	auto CameraFly::Zoom(double offset) -> void
	{
		m_Fov -= static_cast<float>(offset);
		m_Fov = glm::clamp(m_Fov, 1.f, 45.f);
		UpdateProjectionMatrix();
	}

	auto CameraFly::UpdateProjectionMatrix() -> void
	{
		m_spCamera->SetProjectionMatrix(glm::perspective(glm::radians(m_Fov), m_spCamera->GetAspectRatio(), 0.1f, 100.f));
	}

}

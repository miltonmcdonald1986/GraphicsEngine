#include "CameraViewport.h"

namespace GraphicsEngine
{

	CameraViewport::CameraViewport(CameraPtr spCamera)
		: m_spCamera(spCamera)
	{
	}

	auto CameraViewport::GetFront() const -> glm::vec3
	{
		return m_spCamera->GetFront();
	}

	auto CameraViewport::GetProjectionMatrix() const -> glm::mat4
	{
		return m_spCamera->GetProjectionMatrix();
	}

	auto CameraViewport::GetRight() const -> glm::vec3
	{
		return m_spCamera->GetRight();
	}

	auto CameraViewport::GetUp() const -> glm::vec3
	{
		return m_spCamera->GetUp();
	}

	auto CameraViewport::GetViewMatrix() const -> glm::mat4
	{
		return m_spCamera->GetViewMatrix();
	}

	auto CameraViewport::SetAspectRatio(float aspectRatio) -> void
	{
		m_spCamera->SetAspectRatio(aspectRatio);
		UpdateProjectionMatrix();
	}

	auto CameraViewport::SetEye(const glm::vec3& eye) -> void
	{
		return m_spCamera->SetEye(eye);
	}

	auto CameraViewport::UpdateProjectionMatrix() -> void
	{
		float aspect = m_spCamera->GetAspectRatio();
		if (aspect >= 1)
			m_spCamera->SetProjectionMatrix(glm::ortho(-1.f, 1.f, -1.f/aspect, 1.f/aspect, -1.f, 1.f));
		else
			m_spCamera->SetProjectionMatrix(glm::ortho(-1.f * aspect, 1.f * aspect, -1.f, 1.f, -1.f, 1.f));

	}

	auto CreateCameraViewport() -> ICameraViewportPtr
	{
		return std::make_shared<CameraViewport>(CreateCamera());
	}

}

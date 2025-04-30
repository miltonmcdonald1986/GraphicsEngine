#pragma once

#include "ICamera.h"

namespace GraphicsEngine
{

	class Camera : public ICamera
	{
	public:
		Camera();
		~Camera() override = default;

		auto GetAspectRatio()							const	-> float;
		auto GetCenter()								const	-> glm::vec3;
		auto GetEye()									const	-> glm::vec3;
		auto GetFront()									const	-> glm::vec3	override;
		auto GetProjectionMatrix()						const	-> glm::mat4	override;
		auto GetRight()									const	-> glm::vec3	override;
		auto GetUp()									const	-> glm::vec3	override;
		auto GetViewDir()								const	-> glm::vec3;
		auto GetViewMatrix()							const	-> glm::mat4	override;
		auto SetAspectRatio(float aspectRatio)					-> void			override;
		auto SetCenter(const glm::vec3& center)					-> void;
		auto SetEye(const glm::vec3& eye)						-> void			override;
		auto SetProjectionMatrix(const glm::mat4& proj)			-> void;
		auto SetUp(const glm::vec3& up)							-> void;

	private:
		auto UpdateViewMatrix() -> void;

		float		m_AspectRatio		= 1.f;
		glm::vec3	m_Center			= glm::vec3(0.f, 0.f, 0.f);
		glm::vec3	m_Eye				= glm::vec3(0.f, 0.f, 1.f);
		glm::mat4	m_ProjectionMatrix	= glm::mat4(1.f);
		glm::vec3	m_Up				= glm::vec3(0.f, 1.f, 0.f);
		glm::mat4	m_ViewMatrix		= glm::mat4(1.f);
	};

	using CameraPtr = std::shared_ptr<Camera>;
	CameraPtr CreateCamera();

}

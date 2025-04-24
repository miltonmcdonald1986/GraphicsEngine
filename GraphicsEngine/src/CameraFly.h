#pragma once

#include "ICameraFly.h"

namespace GraphicsEngine
{

	class CameraFly : public ICameraFly
	{
	public:
		CameraFly();
		virtual ~CameraFly() = default;

		auto GetViewMatrix() const -> glm::mat4 override;

	private:
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
	};

}

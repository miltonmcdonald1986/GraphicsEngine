#pragma once

#include "glm/mat4x4.hpp"

namespace GraphicsEngine
{

	class ICamera
	{
	public:
		virtual ~ICamera() = default;

		auto GetViewMatrix() const -> glm::mat4 = 0;
	};

}

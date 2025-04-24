#pragma once

#include "glm/mat4x4.hpp"

namespace GraphicsEngine
{

	class ICamera
	{
	public:
		virtual ~ICamera() = default;

		virtual auto GetViewMatrix() const -> glm::mat4 = 0;
	};

	using ICameraPtr = std::shared_ptr<ICamera>;

}

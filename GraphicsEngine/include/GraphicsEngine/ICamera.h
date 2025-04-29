/// @file ICamera.h
/// @brief Interface for a camera in the graphics engine.
/// @author Milton McDonald
/// @date 2025-04-29

#pragma once

#include "glm/mat4x4.hpp"

namespace GraphicsEngine
{

	/// @brief The ICamera interface represents a camera in the graphics engine.
	class ICamera
	{
	public:
		virtual ~ICamera() = default;
		
		/// @brief Gets the projection matrix of the camera.
		/// @return A 4x4 projection matrix.
		virtual auto GetViewMatrix() const -> glm::mat4 = 0;
	};

	using ICameraPtr = std::shared_ptr<ICamera>;

}

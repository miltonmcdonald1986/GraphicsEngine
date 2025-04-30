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

		/// @brief Get the viewing direction of the camera.
		/// @return The direction the camera is looking.
		virtual auto GetFront() const -> glm::vec3 = 0;

		/// @brief Gets the projection matrix of the camera.
		/// @return A 4x4 projection matrix.
		virtual auto GetProjectionMatrix() const->glm::mat4 = 0;

		/// @brief Gets the right direction relative to the view and up directions.
		/// @return The right direction of the camera.
		virtual auto GetRight() const -> glm::vec3 = 0;

		/// @brief Gets the up direction relative to the view and right directions.
		/// @return The up direction of the camera.
		virtual auto GetUp() const -> glm::vec3 = 0;
		
		/// @brief Gets the view matrix of the camera.
		/// @return A 4x4 view matrix.
		virtual auto GetViewMatrix() const -> glm::mat4 = 0;

		/// @brief Set the aspect ration for the camera.
		/// @param aspectRatio the aspect ratio.
		virtual auto SetAspectRatio(float aspectRatio) -> void = 0;
		
		/// @brief Set the world position of the camera.
		/// @param eye the position of the camera in world coordinates.
		virtual auto SetEye(const glm::vec3& eye) -> void = 0;
	};

	using ICameraPtr = std::shared_ptr<ICamera>;

}

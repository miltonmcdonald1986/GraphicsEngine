/// @file ICamera.h
/// @brief Interface for a camera in the graphics engine.
/// @author Milton McDonald
/// @date 2025-04-29

#pragma once

#include "glm/mat4x4.hpp"

#include "Observable.h"

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

		/// @brief Retrieves an observable object for the camera's view and projection matrices.
		/// @return An ObservablePtr containing the view matrix and projection matrix of the camera.
		/// @note The observable allows tracking changes to the camera's matrices in real-time.
		virtual auto GetObservable() const -> Observable<glm::mat4, glm::mat4>* = 0;

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

	/// @brief Alias for a shared pointer to the ICamera interface.
	using ICameraPtr = std::shared_ptr<ICamera>;

	/// @brief Alias for a callback function that takes two 4x4 matrices (view and projection).
	/// @details	This callback is typically used to handle updates to the camera's view and projection matrices.
	///				It is any function of the form `void Fn(const glm::mat4& view, const glm::mat4& projection)`
	using ICameraCallback = Observable<glm::mat4, glm::mat4>::Callback;

}

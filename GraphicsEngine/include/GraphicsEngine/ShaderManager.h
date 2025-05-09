#pragma once

#include <optional>

#include "Types.h"

namespace GraphicsEngine
{

	/// @class ShaderManager
	/// @brief Abstract base class for managing shaders in the graphics engine.
	///
	/// This class provides an interface for adding shaders, retrieving the current shader,
	/// and setting uniform data for shaders.
	///
	/// @remarks This class should not be directly instantiated. The graphics engine will
	/// hold a unique pointer to this class. Clients can obtain a raw pointer to the
	/// ShaderManager by calling @ref IEngine::GetShaderManager. However, the lifetime of
	/// the ShaderManager is managed by the engine, and clients should not attempt to
	/// manage or delete it.
	class ShaderManager
	{
	public:

		/// @brief Virtual destructor for ShaderManager.
		virtual ~ShaderManager() = default;

		/// @brief Adds a shader to the manager.
		/// 
		/// @param vert Path to the vertex shader file.
		/// @param frag Path to the fragment shader file.
		/// @param oGeom Optional path to the geometry shader file (default: std::nullopt).
		/// @return An optional ShaderId if the shader was successfully added, or std::nullopt otherwise.
		virtual auto AddShader(
			const Path& vert, 
			const Path& frag, 
			const OptPath& oGeom = std::nullopt
		) -> OptShaderId = 0;

		/// @brief Retrieves the currently active shader.
		/// 
		/// @return An optional ShaderId of the currently active shader, or std::nullopt if no shader is active.
		virtual auto GetCurrentShader(
		) const -> OptShaderId = 0;

		/// @brief Sets uniform data for a shader.
		/// 
		/// @param id The ID of the shader.
		/// @param name The name of the uniform variable.
		/// @param data The data to set for the uniform variable.
		/// @return True if the uniform data was successfully set, false otherwise.
		virtual auto SetUniformData(
			ShaderId id,
			StringView name,
			const UniformData& data
		) -> bool = 0;

	};

}

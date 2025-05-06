#pragma once

#include <optional>

#include "Types.h"

namespace GraphicsEngine
{

	/// @class ShaderManager
	/// @brief Manages shader programs and uniform data.
	/// 
	/// @remarks	The IEngine class owns a unique_ptr to the ShaderManager, managing its lifetime. Clients can call
	///				GetShaderManager() to obtain a raw pointer to the ShaderManager. However, ownership remains with 
	///				the engine, so clients must not attempt to delete or modify its lifespan.
	class ShaderManager
	{
	public:

		virtual ~ShaderManager() = default;

		/// @brief Add a shader from files.
		/// @param[in] vert Path to the vertex shader.
		/// @param[in] frag Path to the fragment shader.
		/// @param[in] oGeom Optional path to the fragment shader.
		/// @returns If it succeeds, a shader id; nullopt otherwise.
		virtual auto AddShader(
			const Path& vert, 
			const Path& frag, 
			const OptPath& oGeom = std::nullopt
		) -> OptShaderId = 0;

		/// @brief Get the id of the current shader.
		/// @returns The id of the currently used shader program, if it exists; nullopt otherwise.
		virtual auto GetCurrentShader(
		) const -> OptShaderId = 0;

		/// @brief Sets uniform data for a shader program.
		/// @param[in] id The id of the shader program.
		/// @param[in] name The name of the uniform variable.
		/// @param[in] data The new value of the uniform variable.
		/// @returns true if it succeeds; false otherwise.
		virtual auto SetUniformData(
			ShaderId id,
			StringView name,
			const UniformData& data
		) -> bool = 0;

	};

}

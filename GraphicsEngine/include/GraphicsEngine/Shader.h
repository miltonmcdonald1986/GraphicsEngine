#pragma once

#include "Types.h"

namespace graphics_engine
{

	/// @class Shader
	/// @brief Represents a shader in the graphics engine.
	///
	/// The Shader class provides an interface for managing shaders, including
	/// retrieving their ID, source code, setting uniform data, and activating the shader.
	/// 
	/// @note Shaders should not be created directly. Instead, use either the `AddShaderFromFiles` 
	/// method of the `AddShaderFromSource` method of the `ShaderManager` to create and manage shaders. 
	/// This ensures proper initialization and integration with the graphics engine's shader management 
	/// system.
	class Shader
	{
	public:
		
		/// @brief Virtual destructor for the Shader class.
		virtual ~Shader() = default;

		/// @brief Gets the data from the uniform with the given name.
		/// 
		/// @return Uniform data.
		virtual auto GetUniformData (Types::StringView name) const -> std::optional<Types::UniformData> = 0;

		/// @brief Sets uniform data for the shader.
		///
		/// This method allows setting uniform data, such as matrices or vectors,
		/// to be used by the shader during rendering.
		///
		/// @param data The uniform data to set, of type `Types::UniformData`.
		/// @return `true` if the uniform data was successfully set, `false` otherwise.
		virtual auto SetUniformData(Types::StringView name, const Types::UniformData& data) -> bool = 0;

		/// @brief Activates the shader for use in rendering.
		///
		/// This method makes the shader the active shader program in the graphics pipeline.
		virtual auto Use() const -> void = 0;

		/// @brief Source code for the fragment shader.
		const Types::StringView FRAGMENT_SHADER_SOURCE;

		/// @brief Optional source code for the geometry shader.
		const Types::OptStringView GEOMETRY_SHADER_SOURCE;

		/// @brief Unique identifier for the shader.
		const Types::ShaderId ID;

		/// @brief The names of all active uniforms in this shader program.
		const Types::StringViews UNIFORM_NAMES;

		/// @brief Source code for the vertex shader.
		const Types::StringView VERTEX_SHADER_SOURCE;

	protected:

		explicit Shader (const std::tuple<Types::StringView, Types::OptStringView, Types::ShaderId, Types::StringViews, Types::StringView>& data);

	};

}

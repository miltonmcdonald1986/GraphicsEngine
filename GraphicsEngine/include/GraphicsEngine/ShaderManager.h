#pragma once

#include <optional>

#include "Shader.h"
#include "Types.h"

namespace graphics_engine
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
		virtual ~ShaderManager () = default;

		/// @brief Adds a shader to the manager.
		///
		/// This method loads and compiles the specified vertex, fragment, and optional geometry shaders,
		/// and adds the resulting shader program to the manager.
		///
		/// @param vert Path to the vertex shader file.
		/// @param frag Path to the fragment shader file.
		/// @param oGeom Optional path to the geometry shader file (default: std::nullopt).
		/// @return A raw pointer to the created `Shader` object, or `nullptr` if the shader could not be created.
		/// @note The lifetime of the returned `Shader` pointer is managed by the `ShaderManager`.
		/// Clients should not attempt to delete or manage the pointer.
		virtual auto AddShaderFromFiles (
			const Types::Path& vert, 
			const Types::Path& frag, 
			const Types::OptPath& oGeom = std::nullopt
		) -> Shader* = 0;

		/// @brief Adds a shader to the manager.
		///
		/// This method compiles the specified vertex, fragment, and optional geometry shaders from source
		/// and adds the resulting shader program to the manager.
		///
		/// @param vert Source code for the vertex shader.
		/// @param frag Source code for the fragment shader.
		/// @param oGeom Optional source code for the geometry shader (default: std::nullopt).
		/// @return A raw pointer to the created `Shader` object, or `nullptr` if the shader could not be created.
		/// @note The lifetime of the returned `Shader` pointer is managed by the `ShaderManager`.
		/// Clients should not attempt to delete or manage the pointer.
		virtual auto AddShaderFromSource (
			const Types::StringView& vert,
			const Types::StringView& frag,
			const Types::OptStringView& oGeom = std::nullopt
		) -> Shader* = 0;

		/// @brief Retrieves the currently active shader.
		///
		/// This method returns a pointer to the shader that is currently active in the graphics pipeline.
		///
		/// @return A raw pointer to the currently active `Shader` object, or `nullptr` if no shader is active.
		/// @note The lifetime of the returned `Shader` pointer is managed by the `ShaderManager`.
		/// Clients should not attempt to delete or manage the pointer.
		virtual auto GetCurrentShader () -> Shader* = 0;

		/// @brief Retrieves a shader by its unique identifier.
		///
		/// This method allows clients to retrieve a specific shader managed by the `ShaderManager`
		/// using its unique `ShaderId`.
		///
		/// @param id The unique identifier of the shader to retrieve.
		/// @return A raw pointer to the `Shader` object with the specified ID, or `nullptr` if no such shader exists.
		/// @note The lifetime of the returned `Shader` pointer is managed by the `ShaderManager`.
		/// Clients should not attempt to delete or manage the pointer.
		virtual auto GetShader (Types::ShaderId id) -> Shader* = 0;

	};

}

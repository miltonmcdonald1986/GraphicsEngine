#pragma once

#include "Types.h"
#include "DllImpExp.h"

namespace graphics_engine::ShaderUtilities
{

	/// @brief Get the source code for a shader from file.
	///
	/// @param path The path to the shader source code.
	/// @return The source code.
	DLLEXPORT auto GetSourceFromFile (const Types::Path& path) -> Types::String;

}

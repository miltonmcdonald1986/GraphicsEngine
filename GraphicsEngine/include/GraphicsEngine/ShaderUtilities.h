#pragma once

#include "Types.h"
#include "DllImpExp.h"

namespace GraphicsEngine::ShaderUtilities
{

	/// @brief Get the source code for a shader from file.
	///
	/// @param path The path to the shader source code.
	/// @return The source code.
	GRAPHICSENGINE_API auto GetSourceFromFile (const Types::Path& path) -> Types::String;

}

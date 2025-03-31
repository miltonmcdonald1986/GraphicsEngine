#pragma once

#include <array>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "glad/glad.h"

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::GL
{
	
	/// <summary>
	/// Error information
	/// </summary>
	enum class ErrorFlag : GLenum
	{
		/// <summary>
		/// No error has been recorded.
		/// </summary>
		NoError = GL_NO_ERROR,
		
		/// <summary>
		/// An unacceptable value is specified for an enumerated argument.
		/// </summary>
		InvalidEnum = GL_INVALID_ENUM,
		
		/// <summary>
		/// A numeric argument is out of range.
		/// </summary>
		InvalidValue = GL_INVALID_VALUE,
		
		/// <summary>
		/// The specified operation is not allowed in the current state.
		/// </summary>
		InvalidOperation = GL_INVALID_OPERATION,
		
		/// <summary>
		/// The framebuffer object is not complete.
		/// </summary>
		InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
		
		/// <summary>
		/// There is not enough memory left to execute the command.
		/// </summary>
		OutOfMemory = GL_OUT_OF_MEMORY
	};

	/// <summary>
	/// Gets the error flag; if an error is indicated, logs the error.
	/// </summary>
	/// <param name="file"> Use __FILE__ for logging purposes. </param>
	/// <param name="function"> Use __func__, __FUNCTION__, or __PRETTY_FUNCTION__ for logging purposes. </param>
	/// <param name="line"> Use __LINE__ for logging purposes. </param>
	/// <returns> The error flag. </returns>
	GRAPHICSENGINE_API auto GetError(const char* file, const char* function, int line) -> ErrorFlag;

}

#define GL_ERROR() GL::GetError(__FILE__, __func__, __LINE__) != GL::ErrorFlag::NoError

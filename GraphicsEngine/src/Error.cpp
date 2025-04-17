#include "pch.h"
#include "Error.h"

#include "Debug.h"
#include "Log.h"

namespace GraphicsEngine
{

	auto HandleError(const char* funcName) -> void
	{
		auto GLErrorMessage = [&funcName](const std::string& msg) -> std::string
			{
				std::stringstream loggerOutputStream;
				loggerOutputStream << funcName << ": " << msg;

#ifdef _DEBUG
				loggerOutputStream << "\nStack trace:\n============\n" << std::stacktrace::current();
				BREAKPOINT;
#endif
				std::string str = loggerOutputStream.str();
				return str;
			};

		switch (glGetError())
		{
		case GL_NO_ERROR:
			LOG_TRACE("No error has been recorded.");
			break;
		case GL_INVALID_ENUM:
			LOG_ERROR(GLErrorMessage("An unacceptable value is specified for an enumerated argument."));
			break;
		case GL_INVALID_VALUE:
			LOG_ERROR(GLErrorMessage("A numeric argument is out of range."));
			break;
		case GL_INVALID_OPERATION:
			LOG_ERROR(GLErrorMessage("The specified operation is not allowed in the current state."));
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			LOG_ERROR(GLErrorMessage("The framebuffer object is not complete."));
			break;
		case GL_OUT_OF_MEMORY:
			LOG_ERROR(GLErrorMessage("There is not enough memory left to execute the command."));
			break;
		default:
#ifdef _DEBUG
			LOG_WARN("Unknown error flag.");
			BREAKPOINT;
#endif
			break;
		};
	}
}

#include "pch.h"
#include "Error.h"

#include "Debug.h"
#include "Log.h"

namespace GraphicsEngine
{

	auto HandleError(const char* funcName) -> void
	{
		auto GLErrorMessage = [&funcName](const std::string& msg)
			{
				std::stringstream loggerOutputStream;
				loggerOutputStream << funcName << ": " << msg;
				loggerOutputStream << "\nStack trace:\n============\n" << std::stacktrace::current();
				std::string str = loggerOutputStream.str();
				return str;
			};

		LogPtr spLog = GetLog();
		if (!spLog)
			return;

		switch (glGetError())
		{
		case GL_NO_ERROR:
			spLog->Trace("No error has been recorded.");
			break;
		case GL_INVALID_ENUM:
			spLog->Error(GLErrorMessage("An unacceptable value is specified for an enumerated argument."));
			break;
		case GL_INVALID_VALUE:
			spLog->Error(GLErrorMessage("A numeric argument is out of range."));
			break;
		case GL_INVALID_OPERATION:
			spLog->Error(GLErrorMessage("The specified operation is not allowed in the current state."));
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			spLog->Error(GLErrorMessage("The framebuffer object is not complete."));
			break;
		case GL_OUT_OF_MEMORY:
			spLog->Error(GLErrorMessage("There is not enough memory left to execute the command."));
			break;
		default:
			spLog->Warn("Unknown error flag.");
			break;
		};
	}
}

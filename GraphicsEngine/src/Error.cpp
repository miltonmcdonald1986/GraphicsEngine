#include "pch.h"
#include "Error.h"

#include "Debug.h"

namespace GraphicsEngine
{

	auto HandleError(const char* funcName) -> void
	{
		auto LogError = [&funcName](const std::string& msg) -> void
			{
				auto logger = spdlog::get("Engine");
				if (!logger)
					return;

				std::stringstream loggerOutputStream;
				loggerOutputStream << funcName << ": " << msg;

#ifdef _DEBUG

				loggerOutputStream << "\nStack trace:\n============\n" << std::stacktrace::current();
				BREAKPOINT;

#endif

				logger->error(loggerOutputStream.str());
			};

		//auto logger = spdlog::get("Engine");
		switch (glGetError())
		{
		case GL_NO_ERROR:
			//logger->trace("No error has been recorded.");
			break;
		case GL_INVALID_ENUM:
			//LogError("An unacceptable value is specified for an enumerated argument.");
			break;
		case GL_INVALID_VALUE:
			//LogError("A numeric argument is out of range.");
			break;
		case GL_INVALID_OPERATION:
			//LogError("The specified operation is not allowed in the current state.");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			//LogError("The framebuffer object is not complete.");
			break;
		case GL_OUT_OF_MEMORY:
			//LogError("There is not enough memory left to execute the command.");
			break;
		default:
#ifdef _DEBUG

			//logger->warn("Unknown error flag.");
			BREAKPOINT;

#endif
			break;
		};
	}

}

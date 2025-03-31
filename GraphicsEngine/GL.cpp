#include "pch.h"
#include "GraphicsEngine/GL.h"

#include <filesystem>

#include "spdlog/spdlog.h"

namespace GraphicsEngine::GL
{

	auto GetError(const char* file, const char* function, int line) -> ErrorFlag
	{
		auto filename = std::filesystem::path(file).filename().string();

		const auto formatMsg = "{}\t{}\t{}\t{}";
		const std::map<ErrorFlag, std::string> errorMsgMap = {
			{ ErrorFlag::NoError, "No error has been recorded." },
			{ ErrorFlag::InvalidEnum,  "An unacceptable value is specified for an enumerated argument." },
			{ ErrorFlag::InvalidValue, "A numeric argument is out of range." },
			{ ErrorFlag::InvalidOperation, "The specified operation is not allowed in the current state." },
			{ ErrorFlag::InvalidFramebufferOperation, "The framebuffer object is not complete." },
			{ ErrorFlag::OutOfMemory, "There is not enough memory left to execute the command." }};

		auto logger = spdlog::get("Engine");
		ErrorFlag flag = static_cast<ErrorFlag>(glGetError());
		auto errorMsg = errorMsgMap.at(flag);
		switch (flag)
		{
		case ErrorFlag::NoError:
			logger->trace(std::format(formatMsg, filename, function, line, errorMsg));
			break;
		case ErrorFlag::InvalidEnum:
		case ErrorFlag::InvalidValue:
		case ErrorFlag::InvalidOperation:
		case ErrorFlag::InvalidFramebufferOperation:
		case ErrorFlag::OutOfMemory:
			logger->error(std::format(formatMsg, filename, function, line, errorMsg));
			break;
		default:
			logger->warn(std::format(formatMsg, filename, function, line, "Unknown error flag."));
			break;
		}

		return flag;
	}

}

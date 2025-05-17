#pragma once

namespace GraphicsEngine
{

	enum class ErrorCode
	{
		kAngleSumExceeded,
		kInvalidAngle,
		kInvalidSideLength
	};

	struct Error
	{
		const ErrorCode code;
		const std::string message;
	};

}

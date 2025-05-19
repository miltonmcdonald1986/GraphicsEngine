#pragma once

namespace graphics_engine
{

	enum class ErrorCode
	{
		kAngleSumExceeded,
		kInvalidAngle,
		kInvalidInput,
		kInvalidSideLength,
		kInvalidTriangle
	};

	struct Error
	{
		const ErrorCode code;
		const std::string message;
	};

}

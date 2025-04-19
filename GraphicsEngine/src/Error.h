#pragma once

#include <source_location>

namespace GraphicsEngine
{

	auto HandleError(const std::source_location& loc = std::source_location::current()) -> void;

}

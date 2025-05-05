#pragma once

#include "Types.h"

namespace GraphicsEngine
{

	struct Uniform
	{
		Uniform() = delete;
		Uniform(StringView name, int location);

		const String name;
		const int location;
		UniformData data;
	};

}

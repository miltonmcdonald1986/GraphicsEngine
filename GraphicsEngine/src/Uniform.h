#pragma once

#include "Types.h"

namespace GraphicsEngine
{

	struct Uniform
	{
		Uniform() = delete;
		Uniform(Types::StringView name, int location);

		const Types::String name;
		const int location;
		Types::UniformData data;
	};

}

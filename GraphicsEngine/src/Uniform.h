#pragma once

#include "Types.h"

namespace GraphicsEngine
{

	struct Uniform
	{
		Uniform() = delete;
		Uniform(StringView name, int location);

		const String Name;
		const int Location;
		UniformData Data;
	};

}

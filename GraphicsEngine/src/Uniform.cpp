#include "Uniform.h"

namespace GraphicsEngine
{

	Uniform::Uniform(StringView name, int location)
		:	name(std::string(name)),
			location(location)
	{
	}

}

#include "Uniform.h"

namespace GraphicsEngine
{

	Uniform::Uniform(Types::StringView name, int location)
		:	name(std::string(name)),
			location(location)
	{
	}

}

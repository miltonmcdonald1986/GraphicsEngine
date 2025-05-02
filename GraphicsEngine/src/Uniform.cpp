#include "Uniform.h"

namespace GraphicsEngine
{

	Uniform::Uniform(StringView name, int location)
		:	Name(std::string(name)),
			Location(location)
	{
	}

}

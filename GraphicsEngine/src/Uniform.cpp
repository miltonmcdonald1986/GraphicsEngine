#include "Uniform.h"

namespace GraphicsEngine
{

	Uniform::Uniform(Types::StringView name, int location)
		:	name(std::string(name)),
			location(location)
	{
	}

	Uniform::Uniform (const Uniform& other)
		: name (std::string(other.name)), location (other.location), data (other.data) 
	{
	}

}

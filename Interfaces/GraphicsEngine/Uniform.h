#pragma once

#include <string>
#include <variant>

#include "glm/fwd.hpp"

namespace GraphicsEngine
{

	enum UniformType
	{
		UNIFORM_TYPE_EMPTY,
		UNIFORM_TYPE_VEC4,
	};

	struct Uniform
	{
		UniformType m_Type;
		const char* m_Name;
		int m_Location;
		union 
		{
			float vec4[4];
		} m_Data;
	};

}

#pragma once

#include <string>
#include <variant>

#include "glm/fwd.hpp"

enum GEuniformType
{
	GE_UNIFORM_TYPE_EMPTY,
	GE_UNIFORM_TYPE_VEC4,
};

struct GEuniform
{
	GEuniformType m_Type;
	const char* m_Name;
	int m_Location;
	union
	{
		float vec4[4];
	} m_Data;
};

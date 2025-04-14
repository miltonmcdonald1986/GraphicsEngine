#pragma once

enum GEuniformType
{
	GE_UNIFORM_TYPE_EMPTY,
	GE_UNIFORM_TYPE_FLOAT,
	GE_UNIFORM_TYPE_VEC4,
};

struct GEuniform
{
	GEuniformType m_Type;
	const char* m_Name;
	int m_Location;
	union
	{
		float u_float;
		float u_vec4[4];
	} m_Data;
};

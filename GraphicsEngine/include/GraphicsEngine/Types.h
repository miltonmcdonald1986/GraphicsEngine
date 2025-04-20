#pragma once

namespace GraphicsEngine
{

	struct Color
	{
		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
		float a = 1.f;
	};

	enum class PolygonMode
	{
		Fill,
		Line,
		Point
	};

}

#pragma once

#include <variant>

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

	using ShaderId = unsigned int;

	using String = std::string;

	using StringView = std::string_view;
	using StringViews = std::vector<StringView>;
	
	using UniformData = std::variant<
		float,
		glm::mat4x4,
		glm::vec4,
		int
		>;

}

#pragma once

#include <expected>
#include <filesystem>
#include <variant>
#include <vector>

#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

namespace graphics_engine::Types
{

	struct Color
	{
		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
		float a = 1.f;
	};

	using Id = unsigned int;
	using OptId = std::optional<Id>;

	using EntityId = Id;
	using EntityIds = std::vector<EntityId>;

	using Index = unsigned int;
	using Indices = std::vector<Index>;

	using Path = std::filesystem::path;
	using OptPath = std::optional<Path>;

	enum class PolygonMode
	{
		Fill,
		Line,
		Point
	};

	using ShaderId = Id;
	using OptShaderId = std::optional<ShaderId>;

	using String = std::string;
	using Strings = std::vector<String>;
	
	struct StringHash {
		using is_transparent = void;
		std::size_t operator()(std::string_view sv) const {
			std::hash<std::string_view> hasher;
			return hasher (sv);
		}
	};

	using StringView = std::string_view;
	using StringViews = std::vector<StringView>;
	using OptStringView = std::optional<StringView>;

	using UniformData = std::variant<
		std::monostate,
		float,
		glm::mat4x4,
		glm::vec4,
		int
	>;

}

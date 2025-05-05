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

	using Id = unsigned int;

	class IEngine;
	using IEnginePtr = std::shared_ptr<IEngine>;

	class IEntity;
	using IEntityPtr = std::shared_ptr<IEntity>;
	using IEntities = std::vector<IEntityPtr>;

	class ITexture;
	using ITexturePtr = std::shared_ptr<ITexture>;
	using ITextures = std::vector<ITexturePtr>;

	using Path = std::filesystem::path;

	enum class PolygonMode
	{
		Fill,
		Line,
		Point
	};

	using ShaderId = Id;

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

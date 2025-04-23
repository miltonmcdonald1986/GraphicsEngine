#pragma once

#include <string>
#include <variant>

#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"

namespace GraphicsEngine
{

	using Data = std::variant<
		float, 
		glm::mat4x4,
		glm::vec4,
		int
		>;

	class IUniform
	{
	public:
		virtual ~IUniform() = default;

		virtual auto GetData() const -> Data = 0;
		virtual auto GetLocation() const -> int = 0;
		virtual auto GetName() const -> std::string = 0;
		virtual auto SetData(const Data& data) -> void = 0;
	};

	using IUniformPtr = std::shared_ptr<IUniform>;
	using IUniforms = std::vector<IUniformPtr>;

}

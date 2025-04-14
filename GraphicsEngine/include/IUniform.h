#pragma once

#include <string>
#include <variant>

#include "glm/vec4.hpp"

#include "GraphicsEngineFwd.h"

namespace GraphicsEngine
{

	enum class DataType
	{
		Float,
		Vec4
	};

	using Data = std::variant<float, glm::vec4>;

	class IUniform
	{
	public:
		virtual ~IUniform() = default;

		virtual auto GetData() const -> Data = 0;
		virtual auto GetLocation() const -> int = 0;
		virtual auto GetName() const -> std::string = 0;
		virtual auto GetType() const -> DataType = 0;
		virtual auto SetData(const Data& data) -> void = 0;
	};

}

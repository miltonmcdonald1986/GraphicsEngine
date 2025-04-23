#pragma once

#include <string_view>

#include "IUniform.h"

namespace GraphicsEngine
{

	class IShader
	{
	public:
		virtual ~IShader() = default;

		virtual auto GetId() const -> unsigned int = 0;
		virtual auto GetActiveUniform(std::string_view name) const -> IUniformPtr = 0;
		virtual auto GetActiveUniforms() const -> IUniforms = 0;
		virtual auto Use() const -> void = 0;
	};

	using IShaderPtr = std::shared_ptr<IShader>;
	using IShaders = std::vector<IShaderPtr>;

}

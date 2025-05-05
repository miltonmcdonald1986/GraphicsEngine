#pragma once

#include "Fwd.h"
#include "IShader.h"
#include "Uniform.h"

namespace GraphicsEngine
{

	class Shader
	{
	public:
		Shader(StringView vertSource, std::string_view fragSource, std::optional<StringView> oGeomSource = std::nullopt);

		auto GetId() const -> unsigned int;
		auto GetActiveUniform(std::string_view name) -> Uniform*;
		auto GetActiveUniformNames() const -> StringViews;
		auto SetUniformData(StringView name, const UniformData& data) -> void;
		auto Use() const -> void;

		const Id id = 0;

	private:
		Uniforms m_Uniforms;
	};

}

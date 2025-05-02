#pragma once

#include "Fwd.h"
#include "IShader.h"
#include "Uniform.h"

namespace GraphicsEngine
{

	class Shader : public IShader
	{
	public:
		Shader(std::string_view vertSource, std::string_view geomSource, std::string_view fragSource);

		auto GetId() const -> unsigned int;
		auto GetActiveUniform(std::string_view name) -> Uniform*;
		auto GetActiveUniformNames() const -> StringViews;
		auto SetUniformData(StringView name, const UniformData& data) -> void override;
		auto Use() const -> void;

	private:
		unsigned int m_Id = 0;
		Uniforms m_Uniforms;
	};

	IShaderPtr CreateShaderFromSourceCode(std::string_view vert, std::string_view geom, std::string_view frag);

}

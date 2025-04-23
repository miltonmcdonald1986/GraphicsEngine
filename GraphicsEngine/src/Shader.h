#pragma once

#include "IShader.h"

namespace GraphicsEngine
{

	class Shader : public IShader
	{
	public:
		Shader(std::string_view vertSource, std::string_view geomSource, std::string_view fragSource);

		auto GetId() const -> unsigned int override;
		auto GetActiveUniform(std::string_view name) const -> IUniformPtr override;
		auto GetActiveUniforms() const -> IUniforms override;
		auto Use() const -> void override;

	private:
		unsigned int m_Id = 0;
		IUniforms m_Uniforms;
	};

	IShaderPtr CreateShaderFromSourceCode(std::string_view vert, std::string_view geom, std::string_view frag);

}

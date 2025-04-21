#pragma once

#include "IShader.h"
#include "Uniform.h"

namespace GraphicsEngine
{

	class Shader : public IShader
	{
	public:
		Shader(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);

		auto GetId() const -> unsigned int override;
		auto GetActiveUniform(const String& name) const -> IUniformPtr override;
		auto GetActiveUniforms() const -> IUniforms override;
		auto Use() const -> void override;

	private:
		unsigned int m_Id = 0;
		IUniforms m_Uniforms;
	};

	IShaderPtr CreateShaderFromSourceCode(const std::string& vert, const std::string& geom, const std::string& frag);

}

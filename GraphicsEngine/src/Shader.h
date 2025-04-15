#pragma once

#include "IShader.h"
#include "Uniform.h"

namespace GraphicsEngine
{

	class Shader : public IShader
	{
	public:
		Shader(const std::string& vertSource, const std::string& geomSource, const std::string& fragSource);

		virtual auto GetId() const -> unsigned int override;
		virtual auto GetActiveUniforms() const -> IUniforms override;
		virtual auto Use() const -> void override;

	private:
		unsigned int m_Id = 0;
		IUniforms m_Uniforms;
	};

	IShaderPtr CreateShaderFromSourceCode(const std::string& vert, const std::string& geom, const std::string& frag);

}
//
//struct GEshader
//{
//public:
//	GEshader(const char* vertSource, const char* geomSource, const char* fragSource);
//
//	auto GetId() const -> GLuint;
//	auto GetActiveUniforms() const -> std::vector<GEuniform>;
//	auto GetNumActiveUniforms() const -> int;
//
//private:
//	GLuint m_ProgramId;
//	std::vector<GEuniform> m_Uniforms;
//};

#pragma once

#include "IShader.h"
#include "Uniform.h"

struct GEshader
{
public:
	GEshader(const char* vertSource, const char* geomSource, const char* fragSource);

	auto GetId() const -> GLuint;
	auto GetActiveUniforms(int* numUniforms, GEuniform* uniforms) -> void;

private:
	GLuint m_ProgramId;
	std::vector<GEuniform> m_Uniforms;
};

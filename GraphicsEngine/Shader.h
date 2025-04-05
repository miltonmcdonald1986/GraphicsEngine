#pragma once

#include "GraphicsEngine/IShader.h"
#include "GraphicsEngine/Uniform.h"

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

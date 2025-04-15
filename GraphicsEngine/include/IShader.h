#pragma once

#include <filesystem>
#include <vector>

#include "GraphicsEngineFwd.h"
#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	class IShader
	{
	public:
		virtual ~IShader() = default;

		virtual auto GetId() const -> unsigned int = 0;
		virtual auto GetActiveUniforms() const -> IUniforms = 0;
		virtual auto Use() const -> void = 0;
	};

}

//struct GEshader
//{
//public:
//	GEshader(const char* vertSource, const char* geomSource, const char* fragSource);
//
//	auto GetId() const->GLuint;
//	auto GetActiveUniforms() const->std::vector<GEuniform>;
//	auto GetNumActiveUniforms() const -> int;
//
//private:
//	GLuint m_ProgramId;
//	std::vector<GEuniform> m_Uniforms;
//};

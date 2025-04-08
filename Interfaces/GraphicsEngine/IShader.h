#pragma once

#include "GraphicsEngine/Uniform.h"
#include "GraphicsEngineImpExp.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct GEshader GEshader;

	GRAPHICSENGINE_API GEshader*	geCreateShaderFromFiles(const char* vert, const char* geom, const char* frag);
	GRAPHICSENGINE_API GEshader*	geCreateShaderFromStrings(const char* vert, const char* geom, const char* frag);
	GRAPHICSENGINE_API void			geDestroyShader(GEshader* pShader);
	GRAPHICSENGINE_API unsigned int	geGetActiveProgram();
	GRAPHICSENGINE_API void			geGetActiveUniforms(GEshader* pShader, int* numUniforms, GEuniform* uniforms);
	GRAPHICSENGINE_API bool			geSetUniform(GEshader* pShader, const GEuniform* uniform);

#ifdef __cplusplus
}
#endif

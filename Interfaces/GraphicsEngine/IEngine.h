#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include "GraphicsEngine/IShader.h"
#include "GraphicsEngineImpExp.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	enum GEentityType
	{
		GE_ENTITY_TYPE_INDEXED_POINTS_BASIC,
		GE_ENTITY_TYPE_TRIANGLE_BASIC,
		GE_ENTITY_TYPE_TRIANGLE_RGB
	};

	enum GEpolygonMode
	{
		GE_POLYGON_MODE_POINT,
		GE_POLYGON_MODE_LINE,
		GE_POLYGON_MODE_FILL
	};

	typedef struct GEengine GEengine;

	GRAPHICSENGINE_API GEengine*		geCreateGraphicsEngine();
	GRAPHICSENGINE_API void				geDestroyGraphicsEngine(GEengine* pEngine);
	GRAPHICSENGINE_API unsigned int		geGenerateEntity_IndexedPoints3DBasic(GEengine* pEngine, unsigned long long vertexBytes, float* vertices, unsigned long long indexBytes, unsigned int* indices);
	GRAPHICSENGINE_API unsigned int		geGenerateEntity_Triangle3DBasic(GEengine* pEngine);
	GRAPHICSENGINE_API unsigned int		geGenerateEntity_Triangle3DRGB(GEengine* pEngine);
	GRAPHICSENGINE_API void				geGetBackgroundColor(float color[4]);
	GRAPHICSENGINE_API GEshader*		geGetCurrentShaderProgram(GEengine* pEngine);
	GRAPHICSENGINE_API GEpolygonMode	geGetPolygonMode();
	GRAPHICSENGINE_API void				geRender(GEengine* pEngine);
	GRAPHICSENGINE_API void				geSetBackgroundColor(float color[4]);
	GRAPHICSENGINE_API void				geSetPolygonMode(GEpolygonMode mode);

#ifdef __cplusplus
}
#endif

#endif

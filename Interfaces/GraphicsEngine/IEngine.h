#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include "GraphicsEngineImpExp.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	typedef unsigned int Index;
	typedef unsigned long long ByteCount;

	enum GEentityType
	{
		GE_ENTITY_TYPE_INDEXED_POINTS_BASIC,
		GE_ENTITY_TYPE_TRIANGLE_BASIC,
		GE_ENTITY_TYPE_TRIANGLE_RGB
	};

	typedef struct GEengine GEengine;

	GRAPHICSENGINE_API GEengine*	geCreateGraphicsEngine();
	GRAPHICSENGINE_API void			geDestroyGraphicsEngine(GEengine* pEngine);
	GRAPHICSENGINE_API unsigned int geGenerateEntity_IndexedPoints3DBasic(GEengine* pEngine, ByteCount vertexBytes, float* vertices, ByteCount indexBytes, Index* indices);
	GRAPHICSENGINE_API unsigned int geGenerateEntity_Triangle3DBasic(GEengine* pEngine);
	GRAPHICSENGINE_API unsigned int geGenerateEntity_Triangle3DRGB(GEengine* pEngine);
	
	GRAPHICSENGINE_API void			geRender(GEengine* pEngine);
	GRAPHICSENGINE_API int			geSetVertices(GEengine* pEngine, unsigned int entId, unsigned long long size, float* data);

#ifdef __cplusplus
}
#endif

#endif // GRAPHICS_ENGINE_H

#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include "GraphicsEngineImpExp.h"

#ifdef __cplusplus
extern "C" {
#endif

	enum GEentityType
	{
		GE_ENTITY_TYPE_TRIANGLE_BASIC,
		GE_ENTITY_TYPE_TRIANGLE_RGB
	};

	typedef struct GEengine GEengine;

	GRAPHICSENGINE_API GEengine*	geCreateGraphicsEngine();
	GRAPHICSENGINE_API void			geDestroyGraphicsEngine(GEengine* pEngine);
	GRAPHICSENGINE_API unsigned int	geGenerateEntity(GEengine* pEngine, GEentityType type);
	GRAPHICSENGINE_API void			geRender(GEengine* pEngine);

#ifdef __cplusplus
}
#endif

#endif // GRAPHICS_ENGINE_H

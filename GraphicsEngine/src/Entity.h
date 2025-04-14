#pragma once

#include "Engine.h"
#include "Shader.h"

namespace GraphicsEngine
{
	struct Entity
	{
		//GEentityType m_Type = GE_ENTITY_TYPE_POS3F;
		unsigned int m_Id = 0;
		//GEshader* m_pShader = nullptr;
		//unsigned int m_VAO = 0;
		//unsigned int m_NumIndices = 0;
		//unsigned int m_NumVertices = 0;
	};

	bool operator<(const GraphicsEngine::Entity& e1, const GraphicsEngine::Entity& e2);

}

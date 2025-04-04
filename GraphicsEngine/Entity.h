#pragma once

#include "GraphicsEngine/IEngine.h"

namespace GraphicsEngine
{
	struct Entity
	{
		GEentityType m_Type = GE_ENTITY_TYPE_TRIANGLE_BASIC;
		unsigned int m_Id = 0;
		unsigned int m_Shader = 0;
		unsigned int m_VAO = 0;
		int m_NumIndices = 0;
	};

	bool operator<(const GraphicsEngine::Entity& e1, const GraphicsEngine::Entity& e2);

}

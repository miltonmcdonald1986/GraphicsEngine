#include "pch.h"
#include "Entity.h"

namespace GraphicsEngine
{

	bool operator<(const GraphicsEngine::Entity& e1, const GraphicsEngine::Entity& e2)
	{
		return e1.m_Id < e2.m_Id;
	}

}

#pragma once

enum class EntityType;

namespace GraphicsEngine
{

	struct Entity
	{
		EntityType m_Type;
		unsigned int m_Id;
		unsigned int m_Shader;
		unsigned int m_VAO;
	};

	bool operator<(const GraphicsEngine::Entity& e1, const GraphicsEngine::Entity& e2);

}

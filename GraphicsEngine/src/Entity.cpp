#include "pch.h"
#include "Entity.h"

namespace GraphicsEngine
{
	auto CreateEntity() -> EntityPtr
	{
		return EntityPtr(new Entity());
	}

	bool operator<(const GraphicsEngine::IEntityPtr& e1, const GraphicsEngine::IEntityPtr& e2)
	{
		if (!e1)
			return true;
		else if (!e2)
			return false;

		return e1->GetId() < e2->GetId();
	}

	auto Entity::GetId() const -> unsigned int
	{
		return m_Id;
	}

	auto Entity::GetNumIndices() const -> unsigned int
	{
		return m_NumIndices;
	}

	auto Entity::GetNumVertices() const -> unsigned int
	{
		return m_NumVertices;
	}

	auto Entity::GetShader() const -> IShaderPtr
	{
		return m_spShader;
	}

	auto Entity::GetVAO() const -> unsigned int
	{
		return m_VAO;
	}

	auto Entity::SetNumIndices(unsigned int numIndices) -> void
	{
		m_NumIndices = numIndices;
	}

	auto Entity::SetNumVertices(unsigned int numVertices) -> void
	{
		m_NumVertices = numVertices;
	}

	auto Entity::SetShader(IShaderPtr spShader) -> void
	{
		m_spShader = spShader;
	}

	auto Entity::SetVAO(GLuint vao) -> void
	{
		m_VAO = vao;
	}

}

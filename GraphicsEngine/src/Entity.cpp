#include "pch.h"
#include "Entity.h"

namespace GraphicsEngine
{
	auto CreateEntity() -> EntityPtr
	{
		return std::make_shared<Entity>();
	}

	auto operator<=>(const GraphicsEngine::IEntityPtr& e1, const GraphicsEngine::IEntityPtr& e2)
	{
		return e1->GetId() <=> e2->GetId();
	}

	auto Entity::GetId() const -> EntityId
	{
		return m_Id;
	}

	auto Entity::GetNumIndices() const -> Count
	{
		return m_NumIndices;
	}

	auto Entity::GetNumVertices() const -> Count
	{
		return m_NumVertices;
	}

	auto Entity::GetShader() const -> IShaderPtr
	{
		return m_spShader;
	}

	auto Entity::GetTexture() const -> ITexturePtr
	{
		return m_spTexture;
	}

	auto Entity::GetVAO() const -> VAO
	{
		return m_VAO;
	}

	auto Entity::SetNumIndices(GLsizei numIndices) -> void
	{
		m_NumIndices = numIndices;
	}

    auto Entity::SetId(unsigned int id) -> void
    {
		m_Id = id;
    }

    auto Entity::SetNumVertices(GLsizei numVertices) -> void
	{
		m_NumVertices = numVertices;
	}

	auto Entity::SetShader(IShaderPtr spShader) -> void
	{
		m_spShader = spShader;
	}

	auto Entity::SetTexture(ITexturePtr spTexture) -> void
	{
		m_spTexture = spTexture;
	}

	auto Entity::SetVAO(GLuint vao) -> void
	{
		m_VAO = vao;
	}

}

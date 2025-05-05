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

	auto Entity::GetId() const -> unsigned int
	{
		return m_Id;
	}

	auto Entity::GetModelMatrix() const -> glm::mat4
	{
		return m_ModelMatrix;
	}

	auto Entity::GetNumIndices() const -> int
	{
		return m_NumIndices;
	}

	auto Entity::GetNumVertices() const -> int
	{
		return m_NumVertices;
	}

	auto Entity::GetShaderId() const -> Id
	{
		return m_ShaderId;
	}

	auto Entity::GetTextures() const -> ITextures
	{
		return m_spTextures;
	}

	auto Entity::GetVAO() const -> unsigned int
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

	auto Entity::SetModelMatrix(const glm::mat4& model) -> void
	{
		m_ModelMatrix = model;
	}

    auto Entity::SetNumVertices(GLsizei numVertices) -> void
	{
		m_NumVertices = numVertices;
	}

	auto Entity::SetShaderId(Id id) -> void
	{
		m_ShaderId = id;
	}

	auto Entity::SetTextures(const ITextures& textures) -> void
	{
		m_spTextures = textures;
	}

	auto Entity::SetVAO(GLuint vao) -> void
	{
		m_VAO = vao;
	}

}

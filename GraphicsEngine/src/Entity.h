#pragma once

#include "IEntity.h"

namespace GraphicsEngine
{

	class Entity : public IEntity
	{
	public:
		~Entity() override = default;

		auto GetId() const -> unsigned int override;
		auto GetModelMatrix() const -> glm::mat4 override;
		auto GetNumIndices() const -> GLsizei override;
		auto GetNumVertices() const -> GLsizei override;
		auto GetShaderId() const -> Id override;
		auto GetTextures() const -> ITextures override;
		auto GetVAO() const -> unsigned int override;
		auto SetId(unsigned int id) -> void;
		auto SetModelMatrix(const glm::mat4& model) -> void override;
		auto SetNumIndices(GLsizei numIndices) -> void;
		auto SetNumVertices(GLsizei numVertices) -> void;
		auto SetShaderId(Id id) -> void override;
		auto SetTextures(const ITextures& textures) -> void override;
		auto SetVAO(GLuint vao) -> void;

	private:
		unsigned int m_Id = 0;
		GLsizei m_NumIndices = 0;
		GLsizei m_NumVertices = 0;
		Id m_ShaderId = 0;
		ITextures m_spTextures;
		GLuint m_VAO = 0;
		glm::mat4 m_ModelMatrix = glm::mat4(1.f);
	};

	using EntityPtr = std::shared_ptr<Entity>;

	auto CreateEntity() -> EntityPtr;

	auto operator<=>(const GraphicsEngine::IEntityPtr& e1, const GraphicsEngine::IEntityPtr& e2);

}

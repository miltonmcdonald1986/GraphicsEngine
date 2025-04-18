#pragma once

#include "IEntity.h"
#include "Fwd.h"

namespace GraphicsEngine
{

	class Entity : public IEntity
	{
	public:
		~Entity() override = default;

		auto GetId() const -> unsigned int override;
		auto GetNumIndices() const -> GLsizei override;
		auto GetNumVertices() const -> GLsizei override;
		auto GetShader() const -> IShaderPtr override;
		auto GetVAO() const -> unsigned int override;
		auto SetId(unsigned int id) -> void;
		auto SetNumIndices(GLsizei numIndices) -> void;
		auto SetNumVertices(GLsizei numVertices) -> void;
		auto SetShader(IShaderPtr spShader) -> void override;
		auto SetVAO(GLuint vao) -> void;

	private:
		unsigned int m_Id = 0;
		GLsizei m_NumIndices = 0;
		GLsizei m_NumVertices = 0;
		IShaderPtr m_spShader = nullptr;
		GLuint m_VAO = 0;
	};

	auto CreateEntity() -> EntityPtr;

	auto operator<=>(const GraphicsEngine::IEntityPtr& e1, const GraphicsEngine::IEntityPtr& e2);

}

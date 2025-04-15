#pragma once

#include "IEntity.h"
#include "Fwd.h"

namespace GraphicsEngine
{

	class Entity : public IEntity
	{
	public:
		virtual ~Entity() = default;

		virtual auto GetId() const -> unsigned int override;
		virtual auto GetNumIndices() const -> GLsizei override;
		virtual auto GetNumVertices() const -> GLsizei override;
		virtual auto GetShader() const -> IShaderPtr override;
		virtual auto GetVAO() const -> unsigned int override;
		auto SetNumIndices(GLsizei numIndices) -> void;
		auto SetNumVertices(GLsizei numVertices) -> void;
		virtual auto SetShader(IShaderPtr spShader) -> void override;
		auto SetVAO(GLuint vao) -> void;

	private:
		unsigned int m_Id = 0;
		GLsizei m_NumIndices = 0;
		GLsizei m_NumVertices = 0;
		IShaderPtr m_spShader = nullptr;
		GLuint m_VAO = 0;
	};

	auto CreateEntity() -> EntityPtr;

	bool operator<(const GraphicsEngine::IEntityPtr& e1, const GraphicsEngine::IEntityPtr& e2);

}

//namespace GraphicsEngine
//{
//	struct Entity
//	{
//		//GEentityType m_Type = GE_ENTITY_TYPE_POS3F;
//		unsigned int m_Id = 0;
//		//GEshader* m_pShader = nullptr;
//		//unsigned int m_VAO = 0;
//		//unsigned int m_NumIndices = 0;
//		//unsigned int m_NumVertices = 0;
//	};
//
//	bool operator<(const GraphicsEngine::Entity& e1, const GraphicsEngine::Entity& e2);
//
//}

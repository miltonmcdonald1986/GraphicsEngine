#pragma once

#include "ITexture.h"
#include "Observable.h"
#include "Shader.h"
#include "Types.h"

namespace GraphicsEngine
{

	/// @brief Represents a renderable entity within the graphics engine.
	///
	/// An Entity encapsulates vertex attributes, indices, shader information, and textures.
	/// It maintains transformation data via `modelMatrix`, allowing for manipulation in world space.
	/// 
	/// @note Entities should never be created directly. Instead, use the `AddEntity` method
	/// of the `EntityManager` to create and manage entities. This ensures proper initialization 
	/// and integration with the graphics engine's entity management system.
	struct Entity
	{
	public:

		/// @brief Deleted default constructor to enforce initialization with attributes and indices.
		Entity() = delete;

		/// @brief Constructs an Entity with the given attributes and indices.
		/// @param attributes Vertex attributes defining the entity's geometry.
		/// @param indices Index buffer specifying the order in which vertices are drawn.
		Entity(const Types::VertexAttributes& attributes, const Types::Indices& indices);

		/// @brief Unique identifier for the entity.
		const Types::EntityId ENTITY_ID;

		/// @brief Number of indices in the index buffer.
		const int NUM_INDICES;

		/// @brief Number of vertices in the entity.
		const int NUM_VERTICES;

		/// @brief Callback function for when camera view or projection matrices are updated.
		Observable<glm::mat4, glm::mat4>::Callback fnCameraCallback = nullptr;

		/// @brief Transformation matrix representing the entity's position, rotation, and scale.
		/// @details Defaults to the identity matrix.
		glm::mat4	modelMatrix = glm::mat4(1.f);

		/// @brief The shader program associated with the entity.
		Shader* pShader = nullptr;

		/// @brief Collection of textures applied to the entity.
		ITextures textures;

	private:

		explicit Entity(const std::tuple<GLuint, GLsizei, GLsizei>& data);
	};

}

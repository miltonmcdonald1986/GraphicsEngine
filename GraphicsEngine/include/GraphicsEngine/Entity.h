#pragma once

#include "ITexture.h"
#include "Observable.h"
#include "Types.h"

namespace GraphicsEngine
{

	/// @brief Represents a renderable entity within the graphics engine.
	///
	/// An Entity encapsulates vertex attributes, indices, shader information, and textures.
	/// It maintains transformation data via `modelMatrix`, allowing for manipulation in world space.
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

		/// @brief ID of the shader program associated with the entity.
		Types::ShaderId shaderId = 0;

		/// @brief Collection of textures applied to the entity.
		ITextures textures;

	private:

		/// @brief Constructs an entity using raw graphical data.
		/// @param data Tuple containing the VAO handle, the number of indices, and number of vertices.
		explicit Entity(const std::tuple<GLuint, GLsizei, GLsizei>& data);
	};

}
